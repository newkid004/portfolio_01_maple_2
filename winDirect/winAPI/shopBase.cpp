#include "stdafx.h"
#include "shopBase.h"

#include "itemBase.h"
#include "windowShop.h"
#include "player.h"
#include "inventory.h"

HRESULT shopBase::init(void)
{
	return S_OK;
}

void shopBase::release(void)
{
	_vItem.clear();
}

void shopBase::update(void)
{
}

void shopBase::render(void)
{
	static windowShop *& winShop = SHOPMANAGER->getWindow();

	IMAGEMANAGER->getTransformState(TF_POSITION);
	renderShop(winShop);
	renderPlayer(winShop);
}

void shopBase::renderShop(windowShop * winShop)
{
	static fPOINT & posOffset = winShop->getPos() + SHOPMANAGER->getWindow()->getContentShop().firstItemPos;

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		itemBase* viewItem = find(i + winShop->getContentShop().scroll);

		if (viewItem)
			viewItem->render2Inventory(posOffset, fPOINT(0, i));
		else
			break;
	}
}

void shopBase::renderPlayer(windowShop * winShop)
{
	static fPOINT & posOffset = winShop->getPos() + SHOPMANAGER->getWindow()->getContentPlayer().firstItemPos;
	static auto & playerItemView = SHOPMANAGER->getPlayerView();

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		int viewIndex = i + winShop->getContentPlayer().scroll;

		if (playerItemView.size() <= viewIndex) return;
		
		itemBase* viewItem = playerItemView[viewIndex];
		viewItem->render2Inventory(posOffset, fPOINT(0, i));
	}
}
