#include "stdafx.h"
#include "sceneTestShop.h"

#include "player.h"
#include "inventory.h"
#include "itemBase.h"
#include "shopBase.h"
#include "windowShop.h"
#include "windowToolTip.h"

static fPOINT pos = fPOINT(150, 100);

HRESULT sceneTestShop::init(void)
{
	initResource();
	initItem();
	initPlayer();
	initWindow();
	initShop();
	initShortcut();

	return S_OK;
}

void sceneTestShop::release(void)
{
}

void sceneTestShop::update(void)
{
	// reset
	KEYMANAGER->resetFunctional();

	// start
	GAMESYSTEM->update();
	WINMANAGER->update();

	updateControl();
}

void sceneTestShop::render(void)
{
	GAMESYSTEM->render();
	WINMANAGER->render();

	renderText();
}

void sceneTestShop::initResource(void)
{
	IMAGEMANAGER->add("UI_shop_layout", L"image/UI/shop/UI_shop_layout.png");
	IMAGEMANAGER->add("UI_meso", L"image/UI/UI_meso.png");

	IMAGEMANAGER->add("item", L"image/item/xcf/item_consume.png", 10, 3);
	IMAGEMANAGER->add("item_shadow", L"image/item/item_shadow.png");
}

void sceneTestShop::initItem(void)
{
	itemBase* item;

	item = createItem(	L"���� ����",		L"ü��\n����\nȸ��\n��",	fPOINT(0,	0));				item->getContent()->type = 1;	item->getContent()->price = 50;
	item = createItem(	L"��Ȳ ����",		L"ü\n\n��\n��\n��\n\nȸ\n��\n\n��",	fPOINT(50,	0));	item->getContent()->type = 1;	item->getContent()->price = 75;
	item = createItem(	L"�Ͼ� ����",		L"ü�� ���� ȸ��",	fPOINT(100,	0));						item->getContent()->type = 1;	item->getContent()->price = 150;
	item = createItem(	L"�Ķ� ����",		L"���� ���� ȸ��",	fPOINT(150,	0));						item->getContent()->type = 1;	item->getContent()->price = 100;
	item = createItem(	L"������",			L"ü�� �� ȸ��",	fPOINT(200,	0));						item->getContent()->type = 1;	item->getContent()->price = 700;
	item = createItem(	L"���� ������",		L"ü�� ���� ȸ��",	fPOINT(250,	0));						item->getContent()->type = 1;	item->getContent()->price = 1000;
	item = createItem(	L"���� ������",		L"���� ���� ȸ��",	fPOINT(300,	0));						item->getContent()->type = 1;	item->getContent()->price = 2000;
	item = createItem(	L"������ ����",		L"����",			fPOINT(350,	0));						item->getContent()->type = 1;	item->getContent()->price = 5000;
	item = createItem(	L"��ħ �̽�",		L"��� ���� �̽�",	fPOINT(400,	0));						item->getContent()->type = 1;	item->getContent()->price = 60000;
	item = createItem(	L"����",			L"�޴�",			fPOINT(450,	0));						item->getContent()->type = 1;	item->getContent()->price = 12000;

	// bind
	ITEMMANAGER->getImgShadow() = IMAGEMANAGER->find("item_shadow");
}

void sceneTestShop::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();

	p->getInventory(0)->push(ITEMMANAGER->find(L"������"));

	p->getMoney() = 5000000LL;
}

void sceneTestShop::initWindow(void)
{
	// ----- shop ----- //
	windowShop* winShop = new windowShop;
	winShop->init();
	winShop->getImage() = IMAGEMANAGER->find("UI_shop_layout");
	winShop->getPos() = { 200, 50 };

	// bind
	SHOPMANAGER->getWindow() = winShop;

	WINMANAGER->add("shop", winShop);

	// ----- toolTip ----- //
	windowToolTip* winToolTip = new windowToolTip;
	winToolTip->init();

	WINMANAGER->add("item_toolTip", winToolTip);
}

void sceneTestShop::initShop(void)
{
	shopBase* shop = new shopBase;
	shop->init();
	shop->add(ITEMMANAGER->find(L"���� ����"));
	shop->add(ITEMMANAGER->find(L"��Ȳ ����"));
	shop->add(ITEMMANAGER->find(L"�Ͼ� ����"));
	shop->add(ITEMMANAGER->find(L"�Ķ� ����"));

	SHOPMANAGER->add("shop", shop);

	windowShop* winShop = (windowShop*)WINMANAGER->find("shop");
	winShop->getShop() = shop;

	SHOPMANAGER->getImageMeso() = IMAGEMANAGER->find("UI_meso");
}

void sceneTestShop::initShortcut(void)
{
	GAMESYSTEM->addShortcut("transShopWindow", 0, [&](void)->void
	{
		if (KEYMANAGER->press('Q')) 
			WINMANAGER->trans("shop");

		SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(0));
	});
	GAMESYSTEM->putShortcut("transShopWindow", 'Q');
}

void sceneTestShop::updateControl(void)
{
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 100;

	if (KEYMANAGER->press('1'))		SHOPMANAGER->find("shop")->add(ITEMMANAGER->find(getRandomItemName()));
	if (KEYMANAGER->press('2'))
	{
		GAMESYSTEM->getPlayer()->getInventory(0)->push(ITEMMANAGER->find(getRandomItemName()));
		SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(0));
	}

	if (KEYMANAGER->press('A'))		((windowShop*)WINMANAGER->find("shop"))->scrollShop(-1);
	if (KEYMANAGER->press('Z'))		((windowShop*)WINMANAGER->find("shop"))->scrollShop(+1);
	if (KEYMANAGER->press('S'))		((windowShop*)WINMANAGER->find("shop"))->scrollPlayer(-1);
	if (KEYMANAGER->press('X'))		((windowShop*)WINMANAGER->find("shop"))->scrollPlayer(+1);

	WINMANAGER->find("shop")->getPos() = pos;
}

void sceneTestShop::renderText(void)
{
	D2D1_RECT_F rc = {30, 30, 300, 100};
	wstring str;

	TEXTMANAGER->setTextColor(&C_COLOR_BLACK);
	IMAGEMANAGER->resetTransform();
	IMAGEMANAGER->setTransform();

	str = L"< �� �� >"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"����Ű : ���� �̵�"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"Q : ���� ������ ����"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"1, 2 : ����, �÷��̾� ������ �߰�"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"A, Z : ���� ��ũ��"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"S, X : �÷��̾� ��ũ��"; TEXTMANAGER->drawText(&str, &rc);
}

itemBase * sceneTestShop::createItem(wstring name, wstring memo, fPOINT & frame)
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

wstring sceneTestShop::getRandomItemName(void)
{
	switch (RND->getInt(10))
	{
	default: return L"���� ����"	;

	case 0 : return L"���� ����"	;
	case 1 : return L"��Ȳ ����"	;
	case 2 : return L"�Ͼ� ����"	;
	case 3 : return L"�Ķ� ����"	;
	case 4 : return L"������"		;
	case 5 : return L"���� ������"	;
	case 6 : return L"���� ������"	;
	case 7 : return L"������ ����"	;	
	case 8 : return L"��ħ �̽�"	;
	case 9 : return L"����"			;	
	}
}
