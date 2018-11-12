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
	virtual UI_LIST_ITER update(void) { return WINMANAGER->getIgnoreIter(); };
	virtual void render(void) {};

public:
	image* & getImage(void) { return _img; };
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };
	windowBase* &getWindow(void) { return _bindWindow; };

	fPOINT getAbsPos(void) { return _pos + _bindWindow->getPos(); };
	fRECT getAbsRect(void) { fRECT rc; rc.LT = getAbsPos(); rc.RB = rc.LT + _size; return rc; };

	function<UI_LIST_ITER(void)> & getActivate(void) { return _active; };
public:
	buttonBase() : _img(NULL) {};
	~buttonBase() {};
};