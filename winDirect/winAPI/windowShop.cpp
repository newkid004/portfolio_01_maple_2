#include "stdafx.h"
#include "windowShop.h"
#include "shopBase.h"

#include "player.h"
#include "inventory.h"

#include "buttonShop.h"

#include "itemBase.h"


HRESULT windowShop::init(void)
{
	windowMovable::init();
	
	_shop = NULL;

	_conShop.firstItemPos = fPOINT(27.5f, 141.5f);
	_conPlayer.firstItemPos = fPOINT(301.5f, 141.5f);

	initButton();
	initDbClick();
	initWheel();

	return S_OK;
}

UI_LIST_ITER windowShop::update(void)
{
	_currentButton = NULL;
	
	fRECT rcAbs = getAbsRect();
	if (IsClickRect(rcAbs, _ptMouse))
	{
		KEYMANAGER->setWheelUp(GAMESYSTEM->findCallback("UI_shop_scroll_up"), false);
		KEYMANAGER->setWheelDown(GAMESYSTEM->findCallback("UI_shop_scroll_down"), false);
	}
	
	return windowMovable::update();
}

void windowShop::render(void)
{
	windowBase::render();

	// 아이템 목록 render
	if (_shop) _shop->render();

	// 소지금 등
	renderInfo();
	
}

void windowShop::initButton(void)
{
	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		buttonShop_itemList* b = new buttonShop_itemList;
		b->init(i, this);
		addButton("shop_button_" + to_string(i), b);
	}
	
	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		buttonShop_playerItemList* b = new buttonShop_playerItemList;
		b->init(i, this);
		addButton("player_button_" + to_string(i), b);
	}

	_currentButton = NULL;
}

void windowShop::initDbClick(void)
{
	function<void(void)> f;

	// buy
	f = [&](void)->void {
		// 현 상점 슬롯 가져옴
		itemBase* viewItem = _shop->find(_conShop.scroll + _currentButton->getSlot());

		if (viewItem == NULL) return;
		int type = itemBase::getInventoryTap2type(itemBase::getContentType(viewItem));

		// 금액 지불 가능 여부
		__int64 & playerMoney = GAMESYSTEM->getPlayer()->getMoney();
		__int64 & itemPrice = viewItem->getContent()->price;
		if (playerMoney < itemPrice) return;

		// 인벤토리 자리 여부
		inventory* inven = GAMESYSTEM->getPlayer()->getInventory(type);
		if (inven->isFull()) return;

		// 아이템 추가 / 금액 지불
		itemBase* addition = ITEMMANAGER->create(viewItem);
		addition->getContent() = viewItem->getContent();
		inven->push(addition);

		playerMoney -= itemPrice;

		// 상점 플레이어 슬롯 아이템 재정렬
		SHOPMANAGER->makePlayerView(inven);

		// 스크롤 재정렬
		int insertIndex = 0;
		for (itemBase* i : SHOPMANAGER->getPlayerView())
		{
			if (i == addition)
				break;

			++insertIndex;
		}
		int scrollMaximum = _conPlayer.scroll + CNT_SHOP_ITEM_LIST - 1;
		if (insertIndex < _conPlayer.scroll)
			_conPlayer.scroll = insertIndex;
		if (scrollMaximum < insertIndex)
			scrollPlayer(scrollMaximum);
	};
	GAMESYSTEM->addCallback("UI_shop_button_buy", f);

	// sell
	f = [&](void)->void {
		// 현 플레이어 슬롯에 해당하는 아이템 가져옴
		auto & itemView = SHOPMANAGER->getPlayerView();
		int index = _conPlayer.scroll + _currentButton->getSlot();

		if (itemView.size() <= index) return;
		itemBase* viewItem = itemView[index];

		if (viewItem == NULL) return;

		// 인벤토리에서 아이템 가져옴
		inventory* inven = GAMESYSTEM->getPlayer()->getInventory(_conPlayer.tabIndex);
		itemBase* takedItem = inven->pop(viewItem);

		if (takedItem == NULL) return;

		// 상점 플레이어 슬롯 아이템 제외, 재판매에 등록
		itemView.erase(itemView.begin() + index);
		SHOPMANAGER->getRePurchase().push_back(takedItem);

		// 아이템 판매 / 금액 획득
		GAMESYSTEM->getPlayer()->getMoney() += takedItem->getContent()->price / 2;

		// 스크롤 재정렬
		scrollPlayer(SHOPMANAGER->getPlayerView().size() - CNT_SHOP_ITEM_LIST);
	};
	GAMESYSTEM->addCallback("UI_shop_button_sell", f);
}

void windowShop::initWheel(void)
{
	static fRECT rangeShop(fPOINT{ 7, 119 }, fPOINT{ 255, 495 });
	static fRECT rangePlayer(fPOINT{ 281, 119 }, fPOINT{ 486, 495 });

	function<void(void)> f;

	f = [&](void)->void {
		fRECT viewShop = rangeShop + _pos;
		fRECT viewPlayer = rangePlayer + _pos;
		if (IsClickRect(viewShop, _ptMouse))	scrollShop(-1);
		if (IsClickRect(viewPlayer, _ptMouse))	scrollPlayer(-1);
	};
	GAMESYSTEM->addCallback("UI_shop_scroll_up", f);

	f = [&](void)->void {
		fRECT viewShop = rangeShop + _pos;
		fRECT viewPlayer = rangePlayer + _pos;
		if (IsClickRect(viewShop, _ptMouse))	scrollShop(1);
		if (IsClickRect(viewPlayer, _ptMouse))	scrollPlayer(1);
	};
	GAMESYSTEM->addCallback("UI_shop_scroll_down", f);
}

void windowShop::renderInfo(void)
{
	static auto & pMoney = GAMESYSTEM->getPlayer()->getMoney();
	static fPOINT interval = { 415.f, 54.f };

	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(_pos + interval);
	IMAGEMANAGER->setTransform();

	TEXTMANAGER->setTextColor(&C_COLOR_BLACK);
	wstring str; insertComma(&to_wstring(pMoney), &str);
	TEXTMANAGER->drawText(&str, &RectF(0, 0, 80, 14), NULL, 
		TEXTMANAGER->find("defaultText_right"));
}

UI_LIST_ITER windowShop::close(void)
{
	_conShop.scroll = 0;
	_conShop.tabIndex = 0;
	_conPlayer.scroll = 0;
	_conPlayer.tabIndex = 0;

	return windowBase::close();
}

void windowShop::selectInven(int index)
{
	SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(index));
}

void windowShop::scrollShop(int value)
{
	scrolling(
		value, 
		_conShop, 
		_shop->size() - CNT_SHOP_ITEM_LIST);
}

void windowShop::scrollPlayer(int value)
{
	scrolling(
		value, 
		_conPlayer, 
		SHOPMANAGER->getPlayerView().size() - CNT_SHOP_ITEM_LIST);
}

void windowShop::scrolling(int value, tagShopContent & target, int maximum)
{
	target.scroll += value;
	if (maximum < target.scroll) target.scroll = maximum;
	if (target.scroll < 0) target.scroll = 0;
}
