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

void image::render(float clipX, float clipY, float clipW, float clipH, float alpha, D2D1_POINT_2F center)
{
	/*/ // ----- ���̾� Ŭ���� ----- //

	// ��ġ ����
	auto tempPos = IMAGEMANAGER->statePos();
	IMAGEMANAGER->statePos() -= fPOINT(clipX, clipY);

	// �߽���
	D2D1_POINT_2F rotateCenter;
	if (center.x == -1.f || center.y == -1.f)
	{
		rotateCenter.x = (clipX + clipW / 2);
		rotateCenter.y = (clipY + clipH / 2);
	}
	else
		rotateCenter = center;

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
	
	/*/ // ----- ���� ���� Ŭ���� ----- //

	// �߽���
	D2D1_POINT_2F rotateCenter;
	if (center.x == -1.f || center.y == -1.f)
	{
		rotateCenter = { clipW / 2, clipH / 2 };
	}
	else
	rotateCenter = center;

	IMAGEMANAGER->setTransform(&rotateCenter);

	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			clipW,
			clipH),
		alpha,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		RectF(clipX, clipY,
			clipX + clipW,
			clipY + clipH));
	//*/

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

void image::loopRender(fRECT * range, fPOINT offset, int frameX, int frameY, float alpha)
{
	// ���� ���� ���� ����
	fPOINT oPosition = IMAGEMANAGER->statePos();
	int oTransState = IMAGEMANAGER->getTransformState();

	// ���� ���� : ��ġ��
	IMAGEMANAGER->getTransformState(TF_POSITION);

	// ----- ���� ----- //

	// offset < 0 ����
	if (offset.x < 0.f) offset.x = _imageInfo->frameSize.x + rMod(offset.x, _imageInfo->frameSize.x);
	if (offset.y < 0.f) offset.y = _imageInfo->frameSize.y + rMod(offset.y, _imageInfo->frameSize.y);

	fPOINT currentPos;								// ȭ�� �� �׷��� ��ġ
	fPOINT currentSize = _imageInfo->frameSize;		// ȭ�� �� �׷��� ũ��

	fPOINT drawPos;									// �̹��� �� �׷��� ��ġ
	fPOINT drawSize;								// �̹��� �� �׷��� ũ��

	fPOINT drawRange = fRECT::size(range);			// ȭ�� �� �׷��� ���� ũ��
	for (float y = 0; y < drawRange.y; y += drawSize.y)
	{
		drawPos.y = rMod(y + offset.y, currentSize.y);
		drawSize.y = currentSize.y - drawPos.y;

		if (0 < frameY) drawPos.y += frameY * currentSize.y;

		if (drawRange.y < y + drawSize.y)
		{
			drawSize.y -= (y + drawSize.y) - drawRange.y;
			if (drawSize.y <= 0.f) return;
		}

		currentPos.y = y + range->LT.y;

		for (float x = 0; x < drawRange.x; x += drawSize.x)
		{
			drawPos.x = rMod(x + offset.x, currentSize.x);
			drawSize.x = currentSize.x - drawPos.x;

			if (0 < frameX) drawPos.x += frameX * currentSize.x;

			if (drawRange.x < x + drawSize.x)
			{
				drawSize.x -= (x + drawSize.x) - drawRange.x;
				if (drawSize.x <= 0.f) return;
			}

			currentPos.x = x + range->LT.x;

			IMAGEMANAGER->statePos(currentPos);
			render(drawPos.x, drawPos.y, drawSize.x, drawSize.y, alpha);
		}
	}

	// ----- ���� ----- //

	// ���� ���� ����
	IMAGEMANAGER->statePos(oPosition);
	IMAGEMANAGER->getTransformState() = oTransState;
}

void image::loopRender(fRECT * range, fPOINT offset, float frameSizeX, float frameSizeY, float alpha)
{
	// ���� ���� ���� ����
	fPOINT oPosition = IMAGEMANAGER->statePos();
	int oTransState = IMAGEMANAGER->getTransformState();

	// ���� ���� : ��ġ��
	IMAGEMANAGER->getTransformState(TF_POSITION);

	// ----- ���� ----- //

	// offset < 0 ����
	if (offset.x < 0.f) offset.x = _imageInfo->frameSize.x + rMod(offset.x, _imageInfo->frameSize.x);
	if (offset.y < 0.f) offset.y = _imageInfo->frameSize.y + rMod(offset.y, _imageInfo->frameSize.y);

	fPOINT currentPos;								// ȭ�� �� �׷��� ��ġ
	fPOINT currentSize = _imageInfo->frameSize;		// ȭ�� �� �׷��� ũ��

	fPOINT drawPos;									// �̹��� �� �׷��� ��ġ
	fPOINT drawSize;								// �̹��� �� �׷��� ũ��

	fPOINT drawRange = fRECT::size(range);			// ȭ�� �� �׷��� ���� ũ��
	for (float y = 0; y < drawRange.y; y += drawSize.y)
	{
		drawPos.y = rMod(y + offset.y, currentSize.y);
		drawSize.y = currentSize.y - drawPos.y;

		drawPos.y += frameSizeY;

		if (drawRange.y < y + drawSize.y)
		{
			drawSize.y -= (y + drawSize.y) - drawRange.y;
			if (drawSize.y <= 0.f) return;
		}

		currentPos.y = y + range->LT.y;

		for (float x = 0; x < drawRange.x; x += drawSize.x)
		{
			drawPos.x = rMod(x + offset.x, currentSize.x);
			drawSize.x = currentSize.x - drawPos.x;

			drawPos.x += frameSizeX;

			if (drawRange.x < x + drawSize.x)
			{
				drawSize.x -= (x + drawSize.x) - drawRange.x;
				if (drawSize.x <= 0.f) return;
			}

			currentPos.x = x + range->LT.x;

			IMAGEMANAGER->statePos(currentPos);
			render(drawPos.x, drawPos.y, drawSize.x, drawSize.y, alpha);
		}
	}

	// ----- ���� ----- //

	// ���� ���� ����
	IMAGEMANAGER->statePos(oPosition);
	IMAGEMANAGER->getTransformState() = oTransState;
}
