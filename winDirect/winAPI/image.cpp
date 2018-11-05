#include "stdafx.h"
#include "image.h"
#include "animation.h"

// 알파블렌드를 사용하기 위한 라이브러리 추가
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
	
	// 파일 읽기
	if (S_OK != (hr =IMAGEMANAGER->getFactory()->CreateDecoderFromFilename(_fileName.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder))) return hr;

	// 프레임 단위 해석 디코더
	decoder->GetFrame(0, &fDecoder);

	// 이미지 형식 변환
	if (S_OK != (hr = IMAGEMANAGER->getFactory()->CreateFormatConverter(&converter))) return hr;
	if (S_OK != (hr = converter->Initialize(fDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom))) return hr;

	// D2D용 비트맵 생성
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
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈를 먼저 해줄것
	if (_imageInfo != NULL) this->release();

	//이미지 정보 새로 생성후 초기화하기
	_imageInfo = new IMAGE_INFO;

	_imageInfo->maxFrame = { (long)maxFrameX, (long)maxFrameY };

	//파일이름
	_fileName = fileName;

	//리소스 입력
	if (S_OK != _putImage())
	{
		release();
		return E_FAIL;
	}

	// 이미지 정보 입력
	_putImageInfo();

	// 프레임 보정
	--_imageInfo->maxFrame.x;
	--_imageInfo->maxFrame.y;

	return S_OK;
}

void image::release(void)
{
	//이미지 정보가 남아 있다면 해제
	if (_imageInfo)
	{
		// 이미지 삭제
		_imageInfo->bitmap->Release();

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
	}
}

//렌더 (0, 0지점에 렌더)
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
	// 위치 보정
	auto tempPos = IMAGEMANAGER->statePos();
	IMAGEMANAGER->statePos() -= fPOINT(clipX, clipY);

	// 중심점
	D2D1_POINT_2F rotateCenter;
	if (center.x == -1.f || center.y == -1.f)
	{
		rotateCenter.x = (clipX + clipW / 2);
		rotateCenter.y = (clipY + clipH / 2);
	}
	else
		rotateCenter = center;

	IMAGEMANAGER->setTransform(&rotateCenter);


	// 레이어 입력
	fRECT clipArea(clipX, clipY, clipX + clipW, clipY + clipH);
	IMAGEMANAGER->pushLayer(&clipArea);

	// draw
	_renderTarget->DrawBitmap(_imageInfo->bitmap,
		RectF(
			0, 0,
			_imageInfo->size.x,
			_imageInfo->size.y),
		alpha);

	// 레이어 제외
	IMAGEMANAGER->popLayer();

	// 보정 되돌림
	IMAGEMANAGER->statePos() = tempPos;

	// 렌더 상태에 따라 
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
	// 기존 렌더 상태 저장
	fPOINT oPosition = IMAGEMANAGER->statePos();
	int oTransState = IMAGEMANAGER->getTransformState();

	// 렌더 형태 : 위치만
	IMAGEMANAGER->getTransformState(TF_POSITION);

	// ----- 실행 ----- //

	// offset < 0 교정
	if (offset.x < 0.f) offset.x = _imageInfo->frameSize.x + rMod(offset.x, _imageInfo->frameSize.x);
	if (offset.y < 0.f) offset.y = _imageInfo->frameSize.y + rMod(offset.y, _imageInfo->frameSize.y);

	fPOINT currentPos;								// 화면 내 그려질 위치
	fPOINT currentSize = _imageInfo->frameSize;		// 화면 내 그려질 크기

	fPOINT drawPos;									// 이미지 내 그려질 위치
	fPOINT drawSize;								// 이미지 내 그려질 크기

	fPOINT drawRange = fRECT::size(range);			// 화면 내 그려질 범위 크기
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

	// ----- 종료 ----- //

	// 렌더 상태 복구
	IMAGEMANAGER->statePos(oPosition);
	IMAGEMANAGER->getTransformState() = oTransState;
}

void image::loopRender(fRECT * range, fPOINT offset, float frameSizeX, float frameSizeY, float alpha)
{
	// 기존 렌더 상태 저장
	fPOINT oPosition = IMAGEMANAGER->statePos();
	int oTransState = IMAGEMANAGER->getTransformState();

	// 렌더 형태 : 위치만
	IMAGEMANAGER->getTransformState(TF_POSITION);

	// ----- 실행 ----- //

	// offset < 0 교정
	if (offset.x < 0.f) offset.x = _imageInfo->frameSize.x + rMod(offset.x, _imageInfo->frameSize.x);
	if (offset.y < 0.f) offset.y = _imageInfo->frameSize.y + rMod(offset.y, _imageInfo->frameSize.y);

	fPOINT currentPos;								// 화면 내 그려질 위치
	fPOINT currentSize = _imageInfo->frameSize;		// 화면 내 그려질 크기

	fPOINT drawPos;									// 이미지 내 그려질 위치
	fPOINT drawSize;								// 이미지 내 그려질 크기

	fPOINT drawRange = fRECT::size(range);			// 화면 내 그려질 범위 크기
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

	// ----- 종료 ----- //

	// 렌더 상태 복구
	IMAGEMANAGER->statePos(oPosition);
	IMAGEMANAGER->getTransformState() = oTransState;
}
