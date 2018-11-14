#include "stdafx.h"
#include "windowInventory.h"
#include "shopBase.h"

#include "player.h"
#include "inventory.h"

#include "buttonInventory.h"

#include "itemBase.h"

HRESULT windowInventory::init(void)
{
	windowBase::init();

	initButton();
	return S_OK;
}

UI_LIST_ITER windowInventory::update(void)
{


	return windowMovable::update();
}

void windowInventory::render(void)
{
	windowBase::render();

	POINT pSize = GAMESYSTEM->getPlayer()->getInventory(0)->size();
	for (int i = 0; i < INVENX; ++i)
	{
		for (int j = 0; j < INVENY; ++j)
		{
			int viewIndex = i * INVENY + j;

			if (pSize.x * pSize.y <= viewIndex) return;

			itemBase* viewItem = GAMESYSTEM->getPlayer()->getInventory(0)->find(POINT{ i,j });
			if (viewItem)
				viewItem->render2Inventory(_pos + fPOINT(27, 68) - viewItem->getContent()->img->getCenterFramePos(), fPOINT(i, j));
		}
	}

	renderInfo();
}

void windowInventory::initButton(void)
{
	for (int i = 0; i < INVENX; ++i)
	{
		for (int j = 0; j < INVENY; ++j)
		{
			buttonInventory* b = new buttonInventory;
			b->init(fPOINT(i, j), this);
			addButton("inven_button_" + to_string(i * INVENY + j), b);
		}
	}

	_currentButton = NULL;
}

void windowInventory::renderInfo(void)
{
	static auto & pMoney = GAMESYSTEM->getPlayer()->getMoney();
	static fPOINT interval = { 45.f, 268 };

	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(_pos + interval);
	IMAGEMANAGER->setTransform();

	TEXTMANAGER->setTextColor(&C_COLOR_BLACK);
	wstring str; insertComma(&to_wstring(pMoney), &str);
	TEXTMANAGER->drawText(&str, &RectF(0, 0, 80, 14), NULL,
		TEXTMANAGER->find("defaultText_right"));
}

