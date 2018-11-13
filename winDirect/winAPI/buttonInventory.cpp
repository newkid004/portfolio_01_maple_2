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

	_pos = fPOINT(11, 52) + fPOINT(36,35) * pos;
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
	static inventory* & pInventory = GAMESYSTEM->getPlayer()->getInventory(0);

	return 	pInventory->find(PointMake(_slotX, _slotY));
}
