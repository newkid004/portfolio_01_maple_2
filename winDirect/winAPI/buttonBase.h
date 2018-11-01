#pragma once

class windowBase;

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
	image* & getImage(void) { return _img; }
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };
	windowBase* &getWindow(void) { return _bindWindow; }

	function<UI_LIST_ITER(void)> & getActivate(void) { return _active; };
public:
	buttonBase() {};
	~buttonBase() {};
};