#pragma once
#include "windowBase.h"

// ¹öÆ° : 38°³

#define CNT_SHOP_ITEM_LIST 9
#define INTERVAL_ITEM_IN_SHOP 42.f

struct tagShopContent
{
	int scroll;
	int tabIndex;

	fPOINT firstItemPos;

	tagShopContent()
	{
		scroll = 0;
		tabIndex = 0;
	}
};

class shopBase;
class buttonShop_itemList;
class windowShop : public windowMovable
{
private:
	tagShopContent _conShop;
	tagShopContent _conPlayer;
	shopBase* _shop;

	buttonShop_itemList* _currentButton;

public:
	HRESULT init(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

protected :
	void initButton(void);
	void initDbClick(void);
	void initWheel(void);

	void renderInfo(void);

public:
	tagShopContent & getContentShop(void) { return _conShop; };
	tagShopContent & getContentPlayer(void) { return _conPlayer; };
	shopBase*& getShop(void) { return _shop; };
	buttonShop_itemList*& getCurrentButton(void) { return _currentButton; };

	UI_LIST_ITER close(void) override;

public :
	void selectInven(int index);

	void scrollShop(int value);
	void scrollPlayer(int value);

private :
	void scrolling(int value, tagShopContent & target, int maximum);

public:
	windowShop() {};
	~windowShop() {};
};