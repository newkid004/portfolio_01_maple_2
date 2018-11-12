#pragma once
#include "buttonBase.h"

class windowShop;

// ----- item slot ----- //
class buttonShop_itemList : public buttonBase
{
protected :
	int _slot;

protected:
	virtual HRESULT init(void) override { return S_OK; };

public :
	virtual HRESULT init(int slot, windowShop* bindWindow);
	virtual UI_LIST_ITER update(void) override;
	virtual void render(void) override;

public :
	int & getSlot(void) { return _slot; };

protected :
	virtual void initPosition(windowShop* bindWindow);
	virtual void updateDbClick(void) { KEYMANAGER->setDBClick(GAMESYSTEM->findCallback("UI_shop_button_buy"), false); };

	virtual itemBase* getRenderContent(void);

public:
	buttonShop_itemList() {};
	~buttonShop_itemList() {};
};

class buttonShop_playerItemList : public buttonShop_itemList
{
protected :
	virtual void initPosition(windowShop* bindWindow) override;
	virtual void updateDbClick(void) override { KEYMANAGER->setDBClick(GAMESYSTEM->findCallback("UI_shop_button_sell"), false); };

	virtual itemBase* getRenderContent(void) override;

public :
	buttonShop_playerItemList() {};
	~buttonShop_playerItemList() {};
};

// ----- item tab ----- //
class buttonShop_itemTab : public buttonBase
{
protected :
	int _type;
	int* _bindTab;

protected:
	virtual HRESULT init(void) override { return S_OK; };

public:
	virtual HRESULT init(int tabType, windowShop* bindWindow);
	virtual UI_LIST_ITER update(void) override { return _active(); };
	virtual void render(void) override;

protected :
	virtual void initProp(void);
	virtual void initActive(void);

public :
	int & getType(void) { return _type; };
	int* & getBindType(void) { return _bindTab; };

public : 
	buttonShop_itemTab() {};
	~buttonShop_itemTab() {};
};

class buttonShop_playerItemTab : public buttonShop_itemTab
{

protected:
	virtual void initProp(void) override;
	virtual void initActive(void) override;

public :
	buttonShop_playerItemTab() {};
	~buttonShop_playerItemTab() {};
};

// ----- scroll ----- //
class buttonShop_scroll_direction : public buttonBase
{
protected :
	int _scroll;

protected:
	virtual HRESULT init(void) override { return S_OK; };

public:
	virtual HRESULT init(int scroll, windowShop* bindWindow);
	virtual UI_LIST_ITER update(void) override { return _active(); };
	virtual void render(void) override;

protected :
	virtual void initProp(void);

public :
	int & getScroll(void) { return _scroll; };

public :
	buttonShop_scroll_direction() {};
	~buttonShop_scroll_direction() {};
};

class buttonShop_scroll_direction_Player : public buttonShop_scroll_direction
{
public :
	virtual void render(void) override;

protected :
	virtual void initProp(void);

public :
	buttonShop_scroll_direction_Player() {};
	~buttonShop_scroll_direction_Player() {};
};

class buttonShop_scroll_head : public buttonBase
{
protected:
	buttonBase* _bindButton_top;
	buttonBase* _bindButton_bot;

protected:
	virtual HRESULT init(void) override { return S_OK; };

public:
	virtual HRESULT init(buttonBase* buttonTop, buttonBase* buttonBot, windowShop* bindWindow);
	virtual UI_LIST_ITER update(void) override;
	virtual void render(void) override;

protected :
	float getMinHeight(void) { return _bindButton_top->getPos().y + _bindButton_top->getSize().y; };
	float getMaxHeight(void) { return _bindButton_bot->getPos().y - _img->getSize().y; };
	virtual float getDividePlace(void);

public:
	buttonShop_scroll_head() {};
	~buttonShop_scroll_head() {};
};

class buttonShop_scroll_head_Player : public buttonShop_scroll_head
{
protected :
	virtual float getDividePlace(void) override;

public :
	buttonShop_scroll_head_Player() {};
	~buttonShop_scroll_head_Player() {};
};