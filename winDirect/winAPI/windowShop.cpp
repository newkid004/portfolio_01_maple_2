#include "stdafx.h"
#include "windowShop.h"
#include "shopBase.h"

HRESULT windowShop::init(void)
{
	windowBase::init();
	_shop = NULL;

	_conShop.firstItemPos = fPOINT(11, 147);
	_conPlayer.firstItemPos = fPOINT(336, 147);

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