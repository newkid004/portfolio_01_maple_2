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

	POINT selectedItem;		// x : tab, y : scroll

	tagShopContent()
	{
		scroll = 0;
		tabIndex = 0;
		selectedItem = { 0L };
	}
};

class shopBase;
class buttonShop_itemList;
class windowShop : public windowBase
{
private:
	tagShopContent _conShop;
	tagShopContent _conPlayer;
	shopBase* _shop;

	buttonShop_itemList* _currentSlotButton;

public:
	HRESULT init(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

protected :
	void initButton(void);
	void initButtonEtc(void);

	void initCallback(void);
	void initWheel(void);

	void renderSelect(void);
	void renderInfo(void);

public:
	tagShopContent & getContentShop(void) { return _conShop; };
	tagShopContent & getContentPlayer(void) { return _conPlayer; };
	shopBase*& getShop(void) { return _shop; };
	buttonShop_itemList*& getCurrentSlotButton(void) { return _currentSlotButton; };

public :	// 
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