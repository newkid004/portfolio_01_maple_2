#pragma once

class windowBase;

class buttonBase
{
protected:
	image* _img;
	fPOINT _pos;	// relative
	fPOINT _size;

	function<void(void)> _active;
	windowBase* _bindWindow;
public:
	virtual list<windowBase*>::iterator* update(void) { return NULL; };
	virtual void render(fPOINT & offset) {};

public:
	image* & getImage(void) { return _img; }
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };
	function<void(void)> & getActivate(void) { return _active; };
	windowBase* &getWindow(void) { return _bindWindow; }
public:
	buttonBase() {};
	~buttonBase() {};
};
