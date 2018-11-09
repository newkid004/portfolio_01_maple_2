#pragma once
#include "buttonBase.h"

class windowShop;

class buttonShop_itemList : public buttonBase
{
protected :
	int _slot;

private :
	virtual HRESULT init(void) override { return S_OK; };

public :
	virtual HRESULT init(int slot, windowShop* bindWindow);
	virtual UI_LIST_ITER update(void);
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