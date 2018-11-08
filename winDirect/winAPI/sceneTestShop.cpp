#include "stdafx.h"
#include "sceneTestShop.h"

#include "player.h"
#include "inventory.h"
#include "itemBase.h"
#include "shopBase.h"
#include "windowShop.h"

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
	
	IMAGEMANAGER->add("item", L"image/item/xcf/item_consume.png", 10, 6);
}

void sceneTestShop::initItem(void)
{
	itemBase* item;

	item = createItem(	L"빨간 포션",		L"체력 조금 회복",	fPOINT(0,	50)); item->getContent()->price = 50;
	item = createItem(	L"주황 포션",		L"체력 보통 회복",	fPOINT(50,	50)); item->getContent()->price = 75;
	item = createItem(	L"하얀 포션",		L"체력 많이 회복",	fPOINT(100,	50)); item->getContent()->price = 150;
	item = createItem(	L"파란 포션",		L"마나 조금 회복",	fPOINT(150,	50)); item->getContent()->price = 100;
	item = createItem(	L"엘릭서",			L"체력 꽤 회복",		fPOINT(200,	50)); item->getContent()->price = 700;
	item = createItem(	L"좋은 엘릭서",		L"체력 전부 회복",	fPOINT(250,	50)); item->getContent()->price = 1000;
	item = createItem(	L"마나 엘릭서",		L"마나 전부 회복",	fPOINT(300,	50)); item->getContent()->price = 800;
	item = createItem(	L"우유",			L"우유",				fPOINT(350,	50)); item->getContent()->price = 500;
	item = createItem(	L"아침 이슬",		L"어느 잎의 이슬",	fPOINT(400,	50)); item->getContent()->price = 600;
	item = createItem(	L"수박",			L"달다",				fPOINT(450,	50)); item->getContent()->price = 1200;
}

void sceneTestShop::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();

	p->getInventory(0)->push(ITEMMANAGER->find(L"엘릭서"));
}

void sceneTestShop::initWindow(void)
{
	windowShop* winShop = new windowShop;
	winShop->init();
	winShop->getImage() = IMAGEMANAGER->find("UI_shop_layout");
	winShop->getPos() = { 200, 50 };

	// bind
	SHOPMANAGER->getWindow() = winShop;

	WINMANAGER->add("shop", winShop);
}

void sceneTestShop::initShop(void)
{
	shopBase* shop = new shopBase;
	shop->init();
	shop->add(ITEMMANAGER->find(L"빨간 포션"));
	shop->add(ITEMMANAGER->find(L"주황 포션"));
	shop->add(ITEMMANAGER->find(L"하얀 포션"));
	shop->add(ITEMMANAGER->find(L"파란 포션"));

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

	IMAGEMANAGER->resetTransform();
	IMAGEMANAGER->setTransform();

	str = L"< 조 작 >"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"방향키 : 상점 이동"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"Q : 상점 윈도우 열기"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"1, 2 : 상점, 플레이어 아이템 추가"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"A, Z : 상점 스크롤"; TEXTMANAGER->drawText(&str, &rc); IMAGEMANAGER->statePos().y += 30; IMAGEMANAGER->setTransform();
	str = L"S, X : 플레이어 스크롤"; TEXTMANAGER->drawText(&str, &rc);
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
	item->getContent()->frameShadow = (frame - fPOINT(0, itemImage->getFrameSize().y)) / itemImage->getFrameSize();

	ITEMMANAGER->add(item);

	return item;
}

wstring sceneTestShop::getRandomItemName(void)
{
	switch (RND->getInt(10))
	{
	default: return L"빨간 포션"	;

	case 0 : return L"빨간 포션"	;
	case 1 : return L"주황 포션"	;
	case 2 : return L"하얀 포션"	;
	case 3 : return L"파란 포션"	;
	case 4 : return L"엘릭서"		;
	case 5 : return L"좋은 엘릭서"	;
	case 6 : return L"마나 엘릭서"	;
	case 7 : return L"우유"			;	
	case 8 : return L"아침 이슬"	;
	case 9 : return L"수박"			;	
	}
}
