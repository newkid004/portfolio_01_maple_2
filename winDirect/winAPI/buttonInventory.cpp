#include "stdafx.h"
#include "buttonInventory.h"

#include "windowInventory.h"
#include "windowToolTip.h"

#include "player.h"
#include "inventory.h"

HRESULT buttonInventory::init(fPOINT pos, windowInventory * bindWindow)
{
	_slotX = pos.x;
	_slotY = pos.y;

	_bindWindow = bindWindow;


	//11 ,52 가로 세로
	//36 ,35 거리 거리

	_pos = fPOINT(11, 52) + fPOINT(36, 35) * pos;
	_size = fPOINT(32.f);
	return S_OK;
}

UI_LIST_ITER buttonInventory::update(void)
{
	if (IsClickRect(getAbsRect(), _ptMouse))
	{
		((windowInventory*)_bindWindow)->getCurrentButton() = this;
		updateDbClick();
	}

	return _bindWindow->getIter();
}

void buttonInventory::render(void)
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


itemBase * buttonInventory::getRenderContent(void)
{
	inventory* & pInventory = GAMESYSTEM->getPlayer()->getInventory(((windowInventory*)_bindWindow)->getTabIndex());

	return 	pInventory->find(PointMake(_slotX, _slotY));
}


//========= itemTab ==========

HRESULT buttonInvenTab::init(int tabType, windowInventory * bindWindow)
{
	_bindWindow = bindWindow;
	_type = tabType;

	// position, bind
	initProp();

	_size = _img->getFrameSize();
	_pos.x += _type * (_size.x + 1);

	initActive();

	return S_OK;
}

void buttonInvenTab::render(void)
{
	IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
	_img->frameRender(fPOINT(_type, _bindContent->tabIndex == _type));
}

void buttonInvenTab::initProp(void)
{
	_img = IMAGEMANAGER->find("UI_inventory_tab");
	_pos = { 9.f, 26.f };

	_bindContent = &((windowInventory*)_bindWindow)->getContentInven();
}

void buttonInvenTab::initActive(void)
{
	_active = [&](void)->UI_LIST_ITER {
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				_bindContent->tabIndex = _type;
				((windowInventory*)_bindWindow)->selectInven(_type);
				return WINMANAGER->getIgnoreIter();
			}
		}
		return _bindWindow->getIter();
	};
}

//=================== meso =========================

HRESULT buttonInvenMeso::init(void)
{
	_img = IMAGEMANAGER->find("UI_button_meso");

	_active = [&](void)->UI_LIST_ITER {WINMANAGER->trans("setting"); return _bindWindow->getIter(); };

	_size = _img->getFrameSize();
	_pos = { 9,268 };

	_frame = 0;

	return S_OK;
}

UI_LIST_ITER buttonInvenMeso::update(void)
{
	fRECT rc;
	rc.LT = _pos + _bindWindow->getPos();
	rc.RB = rc.LT + _size;

	if (IsClickRect(rc, _ptMouse))
	{
		if (KEYMANAGER->up(VK_LBUTTON))
			/*return _active()*/;
		else if (KEYMANAGER->down(VK_LBUTTON))
			_frame = 2;
		else
			_frame = 1;
	}
	else
		_frame = 0;


	return _bindWindow->getIter();
}

void buttonInvenMeso::render(void)
{
	IMAGEMANAGER->getTransformState() = TF_POSITION;
	IMAGEMANAGER->statePos(_pos + _bindWindow->getPos());
	_img->frameRender(0, _frame);
}
