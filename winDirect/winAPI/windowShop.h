#pragma once
#include "windowBase.h"

// ¹öÆ° : 38°³

#define CNT_SHOP_ITEM_LIST 9

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
class windowShop : public windowBase
{
private:
	tagShopContent _conShop;
	tagShopContent _conPlayer;
	shopBase* _shop;

public:
	HRESULT init(void);
	void render(void);

public :
	void selectInven(int index);

public:
	tagShopContent & getContentShop(void) { return _conShop; };
	tagShopContent & getContentPlayer(void) { return _conPlayer; };
	shopBase*& getShop(void) { return _shop; };

	UI_LIST_ITER close(void) override;

public:
	windowShop() {};
	~windowShop() {};
};