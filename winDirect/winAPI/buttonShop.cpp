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
		((windowShop*)_bindWindow)->getCurrentSlotButton() = this;
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

HRESULT buttonShop_itemTab::init(int tabType, windowShop * bindWindow)
{
	_bindWindow = bindWindow;
	_type = tabType;

	// position, bind
	initProp();

	_size = _img->getFrameSize();
	_pos.x += _type * _size.x;

	initActive();

	return S_OK;
}

void buttonShop_itemTab::render(void)
{
	IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
	_img->frameRender(fPOINT(_type, *_bindTab == _type));
}

void buttonShop_itemTab::initProp(void)
{
	_img = IMAGEMANAGER->find("UI_shop_tab_shop");
	_pos = { 10.f, 100.f };

	_bindTab = &((windowShop*)_bindWindow)->getContentShop().tabIndex;
}

void buttonShop_itemTab::initActive(void)
{
	_active = [&](void)->UI_LIST_ITER {
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				*_bindTab = _type;
				return WINMANAGER->getIgnoreIter();
			}
		}
		return _bindWindow->getIter();
	};
}

void buttonShop_playerItemTab::initProp(void)
{
	_img = IMAGEMANAGER->find("UI_shop_tab_player");
	_pos = { 286.f, 100.f };

	_bindTab = &((windowShop*)_bindWindow)->getContentPlayer().tabIndex;
}

void buttonShop_playerItemTab::initActive(void)
{
	_active = [&](void)->UI_LIST_ITER {
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				*_bindTab = _type;
				((windowShop*)_bindWindow)->selectInven(_type);
				return WINMANAGER->getIgnoreIter();
			}
		}
		return _bindWindow->getIter();
	};
}

HRESULT buttonShop_scroll_direction::init(int scroll, windowShop * bindWindow)
{
	_img = IMAGEMANAGER->find("UI_shop_scroll_direction");
	_size = _img->getFrameSize();
	_scroll = scroll;
	_bindWindow = bindWindow;

	initProp();
	if (0 < _scroll) _pos.y += 361.f;

	return S_OK;
}

void buttonShop_scroll_direction::render(void)
{
	IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
	_img->frameRender(fPOINT(
		CNT_SHOP_ITEM_LIST < ((windowShop*)_bindWindow)->getShop()->size(),
		0 < _scroll));
}

void buttonShop_scroll_direction::initProp(void)
{
	static fPOINT interval = { 256.f, 123.f };
	_pos = interval;

	_active = [&](void)->UI_LIST_ITER {
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				((windowShop*)_bindWindow)->scrollShop(_scroll);
				return WINMANAGER->getIgnoreIter();
			}
		}

		return _bindWindow->getIter();
	};
}

void buttonShop_scroll_direction_Player::render(void)
{
	IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
	_img->frameRender(fPOINT(
		CNT_SHOP_ITEM_LIST < SHOPMANAGER->getPlayerView().size(),
		0 < _scroll));
}

void buttonShop_scroll_direction_Player::initProp(void)
{
	static fPOINT interval = { 487.f, 123.f };
	_pos = interval;

	_active = [&](void)->UI_LIST_ITER {
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				((windowShop*)_bindWindow)->scrollPlayer(_scroll);
				return WINMANAGER->getIgnoreIter();
			}
		}

		return _bindWindow->getIter();
	};
}

HRESULT buttonShop_scroll_head::init(buttonBase* buttonTop, buttonBase* buttonBot, windowShop * bindWindow)
{
	_img = IMAGEMANAGER->find("UI_shop_scroll_head");
	_size = _img->getFrameSize();
	_bindWindow = bindWindow;

	_bindButton_top = buttonTop;
	_bindButton_bot = buttonBot;

	return S_OK;
}

UI_LIST_ITER buttonShop_scroll_head::update(void)
{
	_pos.x = _bindButton_top->getPos().x;
	_pos.y = getMinHeight() + (getMaxHeight() - getMinHeight()) * getDividePlace();

	return _bindWindow->getIter();
}

void buttonShop_scroll_head::render(void)
{
	if (_pos.y < 0) return;

	IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
	_img->render();
}

float buttonShop_scroll_head::getDividePlace(void)
{
	if (((windowShop*)_bindWindow)->getShop()->size() - CNT_SHOP_ITEM_LIST <= 0)
		return -1;

	return ((float)((windowShop*)_bindWindow)->getContentShop().scroll) / 
		(((windowShop*)_bindWindow)->getShop()->size() - CNT_SHOP_ITEM_LIST);
}

float buttonShop_scroll_head_Player::getDividePlace(void)
{
	if ((int)SHOPMANAGER->getPlayerView().size() - CNT_SHOP_ITEM_LIST <= 0)
		return -1;

	return ((float)((windowShop*)_bindWindow)->getContentPlayer().scroll) /
		(SHOPMANAGER->getPlayerView().size() - CNT_SHOP_ITEM_LIST);
}
