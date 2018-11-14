#include "stdafx.h"
#include "sceneTestShopInven.h"

#include "itemDef.h"
#include "player.h"
#include "inventory.h"
#include "itemBase.h"
#include "shopBase.h"
#include "windowShop.h"
#include "windowToolTip.h"

#include "windowInventory.h"

static windowShop* winShop;

HRESULT sceneTestShopInven::init(void)
{
	initResource();
	initItem();
	initPlayer();
	initWindow();
	initShop();
	initShortcut();

	return S_OK;
}

void sceneTestShopInven::release(void)
{
}

void sceneTestShopInven::update(void)
{
	// reset
	KEYMANAGER->resetFunctional();

	// start
	GAMESYSTEM->update();
	WINMANAGER->update();

	updateControl();

}

void sceneTestShopInven::render(void)
{
	GAMESYSTEM->render();
	WINMANAGER->render();

	IMAGEMANAGER->statePos(0);
	IMAGEMANAGER->setTransform();

	//shop->ClickRect text
	_renderTarget->DrawRectangle(&RectF(winShop->getResizeClickRect().LT.x, winShop->getResizeClickRect().LT.y,
		winShop->getResizeClickRect().RB.x, winShop->getResizeClickRect().RB.y), TEXTMANAGER->getBrush());

	renderText();
}

void sceneTestShopInven::initResource(void)
{
	IMAGEMANAGER->add("UI_shop_layout", L"image/UI/shop/UI_shop_layout.png");
	IMAGEMANAGER->add("UI_shop_button", L"image/UI/shop/UI_shop_button.png", 4, 3);
	IMAGEMANAGER->add("UI_shop_tab_shop", L"image/UI/shop/UI_shop_tab_shop.png", 2, 2);
	IMAGEMANAGER->add("UI_shop_tab_player", L"image/UI/shop/UI_shop_tab_player.png", 5, 2);
	IMAGEMANAGER->add("UI_shop_selected_shop", L"image/UI/shop/UI_shop_selected_shop.png");
	IMAGEMANAGER->add("UI_shop_selected_player", L"image/UI/shop/UI_shop_selected_player.png");

	IMAGEMANAGER->add("UI_shop_scroll_body", L"image/UI/shop/UI_shop_scroll_body.png");
	IMAGEMANAGER->add("UI_shop_scroll_head", L"image/UI/shop/UI_shop_scroll_head.png");
	IMAGEMANAGER->add("UI_shop_scroll_direction", L"image/UI/shop/UI_shop_scroll_direction.png", 2, 2);

	IMAGEMANAGER->add("UI_meso", L"image/UI/UI_meso.png");
	IMAGEMANAGER->add("UI_checkBox", L"image/UI/UI_checkBox.png", 2);

	IMAGEMANAGER->add("item", L"image/item/icon/item_icon_consume.png", 10, 3);
	IMAGEMANAGER->add("item_shadow", L"image/item/item_shadow.png");

	IMAGEMANAGER->add("UI_inventory", L"image/UI/UI_inventory.png");
}

void sceneTestShopInven::initItem(void)
{
	itemBase* item;

	item = createItem(L"���� ����", L"ü��\n����\nȸ��\n��", fPOINT(0, 0));				item->getContent()->type = itemDef::ITEM_TYPE_ARMOR;		item->getContent()->price = 50;
	item = createItem(L"��Ȳ ����", L"ü\n\n��\n��\n��\n\nȸ\n��\n\n��", fPOINT(50, 0));	item->getContent()->type = itemDef::ITEM_TYPE_ARMOR;		item->getContent()->price = 75;
	item = createItem(L"�Ͼ� ����", L"ü�� ���� ȸ��", fPOINT(100, 0));						item->getContent()->type = itemDef::ITEM_TYPE_CONSUMABLE;	item->getContent()->price = 150;
	item = createItem(L"�Ķ� ����", L"���� ���� ȸ��", fPOINT(150, 0));						item->getContent()->type = itemDef::ITEM_TYPE_CONSUMABLE;	item->getContent()->price = 100;
	item = createItem(L"������", L"ü�� �� ȸ��", fPOINT(200, 0));						item->getContent()->type = itemDef::ITEM_TYPE_FIT;			item->getContent()->price = 700;
	item = createItem(L"���� ������", L"ü�� ���� ȸ��", fPOINT(250, 0));						item->getContent()->type = itemDef::ITEM_TYPE_FIT;			item->getContent()->price = 1000;
	item = createItem(L"���� ������", L"���� ���� ȸ��", fPOINT(300, 0));						item->getContent()->type = itemDef::ITEM_TYPE_ETC;			item->getContent()->price = 2000;
	item = createItem(L"������ ����", L"����", fPOINT(350, 0));						item->getContent()->type = itemDef::ITEM_TYPE_ETC;			item->getContent()->price = 5000;
	item = createItem(L"��ħ �̽�", L"��� ���� �̽�", fPOINT(400, 0));						item->getContent()->type = itemDef::ITEM_TYPE_CACHE;		item->getContent()->price = 60000;
	item = createItem(L"����", L"�޴�", fPOINT(450, 0));						item->getContent()->type = itemDef::ITEM_TYPE_CACHE;		item->getContent()->price = 12000;

	// bind
	ITEMMANAGER->getImgShadow() = IMAGEMANAGER->find("item_shadow");
}

