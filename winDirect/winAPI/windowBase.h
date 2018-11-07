#pragma once

class buttonBase;

class windowBase
{
protected:
	image* _img;
	list<windowBase*>::iterator _managedIter;
	string _winName;
	fPOINT _pos;
	fPOINT _size = -1.f;

	unordered_map<string, buttonBase*> _mButton;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual UI_LIST_ITER update(void);
	virtual void render(void);

public :
	image* & getImage(void) { return _img; }
	UI_LIST_ITER & getIter(void) { return _managedIter; };
	string & getName(void) { return _winName; };
	fPOINT & getPos(void) { return _pos; };
	fPOINT & getSize(void) { return _size; };

public :	// ----- window ----- //
	virtual void show(void) { WINMANAGER->show(this); };
	virtual UI_LIST_ITER close(void) { return WINMANAGER->close(this); };
	virtual UI_LIST_ITER trans(void) { return WINMANAGER->trans(this); };
	virtual bool isShow(void) { return !(_managedIter == WINMANAGER->getIgnoreIter()); };
	virtual bool isClose(void) { return _managedIter == WINMANAGER->getIgnoreIter(); };

public :	// ----- button ----- //
	buttonBase* addButton(string name, buttonBase* addition);
	buttonBase* findButton(string name);

public :
	windowBase() {};
	~windowBase() {};
};
