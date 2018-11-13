#include "stdafx.h"
#include "buttonShop.h"

#include "windowShop.h"
#include "windowToolTip.h"

#include "shopBase.h"

HRESULT buttonShop_itemList::init(int slot, windowShop* bindWindow)
{
	_bindWindow = bindWindow;

	_slot = slot;
	
	initPosition(bindWindow);
	_pos.y += INTERVAL_ITEM_IN_SHOP * _slot;

	return S_OK;
}

UI_LIST_ITER buttonShop_itemList::update(void)
{
	if (IsClickRect(getAbsRect(), _ptMouse))
	{
		((windowShop*)_bindWindow)->getCurrentButton() = this;
		updateDbClick();
	}
	
	return _bindWindow->getIter();
}

void buttonShop_itemList::render(void)
{
	if (IsClickRect(getAbsRect(), _ptMouse))
	{
		windowToolTip* winTT = (windowToolTip*)WINMANAGER->find("item_toolTip");
		itemBase* viewItem = getRenderContent();

		if (viewItem)
		{
			winTT->setBindItem(viewItem);
			winTT->show();
		}
	}
}

void buttonShop_itemList::initPosition(windowShop* bindWindow)
{
	_pos = bindWindow->getContentShop().firstItemPos - 16.5f;
	_size = { 243.f, 33.f };
}

itemBase * buttonShop_itemList::getRenderContent(void)
{
	windowShop* bindWindow = (windowShop*)_bindWindow;
	shopBase* bindShop = bindWindow->getShop();

	return bindShop->find(_slot + bindWindow->getContentShop().scroll);
}

void buttonShop_playerItemList::initPosition(windowShop * bindWindow)
{
	_pos = bindWindow->getContentPlayer().firstItemPos - 16.5f;
	_size = { 201.f, 33.f };
}

itemBase * buttonShop_playerItemList::getRenderContent(void)
{
	static vector<itemBase*> & playerItemView = SHOPMANAGER->getPlayerView();

	windowShop* bindWindow = (windowShop*)_bindWindow;
	int index = _slot + bindWindow->getContentPlayer().scroll;

	if (playerItemView.size() <= index) return NULL;

	return playerItemView[_slot + bindWindow->getContentPlayer().scroll];
}