void sceneTestShopInven::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();

	p->getInventory(0)->push(ITEMMANAGER->find(L"������"));

	p->getMoney() = 5000000LL;
}

void sceneTestShopInven::initWindow(void)
{
	// ----- shop ----- //
	winShop = new windowShop;
	winShop->init();
	winShop->getImage() = IMAGEMANAGER->find("UI_shop_layout");
	winShop->getPos() = { 150,100 };

	// inven
	windowInventory* wInven;
	wInven = new windowInventory;	wInven->init();

	wInven->getImage() = IMAGEMANAGER->find("UI_inventory");
	wInven->getPos().x = 900;
	wInven->getPos().y = 100;

	WINMANAGER->add("UI_inventory", wInven);
	WINMANAGER->show(wInven);

	// bind
	SHOPMANAGER->getWindow() = winShop;

	WINMANAGER->add("shop", winShop);

	// ----- toolTip ----- //
	windowToolTip* winToolTip = new windowToolTip;
	winToolTip->init();

	WINMANAGER->add("item_toolTip", winToolTip);
}

void sceneTestShopInven::initShop(void)
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

void sceneTestShopInven::initShortcut(void)
{
	GAMESYSTEM->addShortcut("transShopWindow", 0, [&](void)->void
	{
		if (KEYMANAGER->press('Q'))
			WINMANAGER->trans("shop");

		SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(0));
	});
	GAMESYSTEM->putShortcut("transShopWindow", 'Q');
}

void sceneTestShopInven::updateControl(void)
{
	if (KEYMANAGER->down(VK_UP))	WINMANAGER->find("shop")->getPos().y -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_DOWN))	WINMANAGER->find("shop")->getPos().y += TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_LEFT))	WINMANAGER->find("shop")->getPos().x -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_RIGHT))	WINMANAGER->find("shop")->getPos().x += TIMEMANAGER->getElapsedTime() * 100;

	if (KEYMANAGER->press('1'))		SHOPMANAGER->find("shop")->add(ITEMMANAGER->find(getRandomItemName()));
	if (KEYMANAGER->press('2'))
	{
		GAMESYSTEM->getPlayer()->getInventory(0)->push(
			ITEMMANAGER->create(
				ITEMMANAGER->find(getRandomItemName())
				)
			);
		SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(0));
	}

	if (KEYMANAGER->press('A'))		((windowShop*)WINMANAGER->find("shop"))->scrollShop(-1);
	if (KEYMANAGER->press('Z'))		((windowShop*)WINMANAGER->find("shop"))->scrollShop(+1);
	if (KEYMANAGER->press('S'))		((windowShop*)WINMANAGER->find("shop"))->scrollPlayer(-1);
	if (KEYMANAGER->press('X'))		((windowShop*)WINMANAGER->find("shop"))->scrollPlayer(+1);

}

void sceneTestShopInven::renderText(void)
{
	D2D1_RECT_F rc = { 30, 30, 300, 100 };
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

itemBase * sceneTestShopInven::createItem(wstring name, wstring memo, fPOINT & frame)
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

wstring sceneTestShopInven::getRandomItemName(void)
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
