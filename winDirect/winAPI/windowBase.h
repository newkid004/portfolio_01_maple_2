#pragma once

class buttonBase;

class windowBase
{
protected:
	image* _img;
	list<windowBase*>::iterator _managedIter;
	string _winName;
	fPOINT _pos;

	map<string, buttonBase*> _mButton;

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

public :	// ----- window ----- //
	virtual void show(void) { WINMANAGER->show(this); };
	virtual UI_LIST_ITER close(void) {return WINMANAGER->close(this); };
	virtual bool isShow(void) { return !(_managedIter == WINMANAGER->getIgnoreIter()); };
	virtual bool isClose(void) { return _managedIter == WINMANAGER->getIgnoreIter(); };

public :	// ----- button ----- //
	buttonBase* addButton(string name, buttonBase* addition);
	buttonBase* findButton(string name);

public :
	windowBase() {};
	~windowBase() {};
};

// ----- window : shop ----- //
#define CNT_SHOP_ITEM_LIST 9
class shopBase;
class windowShop : public windowBase
{
private :
	int _scroll;
	shopBase* _shop;

public :
	HRESULT init(void);
	void render(void);

public :
	int & getScroll(void) { return _scroll; };
	shopBase*& getShop(void) { return _shop; };

	UI_LIST_ITER close(void) override { _scroll = 0; return windowBase::close(); };

public:
	windowShop() {};
	~windowShop() {};
};