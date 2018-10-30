#include "stdafx.h"
#include "imageManager.h"

HRESULT imageManager::init(void)
{
	// �̹��� ���丮 ����
	CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_imgFactory));

	// �̹��� Ŭ�������� ���� ���̾� ����
	_renderTarget->CreateLayer(NULL, &_layer);

	// state �ʱ�ȭ
	_imgPos = { 0, 0 };
	_imgFlip = 0;
	_imgRotate = 0.0f;
	_imgScale = { 1.f, 1.f };

	_renderTransform = TF_ALL;
	_renderState = 0;

	return S_OK;
}

void imageManager::release(void)
{
	this->deleteAll();

	_imgFactory->Release();
	_layer->Release();
}

image * imageManager::add(string strKey, const wchar_t * fileName, int maxFrameX, int maxFrameY, bool isUsePixel)
{
	// �߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	image* img = find(strKey);

	// �̹� �ִٸ� ����
	if (img) return img;

	// ������ ����
	img = new image;
	img->init(fileName, maxFrameX, maxFrameY, isUsePixel);

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

// imageManager �ٽ� �Լ�
image * imageManager::find(string strKey)
{
	// �ش� Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	// ã��
	if (key != _mImageList.end()) return key->second;

	// ��ã��
	return NULL;
}

BOOL imageManager::deleteImage(string strKey)
{
	// �ش� Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	// ã��
	if (key != _mImageList.end())
	{
		// �̹��� ����
		key->second->release();
		SAFE_DELETE(key->second);

		// �� ���� ����
		_mImageList.erase(key);

		return TRUE;
	}

	return FALSE;
}

BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		// �̹����� ������
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		// �̹����� ������
		else
		{
			++iter;
		}
	}

	// ������ġ
	_mImageList.clear();

	return TRUE;
}

void imageManager::pushLayer(fRECT * clippedArea)
{
	_renderTarget->PushLayer(
		LayerParameters(RectF(
			clippedArea->LT.x,
			clippedArea->LT.y,
			clippedArea->RB.x,
			clippedArea->RB.y)),
		_layer);
}

void imageManager::popLayer(void)
{
	_renderTarget->PopLayer();
}

void imageManager::resetTransform(void)
{
	_imgPos = { 0 ,0 };
	_imgFlip = 0; 
	_imgRotate = 0.0f;
	_imgScale = { 1.f, 1.f };
}

void imageManager::resetTransform(e_TRANSFORM resetValue)
{
	if (resetValue & TF_POSITION)	_imgPos = { 0 ,0 };
	if (resetValue & TF_ROTATION)	_imgRotate = 0.0f;
	if (resetValue & TF_FLIP)		_imgFlip = 0;
	if (resetValue & TF_SCALE)		_imgScale = { 1.f, 1.f };
}

void imageManager::setTransform(D2D1_POINT_2F * pos)
{
	Matrix3x2F m = Matrix3x2F::Identity();

	// ����
	if (_renderTransform & TF_FLIP) {
		D2D1_SIZE_F flipPos; _flip2fpos(_imgFlip, flipPos);
		m = m * Matrix3x2F::Scale(flipPos, *pos);
	}
	if (_renderTransform & TF_SCALE)	m = m * Matrix3x2F::Scale(_imgScale, *pos);				// ũ��
	if (_renderTransform & TF_ROTATION)	m = m * Matrix3x2F::Rotation(_imgRotate, *pos);			// ȸ��
	if (_renderTransform & TF_POSITION)	m = m * Matrix3x2F::Translation(_imgPos.x, _imgPos.y);	// ��ġ

	_renderTarget->SetTransform(m);
}

void imageManager::setRenderState(e_IMG_RENDER_STATE state, int value)
{
	switch (state)
	{
	case IRS_ALWAYS_RESET_TRANSFORM: {		// �׻� �ʱ�ȭ �ϴ���
		if (value)	_renderState = bit_put(_renderState, state);
		else		_renderState = bit_pick(_renderState, state);
	} break;
	}
}

void imageManager::_flip2fpos(int flip, D2D1_SIZE_F & output)
{
	output.width = 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_VERTICAL) ? -1.0f : 1.0f;
	output.height = 0 < (flip & e_IMAGE_FLIP::IMAGE_FLIP_HORIZON) ? -1.0f : 1.0f;
}
