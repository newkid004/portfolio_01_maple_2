#pragma once

//class windowBase;
class buttonBase;

class windowBase
{
protected :
	typedef list<windowBase*>::iterator UI_LIST_ITER;

protected:
	image* _img;
	UI_LIST_ITER* _managedIter;
	string _winName;
	fPOINT _pos;

	list<buttonBase*> _lButton;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual UI_LIST_ITER* update(void);
	virtual void render(void);

public :
	UI_LIST_ITER*& getIter(void) { return _managedIter; };
	string & getName(void) { return _winName; };
	fPOINT & getPos(void) { return _pos; };

public :	// ----- window ----- //
	virtual void show(void) { WINMANAGER->show(this); };
	virtual UI_LIST_ITER* close(void) {return WINMANAGER->close(this); };
	virtual bool isShow(void) { return _managedIter ? true : false; };

public :	// ----- button ----- //
	buttonBase* addButton(buttonBase* addition) { _lButton.push_back(addition); };

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

	UI_LIST_ITER* close(void) override { _scroll = 0; return windowBase::close(); };

public:
	windowShop() {};
	~windowShop() {};
};