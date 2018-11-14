#include "stdafx.h"
#include "sceneTestInventory.h"

#include "player.h"
#include "inventory.h"
#include "itemBase.h"
#include "windowInventory.h"
#include "windowToolTip.h"

static fPOINT pos = fPOINT(900, 100);

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
	wInven->getPos().x = pos.x;
	wInven->getPos().y = pos.y;

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

	item = createItem(L"���� ����", L"ü��\n����\nȸ��\n��", fPOINT(0, 0));				item->getContent()->type = 1;	item->getContent()->price = 50;
	item = createItem(L"��Ȳ ����", L"ü\n\n��\n��\n��\n\nȸ\n��\n\n��", fPOINT(50, 0));	item->getContent()->type = 1;	item->getContent()->price = 75;
	item = createItem(L"�Ͼ� ����", L"ü�� ���� ȸ��", fPOINT(100, 0));						item->getContent()->type = 1;	item->getContent()->price = 150;
	item = createItem(L"�Ķ� ����", L"���� ���� ȸ��", fPOINT(150, 0));						item->getContent()->type = 1;	item->getContent()->price = 100;
	item = createItem(L"������", L"ü�� �� ȸ��", fPOINT(200, 0));						item->getContent()->type = 1;	item->getContent()->price = 700;
	item = createItem(L"���� ������", L"ü�� ���� ȸ��", fPOINT(250, 0));						item->getContent()->type = 1;	item->getContent()->price = 1000;
	item = createItem(L"���� ������", L"���� ���� ȸ��", fPOINT(300, 0));						item->getContent()->type = 1;	item->getContent()->price = 2000;
	item = createItem(L"������ ����", L"����", fPOINT(350, 0));						item->getContent()->type = 1;	item->getContent()->price = 5000;
	item = createItem(L"��ħ �̽�", L"��� ���� �̽�", fPOINT(400, 0));						item->getContent()->type = 1;	item->getContent()->price = 60000;
	item = createItem(L"����", L"�޴�", fPOINT(450, 0));						item->getContent()->type = 1;	item->getContent()->price = 12000;

	// bind
	ITEMMANAGER->getImgShadow() = IMAGEMANAGER->find("item_shadow");
}

void sceneTestInventory::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();

	p->getInventory(0)->push(ITEMMANAGER->find(L"������"));

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
	default: return L"���� ����";

	case 0: return L"���� ����";
	case 1: return L"��Ȳ ����";
	case 2: return L"�Ͼ� ����";
	case 3: return L"�Ķ� ����";
	case 4: return L"������";
	case 5: return L"���� ������";
	case 6: return L"���� ������";
	case 7: return L"������ ����";
	case 8: return L"��ħ �̽�";
	case 9: return L"����";
	}
}
