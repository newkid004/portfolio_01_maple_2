#pragma once

// 클래스 전방선언
class animation;

class image
{
public:
	typedef struct tagImage
	{
		ID2D1Bitmap*	bitmap;			// 비트맵
		fPOINT			size;			// 크기
		POINT			maxFrame;		// 최대 프레임 수
		fPOINT			frameSize;		// 프레임 크기

		fPOINT			centerPos;		// 중앙
		fPOINT			centerFramePos;	// 프레임 중앙

		tagImage()
		{
			bitmap			= NULL;
			size			= { 0.f, 0.f };
			maxFrame		= { 0, 0 };
			frameSize		= { 0.f, 0.f };

			centerPos		= { 0.f, 0.f };
			centerFramePos	= { 0.f, 0.f };
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO*		_imageInfo;		//이미지 정보
	wstring			_fileName;		//이미지 이름

private :
	HRESULT _putImage(void);
	void	_putImageInfo(void);

public:
	// 프레임 초기화
	HRESULT init(const wchar_t * fileName);
	HRESULT init(const wchar_t * fileName, int maxFrameX, int maxFrameY);
	HRESULT init(const wchar_t * fileName, fPOINT frameSize);	// init to frameSize
	HRESULT init(const wchar_t * fileName, float frameWidth, float frameHeight);	// init to frameSize

	//해제
	void release(void);

	//렌더 (내가 지정한 좌표에 이미지 출력한다)
	void render(float alpha = 1.0f, D2D1_POINT_2F center = { -1.f, -1.f });

	// 이미지 클리핑
	void render(float clipX, float clipY, float clipW, float clipH, float alpha = 1.0f, D2D1_POINT_2F center = { -1.f, -1.f });

	// 프레임 렌더
	void frameRender(int frameX, int frameY, float alpha = 1.0f);
	void frameRender(fPOINT frame, float alpha = 1.0f);

	// 애니 렌더
	void aniRender(animation * ani, float alpha = 1.0f);

	// 루프 렌더 : 회전 무효화
	void loopRender(fRECT * range, fPOINT offset = 0.f, int frameX = 0, int frameY = 0, float alpha = 1.f);
	void loopRender(fRECT * range, fPOINT offset = 0.f, float frameSizeX = 0, float frameSizeY = 0, float alpha = 1.f);

public :
	// =========================== inline ============================== //
	// 이미지 가로, 세로크기
	inline const fPOINT & getSize(void) { return _imageInfo->size; };

	// 이미지 1프레임 가로, 세로 크기
	inline const fPOINT & getFrameSize(void) { return _imageInfo->frameSize; }

	// 이미지 프레임 개수
	inline const POINT & getMaxFrame(void) { return _imageInfo->maxFrame; };

	// 중앙좌표
	inline const fPOINT & getCenterPos(void) { return _imageInfo->centerPos; }
	inline const fPOINT & getCenterFramePos(void) { return _imageInfo->centerFramePos; };

	// 이미지 정보
	inline const IMAGE_INFO* getImageInfo(void) { return _imageInfo; };

	image();
	~image() {}
};