#include "stdafx.h"
#include "windowShop.h"
#include "shopBase.h"

#include "player.h"
#include "inventory.h"

#include "buttonShop.h"
#include "buttonCheckBox.h"

#include "itemBase.h"

HRESULT windowShop::init(void)
{
	windowBase::init();
	_shop = NULL;

	_img = IMAGEMANAGER->add("UI_shop_layout", L"image/UI/shop/UI_shop_layout.png");

	_conShop.firstItemPos = fPOINT(27.5f, 141.5f);
	_conPlayer.firstItemPos = fPOINT(301.5f, 141.5f);

	_conShop.selectedItem.x = -1;
	_conPlayer.selectedItem.x = -1;

	initButton();
	initCallback();
	initWheel();

	return S_OK;
}

UI_LIST_ITER windowShop::update(void)
{
	_currentSlotButton = NULL;
	
	fRECT rcAbs = getAbsRect();
	if (this == WINMANAGER->getFocus() && IsClickRect(rcAbs, _ptMouse))
	{
		KEYMANAGER->setWheelUp(GAMESYSTEM->findCallback("UI_shop_scroll_up"), false);
		KEYMANAGER->setWheelDown(GAMESYSTEM->findCallback("UI_shop_scroll_down"), false);
	}

	return windowBase::update();
}

void windowShop::render(void)
{
	windowBase::render();

	// 선택 아이템
	renderSelect();

	// 아이템 목록 render
	if (_shop) _shop->render();

	// 소지금 등
	renderInfo();
}

void windowShop::initButton(void)
{
	// ----- slot ----- //
	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		buttonShop_itemList* b = new buttonShop_itemList;
		b->init(i, this);
		addButton("shop_slot_" + to_string(i), b);
	}
	for (int i = 0; i < CNT_SHOP_ITEM_LIST; ++i)
	{
		buttonShop_playerItemList* b = new buttonShop_playerItemList;
		b->init(i, this);
		addButton("player_slot_" + to_string(i), b);
	}
	_currentSlotButton = NULL;

	// ----- tab ----- //
	for (int i = 0; i <= IMAGEMANAGER->find("UI_shop_tab_shop")->getMaxFrame().x; ++i)
	{
		buttonShop_itemTab* b = new buttonShop_itemTab;
		b->init(i, this);
		addButton("shop_tab_" + to_string(i), b);
	}
	for (int i = 0; i <= IMAGEMANAGER->find("UI_shop_tab_player")->getMaxFrame().x; ++i)
	{
		buttonShop_playerItemTab* b = new buttonShop_playerItemTab;
		b->init(i, this);
		addButton("player_tab_" + to_string(i), b);
	}

	// ----- scroll ----- //
	for (int i = -1; i <= 1; i += 2)
	{
		buttonShop_scroll_direction* b = new buttonShop_scroll_direction;
		b->init(i, this);
		addButton("shop_direction_" + to_string((i + 1) / 2), b);
	}
	for (int i = -1; i <= 1; i += 2)
	{
		buttonShop_scroll_direction_Player* b = new buttonShop_scroll_direction_Player;
		b->init(i, this);
		addButton("player_direction_" + to_string((i + 1) / 2), b);
	}

	for (int i = 0; i < 2; ++i)
	{
		if (i)
		{
			buttonShop_scroll_head* b = new buttonShop_scroll_head;
			b->init(findButton("shop_direction_0"), findButton("shop_direction_1"), this);
			addButton("shop_scroll_head", b);
		}
		else
		{
			buttonShop_scroll_head_Player* b = new buttonShop_scroll_head_Player;
			b->init(findButton("player_direction_0"), findButton("player_direction_1"), this);
			addButton("player_scroll_head", b);
		}
	}

	// ---- right click ----- //
	buttonCheckBox* btnRight = new buttonCheckBox;
	btnRight->init(); btnRight->getPos() = { 249.f, 18.f };
	addButton("shop_isRight", btnRight);
	
	// ----- etc ----- //
	initButtonEtc();
}

