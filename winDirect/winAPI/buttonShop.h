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
	virtual UI_LIST_ITER update(void) { return _bindWindow->getIter(); };
	virtual void render(void) override;

protected :
	virtual void initPosition(windowShop* bindWindow);
	virtual itemBase* getRenderContent(void);

public:
	buttonShop_itemList() {};
	~buttonShop_itemList() {};
};

class buttonShop_playerItemList : public buttonShop_itemList
{
protected :
	virtual void initPosition(windowShop* bindWindow) override;
	virtual itemBase* getRenderContent(void) override;

public :
	buttonShop_playerItemList() {};
	~buttonShop_playerItemList() {};
};