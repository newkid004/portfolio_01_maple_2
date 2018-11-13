#include "stdafx.h"
#include "sceneTestInventory.h"

#include "player.h"
#include "inventory.h"
#include "itemBase.h"
#include "windowInventory.h"
#include "windowToolTip.h"

static fPOINT pos = fPOINT(150, 100);

HRESULT sceneTestInventory::init(void)
{
	initImage();
	initWindow();

	initItem();
	initPlayer();
	return S_OK;
}

void sceneTestInventory::release(void)
{
}

void sceneTestInventory::update(void)
{
	GAMESYSTEM->update();
	WINMANAGER->update();
	updateControl();
}

void sceneTestInventory::render(void)
{
	GAMESYSTEM->render();
	WINMANAGER->render();
}

void sceneTestInventory::initImage(void)
{
	IMAGEMANAGER->add("UI_inventory", L"image/UI/UI_inventory.png");

	IMAGEMANAGER->add("item", L"image/item/xcf/item_consume.png", 10, 3);
	IMAGEMANAGER->add("item_shadow", L"image/item/item_shadow.png");
}

void sceneTestInventory::initWindow(void)
{

	windowInventory* wInven;
	wInven = new windowInventory;	wInven->init();

	wInven->getImage() = IMAGEMANAGER->find("UI_inventory");
	wInven->getPos().x = 300;
	wInven->getPos().y = 200;

	WINMANAGER->add("UI_inventory", wInven);
	WINMANAGER->show(wInven);

	// ----- toolTip ----- //
	windowToolTip* winToolTip = new windowToolTip;
	winToolTip->init();

	WINMANAGER->add("item_toolTip", winToolTip);
}

void sceneTestInventory::initItem(void)
{
	itemBase* item;

	item = createItem(L"빨간 포션", L"체력\n조금\n회복\n함", fPOINT(0, 0));				item->getContent()->type = 1;	item->getContent()->price = 50;
	item = createItem(L"주황 포션", L"체\n\n력\n보\n통\n\n회\n복\n\n함", fPOINT(50, 0));	item->getContent()->type = 1;	item->getContent()->price = 75;
	item = createItem(L"하얀 포션", L"체력 많이 회복", fPOINT(100, 0));						item->getContent()->type = 1;	item->getContent()->price = 150;
	item = createItem(L"파란 포션", L"마나 조금 회복", fPOINT(150, 0));						item->getContent()->type = 1;	item->getContent()->price = 100;
	item = createItem(L"엘릭서", L"체력 꽤 회복", fPOINT(200, 0));						item->getContent()->type = 1;	item->getContent()->price = 700;
	item = createItem(L"좋은 엘릭서", L"체력 전부 회복", fPOINT(250, 0));						item->getContent()->type = 1;	item->getContent()->price = 1000;
	item = createItem(L"마나 엘릭서", L"마나 전부 회복", fPOINT(300, 0));						item->getContent()->type = 1;	item->getContent()->price = 2000;
	item = createItem(L"순록의 우유", L"우유", fPOINT(350, 0));						item->getContent()->type = 1;	item->getContent()->price = 5000;
	item = createItem(L"아침 이슬", L"어느 잎의 이슬", fPOINT(400, 0));						item->getContent()->type = 1;	item->getContent()->price = 60000;
	item = createItem(L"수박", L"달다", fPOINT(450, 0));						item->getContent()->type = 1;	item->getContent()->price = 12000;

	// bind
	ITEMMANAGER->getImgShadow() = IMAGEMANAGER->find("item_shadow");
}

void sceneTestInventory::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();

	p->getInventory(0)->push(ITEMMANAGER->find(L"엘릭서"));

	p->getMoney() = 50000000LL;
}

void sceneTestInventory::updateControl(void)
{
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 100;

	if (KEYMANAGER->press('2'))
	{
		GAMESYSTEM->getPlayer()->getInventory(0)->push(ITEMMANAGER->find(ITEMMANAGER->find(getRandomItemName())));
	}


}

itemBase * sceneTestInventory::createItem(wstring name, wstring memo, fPOINT & frame)
{
	static image* itemImage = IMAGEMANAGER->find("item");
	itemBase* item = new itemBase;
	
	item->getContent() = new itemContentBase;
	
	item->getContent()->img = itemImage;
	item->getContent()->name = name;
	item->getContent()->memo = memo;
	item->getContent()->frame = frame / itemImage->getFrameSize();
	
	ITEMMANAGER->add(item);
	
	return item;
}

wstring sceneTestInventory::getRandomItemName(void)
{
	switch (RND->getInt(10))
	{
	default: return L"빨간 포션";

	case 0: return L"빨간 포션";
	case 1: return L"주황 포션";
	case 2: return L"하얀 포션";
	case 3: return L"파란 포션";
	case 4: return L"엘릭서";
	case 5: return L"좋은 엘릭서";
	case 6: return L"마나 엘릭서";
	case 7: return L"순록의 우유";
	case 8: return L"아침 이슬";
	case 9: return L"수박";
	}
}
