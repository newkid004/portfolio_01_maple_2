#include "stdafx.h"
#include "windowShop.h"
#include "shopBase.h"

#include "player.h"
#include "inventory.h"

HRESULT windowShop::init(void)
{
	windowBase::init();
	_shop = NULL;

	_conShop.firstItemPos = fPOINT(27.5f, 141.5f);
	_conPlayer.firstItemPos = fPOINT(301.5f, 141.5f);

	return S_OK;
}

void windowShop::render(void)
{
	windowBase::render();

	if (_shop) _shop->render();
}

UI_LIST_ITER windowShop::close(void)
{
	_conShop.scroll = 0;
	_conShop.tabIndex = 0;
	_conPlayer.scroll = 0;
	_conPlayer.tabIndex = 0;

	return windowBase::close();
}

void windowShop::selectInven(int index)
{
	SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(index));
}

void windowShop::scrollShop(int value)
{
	scrolling(
		value, 
		_conShop, 
		_shop->size() - CNT_SHOP_ITEM_LIST);
}

void windowShop::scrollPlayer(int value)
{
	scrolling(
		value, 
		_conPlayer, 
		SHOPMANAGER->getPlayerView().size() - CNT_SHOP_ITEM_LIST);
}

void windowShop::scrolling(int value, tagShopContent & target, int maximum)
{
	target.scroll += value;
	if (maximum < target.scroll) target.scroll = maximum;
	if (target.scroll < 0) target.scroll = 0;
}
