#include "stdafx.h"
#include "image.h"
#include "animation.h"

// ���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
#pragma comment(lib, "msimg32.lib")

image::image() : _imageInfo(NULL)
{
}

HRESULT image::_putImage(bool isUsePixel)
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

	// pixel�� ��Ʈ�� ����
	if (isUsePixel)
	{
		if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateBitmap(_imageInfo->bitmap->GetSize().width, _imageInfo->bitmap->GetSize().height,
			GUID_WICPixelFormat32bppRGBA1010102, WICBitmapNoCache, &_imageInfo->wBitmap)))return hr;
	}
		
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

HRESULT image::init(const wchar_t * fileName, bool isUsePixel)
{
	return init(fileName, 1, 1, isUsePixel);
}

HRESULT image::init(const wchar_t * fileName, int maxFrameX, int maxFrameY, bool isUsePixel)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ����� ���� ���ٰ�
	if (_imageInfo != NULL) this->release();

	//�̹��� ���� ���� ������ �ʱ�ȭ�ϱ�
	_imageInfo = new IMAGE_INFO;

	_imageInfo->maxFrame = { (long)maxFrameX, (long)maxFrameY };

	//�����̸�
	_fileName = fileName;

	//���ҽ� �Է�
	if (S_OK != _putImage(isUsePixel))
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

		// �ȼ� �̹��� ����
		if (_imageInfo->wBitmap) 
			_imageInfo->wBitmap->Release();

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

ColorF image::getBitmapPixel(POINT pos)
{
	IWICBitmapLock * bLock;
	BYTE* buffer;
	UINT size;
	WICRect rc;
	rc.X = pos.x; rc.Width = 1;
	rc.Y = pos.y; rc.Height = 1;
	
	_imageInfo->wBitmap->Lock(&rc, WICBitmapLockRead, &bLock);
	bLock->GetDataPointer(&size,&buffer);
	
	ColorF color = ColorF(buffer[2], buffer[1], buffer[0], buffer[3]);
	bLock->Release();
	return color;
}

HRESULT image::getBitmapPixels(POINT posSour, POINT posDest, ColorF * out)
{
	IWICBitmapLock * bLock;
	BYTE* buffer;
	UINT size;
	WICRect rc;
	rc.X = posSour.x; rc.Width = posDest.x - posSour.x;
	rc.Y = posSour.y; rc.Height = posDest.y - posSour.y;

	_imageInfo->wBitmap->Lock(&rc, WICBitmapLockRead, &bLock);
	HRESULT hr = bLock->GetDataPointer(&size, &buffer);

	for (int i = 0; i < size / sizeof(UINT); ++i)
		out[i] = ColorF(buffer[2], buffer[1], buffer[0], buffer[3]);

	bLock->Release();

	return hr;
}
