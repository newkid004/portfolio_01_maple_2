#include "stdafx.h"
#include "image.h"
#include "animation.h"

// ���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
#pragma comment(lib, "msimg32.lib")

image::image() : _imageInfo(NULL)
{
}

HRESULT image::_putImage()
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder * decoder = NULL;
	IWICBitmapFrameDecode * fDecoder = NULL;
	IWICFormatConverter * converter = NULL;
	
	// ���� �б�
	if (S_OK != (hr =IMAGEMANAGER->getFactory()->CreateDecoderFromFilename(_fileName.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder))) return hr;

	// ������ ���� �ؼ� ���ڴ�
	decoder->GetFrame(0, &fDecoder);

	// �̹��� ���� ��ȯ
	if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateFormatConverter(&converter))) return hr;
	if (S_OK != (hr = converter->Initialize(fDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom))) return hr;

	// D2D�� ��Ʈ�� ����
	if (S_OK != (hr = _renderTarget->CreateBitmapFromWicBitmap(converter, NULL, &_imageInfo->bitmap))) return hr;
		
	converter->Release();
	fDecoder->Release();
	decoder->Release();

	return hr;
}

void image::_putImageInfo(void)
{
	_imageInfo->size.x = _imageInfo->bitmap->GetSize().width;
	_imageInfo->size.y = _imageInfo->bitmap->GetSize().height;
	_imageInfo->frameSize.x = _imageInfo->size.x / _imageInfo->maxFrame.x;
	_imageInfo->frameSize.y = _imageInfo->size.y / _imageInfo->maxFrame.y;
}

HRESULT image::init(const wchar_t * fileName)
{
	return init(fileName, 1, 1);
}

HRESULT image::init(const wchar_t * fileName, int maxFrameX, int maxFrameY)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;

	_imageInfo->maxFrame = { (long)maxFrameX, (long)maxFrameY };

	//�����̸�
	_fileName = fileName;

	//���ҽ� �Է�
	if (S_OK != _putImage())
	{
		release();
		return E_FAIL;
	}

	// �̹��� ���� �Է�
	_putImageInfo();

	// ������ ����
	--_imageInfo->maxFrame.x;
	--_imageInfo->maxFrame.y;

	return S_OK;
}

void image::release(void)
{
	//�̹��� ������ ���� �ִٸ� ����
	if (_imageInfo)
	{
		// �̹��� ����
		_imageInfo->bitmap->Release();

		//������ ����
		SAFE_DELETE(_imageInfo);
	}
}

//���� (0, 0������ ����)
void image::render(float alpha)
{
	D2D1_POINT_2F rotateCenter = { _imageInfo->size.x / 2, _imageInfo->size.y / 2 };
	IMAGEMANAGER->setTransform(&rotateCenter);

	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);

	if (IMAGEMANAGER->getRenderState() & IRS_ALWAYS_RESET_TRANSFORM)
		IMAGEMANAGER->resetTransform();
}

void image::render(float clipX, float clipY, float clipW, float clipH, float alpha)
{
	// ��ġ ����
	auto tempPos = IMAGEMANAGER->statePos();
	IMAGEMANAGER->statePos() -= fPOINT(clipX , clipY);

	// �߽���
	D2D1_POINT_2F rotateCenter;
	rotateCenter.x = (clipX + clipW / 2);
	rotateCenter.y = (clipY + clipH / 2);
	IMAGEMANAGER->setTransform(&rotateCenter);

	// ���̾� �Է�
	fRECT clipArea(clipX, clipY, clipX + clipW, clipY + clipH);
	IMAGEMANAGER->pushLayer(&clipArea);

	// draw
	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);

	// ���̾� ����
	IMAGEMANAGER->popLayer();

	// ���� �ǵ���
	IMAGEMANAGER->statePos() = tempPos;

	// ���� ���¿� ���� 
	if (IMAGEMANAGER->getRenderState() & IRS_ALWAYS_RESET_TRANSFORM)
		IMAGEMANAGER->resetTransform();
}

void image::frameRender(int frameX, int frameY, float alpha)
{
	this->render(
		(float)frameX * _imageInfo->frameSize.x,
		(float)frameY * _imageInfo->frameSize.y , 
		_imageInfo->frameSize.x,
		_imageInfo->frameSize.y,
		alpha);
}

void image::frameRender(fPOINT frame, float alpha)
{
	this->render(
		frame.x * _imageInfo->frameSize.x,
		frame.y * _imageInfo->frameSize.y,
		_imageInfo->frameSize.x,
		_imageInfo->frameSize.y,
		alpha);
}

void image::aniRender(animation * ani, float alpha)
{
	if (ani->isPlay())
		this->render(
			(float)ani->getFramePos().x, (float)ani->getFramePos().y,
			(float)ani->getFrameWidth(), (float)ani->getFrameHeight(),
			alpha);
}

void image::loopRender(fRECT * range, fPOINT offset, float alpha)
{
	// ���� ���� ���� ����
	fPOINT oPosition = IMAGEMANAGER->statePos();
	int oTransState = IMAGEMANAGER->getTransformState();

	// ȸ�� ��ȿȭ
	IMAGEMANAGER->disableTransform(TF_ROTATION);

	// ----- ���� ----- //

	fPOINT scale = fPOINT(IMAGEMANAGER->statScale().width, IMAGEMANAGER->statScale().height);
	fPOINT currentPos = range->LT;
	fPOINT currentSize = _imageInfo->size * scale;
	fPOINT destPos;

	for (; currentPos.y < range->RB.y; currentPos.y += currentSize.y)
	{
		destPos.y = currentPos.y + currentSize.y;
		destPos.y = range->RB.y <= destPos.y ? range->RB.y : destPos.y;

		for (currentPos.x = 0; currentPos.x < range->RB.x; currentPos.x += currentSize.x)
		{
			destPos.x = currentPos.x + currentSize.x;
			destPos.x = range->RB.x <= destPos.x ? range->RB.x : destPos.x;
			IMAGEMANAGER->statePos(currentPos);

			// ���� �̹��� ��� ���� ���
			fPOINT imgRatio = destPos - currentPos;
			imgRatio.x = _imageInfo->size.x * (imgRatio.x / _imageInfo->size.x);
			imgRatio.y = _imageInfo->size.y * (imgRatio.y / _imageInfo->size.y);

			render(offset.x, offset.y, imgRatio.x, imgRatio.y, alpha);
		}
	}

	// ----- ���� ----- //

	// ���� ���� ����
	IMAGEMANAGER->statePos(oPosition);
	IMAGEMANAGER->getTransformState() = oTransState;
}

void image::loopFrameRender(int frameX, int frameY, fRECT * range, fPOINT offset, float alpha)
{
}