void windowShop::initButtonEtc(void)
{
	// button : 상점 나가기
	buttonBaseFrame* btnExit = new buttonBaseFrame;
	btnExit->init(IMAGEMANAGER->find("UI_shop_button"));
	btnExit->getPos() = { 201.f, 53.f };
	btnExit->getActive() = [&](void)->UI_LIST_ITER {

		buttonBaseFrame* btn = (buttonBaseFrame*)findButton("exit");
		if (IsClickRect(btn->getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->up(VK_LBUTTON))
				close();
			else if (KEYMANAGER->press(VK_LBUTTON))
			{
				// 사운드 추가
			}
			else if (KEYMANAGER->down(VK_LBUTTON))
				btn->getCurFrame() = { 2, 0 };
			else
				btn->getCurFrame() = { 1, 0 };
		}
		else
			btn->getCurFrame() = { 0, 0 };

		return _managedIter;
	};
	addButton("exit", btnExit);

	// button : 아이템 구입
	buttonBaseFrame* btnBuy = new buttonBaseFrame;
	btnBuy->init(IMAGEMANAGER->find("UI_shop_button"));
	btnBuy->getPos() = { 201.f, 73.f };
	btnBuy->getActive() = [&](void)->UI_LIST_ITER {

		buttonBaseFrame* btn = (buttonBaseFrame*)findButton("buy");
		if (IsClickRect(btn->getAbsRect(), _ptMouse))
		{
			if (-1 < _conShop.selectedItem.x && KEYMANAGER->up(VK_LBUTTON))
			{
				_currentSlotButton = (buttonShop_itemList*)findButton("shop_slot_" + to_string(_conShop.selectedItem.y - _conShop.scroll));
				if (_currentSlotButton)
					(*GAMESYSTEM->findCallback("UI_shop_button_buy"))();

				return WINMANAGER->getIgnoreIter();
			}
			else if (KEYMANAGER->press(VK_LBUTTON))
			{
				// 사운드 추가
			}
			else if (KEYMANAGER->down(VK_LBUTTON))
				btn->getCurFrame() = { 2, 1 };
			else
				btn->getCurFrame() = { 1, 1 };
		}
		else
			btn->getCurFrame() = { 0, 1 };

		return _managedIter;
	};
	addButton("buy", btnBuy);

	// button : 아이템 판매
	buttonBaseFrame* btnSell = new buttonBaseFrame;
	btnSell->init(IMAGEMANAGER->find("UI_shop_button"));
	btnSell->getPos() = { 433.f, 73.f };
	btnSell->getActive() = [&](void)->UI_LIST_ITER {

		buttonBaseFrame* btn = (buttonBaseFrame*)findButton("sell");
		if (IsClickRect(btn->getAbsRect(), _ptMouse))
		{
			if (-1 < _conPlayer.selectedItem.x && KEYMANAGER->up(VK_LBUTTON))
			{
				// 인벤토리 재정렬
				_conPlayer.tabIndex = _conPlayer.selectedItem.x;
				_conPlayer.scroll = _conPlayer.selectedItem.y;
				SHOPMANAGER->makePlayerView(GAMESYSTEM->getPlayer()->getInventory(_conPlayer.selectedItem.x));

				// 판매
				_currentSlotButton = (buttonShop_itemList*)findButton("player_slot_0");
				(*GAMESYSTEM->findCallback("UI_shop_button_sell"))();

				_conPlayer.selectedItem.x = -1;

				return WINMANAGER->getIgnoreIter();
			}
			else if (KEYMANAGER->press(VK_LBUTTON))
			{
				// 사운드 추가
			}
			else if (KEYMANAGER->down(VK_LBUTTON))
				btn->getCurFrame() = { 2, 2 };
			else
				btn->getCurFrame() = { 1, 2 };
		}
		else
			btn->getCurFrame() = { 0, 2 };

		return _managedIter;
	};
	addButton("sell", btnSell);
}

void windowShop::initCallback(void)
{
	function<void(void)> f;

	// buy
	f = [&](void)->void {
		// 현 상점 슬롯 가져옴
		itemBase* viewItem = _shop->find(_conShop.scroll + _currentSlotButton->getSlot());

		if (viewItem == NULL) return;
		int type = itemBase::getInventoryTap2type(itemBase::getContentType(viewItem));

		// 금액 지불 가능 여부
		__int64 & playerMoney = GAMESYSTEM->getPlayer()->getMoney();
		__int64 & itemPrice = viewItem->getContent()->price;
		if (playerMoney < itemPrice) return;

		// 인벤토리 자리 여부
		inventory* inven = GAMESYSTEM->getPlayer()->getInventory(type);
		if (inven->isFull()) return;

		// 인벤토리 종류 변경
		if (_conPlayer.tabIndex != type)
		{
			_conPlayer.tabIndex = type;
			_conPlayer.scroll = 0;
		}

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
		int scrollMaximum = _conPlayer.scroll + CNT_SHOP_ITEM_LIST;
		if (scrollMaximum <= insertIndex)
			_conPlayer.scroll = insertIndex - CNT_SHOP_ITEM_LIST + 1;
		if (insertIndex < _conPlayer.scroll)
			_conPlayer.scroll = insertIndex;
	};
	GAMESYSTEM->addCallback("UI_shop_button_buy", f);

	// sell
	f = [&](void)->void {
		// 현 플레이어 슬롯에 해당하는 아이템 가져옴
		auto & itemView = SHOPMANAGER->getPlayerView();
		int index = _conPlayer.scroll + _currentSlotButton->getSlot();

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
		if (SHOPMANAGER->getPlayerView().size() <= _conPlayer.scroll + CNT_SHOP_ITEM_LIST)
			scrollPlayer(-1);
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

void windowShop::renderSelect(void)
{
	static fPOINT intervalShop = { 47.f, 124.f };
	static fPOINT intervalPlayer = { 321.f, 124.f };

	int selectedShop	= _conShop.selectedItem.y - _conShop.scroll;
	int selectedPlayer	= _conPlayer.selectedItem.y - _conPlayer.scroll;

	if (_conShop.selectedItem.x == _conShop.tabIndex  &&
		-1 < selectedShop && selectedShop < CNT_SHOP_ITEM_LIST)
	{
		IMAGEMANAGER->statePos(_pos + intervalShop).y += selectedShop * 42.f;
		IMAGEMANAGER->find("UI_shop_selected_shop")->render();
	}

	if (_conPlayer.selectedItem.x == _conPlayer.tabIndex &&
		-1 < selectedPlayer && selectedPlayer < CNT_SHOP_ITEM_LIST)
	{
		IMAGEMANAGER->statePos(_pos + intervalPlayer).y += selectedPlayer * 42.f;
		IMAGEMANAGER->find("UI_shop_selected_player")->render();
	}
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
