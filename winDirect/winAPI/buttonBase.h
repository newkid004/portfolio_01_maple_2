#pragma once
#include "windowBase.h"

class buttonBase
{
protected:
	image* _img;
	fPOINT _pos;	// relative
	fPOINT _size;

	function<UI_LIST_ITER(void)> _active;
	windowBase* _bindWindow;

public:
	virtual HRESULT init(void) { return S_OK; };
	virtual void release(void) {};
	virtual UI_LIST_ITER update(void) { return _active(); };
	virtual void render(void) { if (_img) { IMAGEMANAGER->statePos(getAbsPos()); _img->render(); } };

public:
	image* & getImage(void) { return _img; };
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };
	windowBase* &getWindow(void) { return _bindWindow; };

	fPOINT getAbsPos(void) { return _pos + _bindWindow->getPos(); };
	virtual fRECT getAbsRect(void) { fRECT rc; rc.LT = getAbsPos(); rc.RB = rc.LT + _size; return rc; };

	function<UI_LIST_ITER(void)> & getActive(void) { return _active; };
public:
	buttonBase() : _img(NULL), _bindWindow(NULL) {};
	~buttonBase() {};
};

class buttonBaseFrame : public buttonBase
{
protected :
	fPOINT _curFrame;
	fPOINT _frameSize;

public :
	virtual HRESULT init(image* img) { _img = img; _size = _img->getSize(); _frameSize = _img->getFrameSize(); return S_OK; }
	virtual void render(void) { if (_img) { IMAGEMANAGER->statePos(getAbsPos()); _img->frameRender(_curFrame); } };

public :
	fPOINT & getCurFrame(void) { return _curFrame; };
	fPOINT & getFrameSize(void) { return _frameSize; };

	virtual fRECT getAbsRect(void) { fRECT rc; rc.LT = getAbsPos(); rc.RB = rc.LT + _frameSize; return rc; };

public :
	buttonBaseFrame() {};
	~buttonBaseFrame() {};
};