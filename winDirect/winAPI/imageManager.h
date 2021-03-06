#pragma once
#include "singletonBase.h"
#include "image.h"

enum e_IMG_RENDER_STATE
{
	IRS_ALWAYS_RESET_TRANSFORM	= 0x0001,
	IRS_NONE					= 0
};

enum e_IMAGE_FLIP
{
	IMAGE_FLIP_NONE		= 0b00,
	IMAGE_FLIP_VERTICAL	= 0b10,
	IMAGE_FLIP_HORIZON	= 0b01
};

enum e_TRANSFORM
{
	TF_NONE			= 0,
	TF_POSITION		= 0b0001,		// 위치
	TF_ROTATION		= 0b0010,		// 회전
	TF_FLIP			= 0b0100,		// 반전
	TF_SCALE		= 0b1000,		// 크기
	TF_ALL			= 0b1111		// 전부
};

class imageManager : public singletonBase<imageManager>
{
private:
	typedef unordered_map<string, image*> mapImageList;				// 맵 이미지 목록
	typedef unordered_map<string, image*>::iterator mapImageIter;		// 맵 이미지 목록 반복자

private:
	mapImageList _mImageList;

	IWICImagingFactory*	_imgFactory = NULL;
	ID2D1Layer *		_layer = NULL;

private:
	fPOINT		_imgPos;
	int			_imgFlip;
	float		_imgRotate;
	D2D1_SIZE_F	_imgScale;

	int		_renderTransform;
	int		_renderState;

public:
	HRESULT init(void);
	void release(void);

public :
	// 키값으로 이미지 탐색
	image* find(string strKey);

	// 키값으로 이미지 삭제
	BOOL deleteImage(string strKey);

	// 전체 이미지 삭제
	BOOL deleteAll();

	IWICImagingFactory * getFactory(void) { return _imgFactory; };

	// ----- image ----- //
	image* add(string strKey, const wchar_t * fileName, int maxFrameX = 1, int maxFrameY = 1);
	image* add(string strKey, const wchar_t * fileName, fPOINT frameSize) { return add(strKey, fileName, frameSize.x, frameSize.y); };
	image* add(string strKey, const wchar_t * fileName, float frameWidth, float frameHeight);

	// ----- layer ----- //
	void pushLayer(fRECT * clippedArea);
	void popLayer(void);

	// ----- state ----- //
	fPOINT &	statePos(void)		{ return _imgPos; };
	int &		stateFlip(void)		{ return _imgFlip; };
	float &		stateRotate(void)	{ return _imgRotate; };
	D2D1_SIZE_F& stateScale(void)	{ return _imgScale; };

	fPOINT &	statePos(float x, float y)	{ return _imgPos = fPOINT(x, y); };
	fPOINT &	statePos(fPOINT input)		{ return _imgPos = input; };
	int &		stateFlip(int input)		{ return _imgFlip = input; };
	float &		stateRotate(float input)	{ return _imgRotate = input; };
	D2D1_SIZE_F& stateScale(float xy)		{ return _imgScale = D2D1_SIZE_F{ xy, xy }; }
	D2D1_SIZE_F& stateScale(float x, float y){ return _imgScale = D2D1_SIZE_F{ x, y }; }
	D2D1_SIZE_F& stateScale(fPOINT input)	{ return _imgScale = D2D1_SIZE_F{ input.x, input.y }; }

	void resetTransform(void);
	void resetTransform(e_TRANSFORM resetValue);
	void setTransform(void) { D2D1_POINT_2F posZero = { 0.f, 0.f }; setTransform(&posZero); };
	void setTransform(D2D1_POINT_2F * pos);
	void setTransformZero(void);
	void enableTransform(void) { _renderTransform = TF_ALL; };
	void enableTransform(int tf) { _renderTransform |= tf; };
	void disableTransform(void) { _renderTransform = 0; };
	void disableTransform(int tf) { _renderTransform = bit_pick(_renderTransform, tf); };
	int & getTransformState(void) { return _renderTransform; };
	int & getTransformState(int tf) { return _renderTransform = tf; };

	void setRenderState(e_IMG_RENDER_STATE state, int value);
	const int getRenderState(void) { return _renderState; };
	const int getRenderState(e_IMG_RENDER_STATE state) { return _renderState & state; }

private:
	void	_flip2fpos(int flip, D2D1_SIZE_F & output);

public :
	imageManager() {};
	~imageManager() {};
};