#include "stdafx.h"
#include "shopBase.h"

#include "itemBase.h"
#include "windowShop.h"

HRESULT shopBase::init(void)
{
	return S_OK;
}

void shopBase::release(void)
{
	for (auto i : _vItem)
	{
		i->release();
		SAFE_DELETE(i);
	}
}

void shopBase::update(void)
{
}

void shopBase::render(void)
{
	static windowShop *& winShop = SHOPMANAGER->getWindow();

	IMAGEMANAGER->getTransformState(TF_POSITION);
}

void shopBase::renderShop(windowShop * winShop)
{
	fPOINT & posOffset = winShop->getPos();

	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		itemBase* viewItem = find(i + winShop->getContentShop().scroll);

		if (viewItem)
			viewItem->render2Inventory(posOffset, i);
		else
			break;
	}
}

void shopBase::renderPlayer(windowShop * winShop)
{
	fPOINT & posOffset = winShop->getPos();
}
