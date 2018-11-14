#include "stdafx.h"
#include "windowStatus.h"

#include "eventBase.h"
#include "eventCatcher.h"

#include "buttonBase.h"

#include "player.h"
#include "characterBase.h"
#include "state.h"

HRESULT windowStatus::init(void)
{
	_img = IMAGEMANAGER->find("UI_status_layout_begin");
	_size = _img->getSize();

	_bindWindow = (windowStatusDetail*)WINMANAGER->add("status_detail", new windowStatusDetail);
	_bindWindow->init(this);

	initEventCatcher();
	initButton();

	return S_OK;
}

void windowStatus::render(void)
{
	windowBase::render();

	renderInfo();
}

void windowStatus::initEventCatcher(void)
{
	eventCatcher* e = new eventCatcher; e->init();
	e->getParam() = makeDestParam(
		ET_PLAYER |
		EK_PLAYER_NONE |
		EA_PLAYER_STATUS_LEVEL |
		EC_PLAYER_STATUS_CHANGE_INCREASE);

	e->getAfterActive() = new eventCatcherActive;
	*e->getAfterActive() = [this](eventBase* e)->void {
		// 조건 : 전직 || 10 < level
		if (10 <= ((player*)e->getDest())->getStat().stateLimit.Lv)
		{
			((windowStatus*)WINMANAGER->find("status"))->getImage() = IMAGEMANAGER->find("UI_status_layout");
			findButton("stat_STR")->getImage() = IMAGEMANAGER->find("UI_increase");
			findButton("stat_DEX")->getImage() = IMAGEMANAGER->find("UI_increase");
			findButton("stat_INT")->getImage() = IMAGEMANAGER->find("UI_increase");
			findButton("stat_LUK")->getImage() = IMAGEMANAGER->find("UI_increase");
		}
		else
			((windowStatus*)WINMANAGER->find("status"))->getImage() = IMAGEMANAGER->find("UI_status_layout_begin");

		++GAMESYSTEM->getPlayer()->getStatPoint();
	};
	EVENTMANAGER->getEventCatcherArray(e->getParam()).push_back(e);
}

void windowStatus::initButton(void)
{
	buttonBaseFrame* b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_status_button_detail"));
	b->getPos() = { 132.f, 286.f };
	b->getActive() = [this](void)->UI_LIST_ITER {
		buttonBaseFrame* btn = (buttonBaseFrame*)findButton("show_detail");

		btn->getCurFrame().x = _bindWindow->isShow();
		if (IsClickRect(btn->getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->up(VK_LBUTTON))
			{
				_bindWindow->trans();
				return WINMANAGER->getIgnoreIter();
			}
			else if (KEYMANAGER->press(VK_LBUTTON))
			{
				// 사운드 추가
			}
			else if (KEYMANAGER->down(VK_LBUTTON))
				btn->getCurFrame().y = 2.f;
			else
				btn->getCurFrame().y = 1.f;
		}
		else
			btn->getCurFrame().y = 0.f;

		return _managedIter;
	};
	addButton("show_detail", b);

	// ----- stat ----- //
	// 0 : HP	,	1 : MP
	// 2 : STR	,	3 : DEX
	// 4 : INT	,	5 : LUK
	static fPOINT offset = { 187.f, 121.f };
	static player* & p = GAMESYSTEM->getPlayer();
	static function<UI_LIST_ITER(int, buttonBaseFrame*)> buttonActive = [this](int statType, buttonBaseFrame* btn)->UI_LIST_ITER {
		if (!p->getStatPoint())
			btn->getCurFrame().x = 3.f;
		else
		{
			if (IsClickRect(btn->getAbsRect(), _ptMouse))
			{
				if (KEYMANAGER->up(VK_LBUTTON))
				{
					switch (statType)
					{
					case 0: p->getBasicStat().maxHp += 10; break;
					case 1: p->getBasicStat().maxMp += 10; break;
					case 2: ++p->getStat().permanentPoint.STR; break;
					case 3: ++p->getStat().permanentPoint.DEX; break;
					case 4: ++p->getStat().permanentPoint.INT; break;
					case 5: ++p->getStat().permanentPoint.LUK; break;
					}

					--p->getStatPoint();
					return WINMANAGER->getIgnoreIter();
				}
				else if (KEYMANAGER->press(VK_LBUTTON))
				{
					// 사운드 추가
				}
				else if (KEYMANAGER->down(VK_LBUTTON))
					btn->getCurFrame().x = 1.f;
				else
					btn->getCurFrame().x = 2.f;
			}
			else
				btn->getCurFrame().x = 0.f;
		}
		return _managedIter;
	};

	// HP
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase"));
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER { return buttonActive(0, (buttonBaseFrame*)findButton("stat_HP")); };
	addButton("stat_HP", b);

	offset.y += 18.f;
	// MP
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase"));
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER { return buttonActive(1, (buttonBaseFrame*)findButton("stat_MP")); };
	addButton("stat_MP", b);

	offset.y += 69.f;
	// STR
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase")); b->getImage() = NULL;
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER {return buttonActive(2, (buttonBaseFrame*)findButton("stat_STR")); };
	addButton("stat_STR", b);

	offset.y += 18.f;
	// DEX
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase")); b->getImage() = NULL;
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER {return buttonActive(3, (buttonBaseFrame*)findButton("stat_DEX")); };
	addButton("stat_DEX", b);

	offset.y += 18.f;
	// INT
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase")); b->getImage() = NULL;
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER {return buttonActive(4, (buttonBaseFrame*)findButton("stat_INT")); };
	addButton("stat_INT", b);

	offset.y += 18.f;
	// LUK
	b = new buttonBaseFrame;
	b->init(IMAGEMANAGER->find("UI_increase")); b->getImage() = NULL;
	b->getPos() = offset;
	b->getActive() = [this](void)->UI_LIST_ITER {return buttonActive(5, (buttonBaseFrame*)findButton("stat_LUK")); };
	addButton("stat_LUK", b);
}

void windowStatus::renderInfo(void)
{
	static player* p = GAMESYSTEM->getPlayer();
	static auto drawRect = RectF(0, 0, 130, 14);

	wstring str;
	fPOINT offset = _pos + fPOINT( 72.f, 30.f );

	TEXTMANAGER->setFont("statusText");

	// ----- normal ----- //
	// 이름

	offset.y += 18.f;
	// 직업

	offset.y += 18.f;
	// 길드 - 비구현

	offset.y += 18.f;
	// 인기도 - 비구현

	offset.y += 18.f;
	// 스탯 공격력

	offset.y += 18.f;
	// HP
	str = to_wstring(p->getBasicStat().hp) + L" / " + to_wstring(p->getBasicStat().maxHp);
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	offset.y += 18.f;
	// MP
	str = to_wstring(p->getBasicStat().mp) + L" / " + to_wstring(p->getBasicStat().maxMp);
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	// begin image : block
	if (p->getStat().stateLimit.Lv < 10) return;

	offset.y = _pos.y + 207.f;
	// ----- stat ----- //
	// str
	str = to_wstring(p->getStat().permanentPoint.STR + p->getStat().itemStatePoint.STR) +
		L" (" + to_wstring(p->getStat().permanentPoint.STR) +
		L"+" + to_wstring(p->getStat().itemStatePoint.STR) + L")";
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	offset.y += 18.f;
	// dex
	str = to_wstring(p->getStat().permanentPoint.DEX + p->getStat().itemStatePoint.DEX) +
		L" (" + to_wstring(p->getStat().permanentPoint.DEX) +
		L"+" + to_wstring(p->getStat().itemStatePoint.DEX) + L")";
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	offset.y += 18.f;
	// int
	str = to_wstring(p->getStat().permanentPoint.INT + p->getStat().itemStatePoint.INT) +
		L" (" + to_wstring(p->getStat().permanentPoint.INT) +
		L"+" + to_wstring(p->getStat().itemStatePoint.INT) + L")";
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	offset.y += 18.f;
	// luk
	str = to_wstring(p->getStat().permanentPoint.LUK + p->getStat().itemStatePoint.LUK) +
		L" (" + to_wstring(p->getStat().permanentPoint.LUK) +
		L"+" + to_wstring(p->getStat().itemStatePoint.LUK) + L")";
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);

	offset = _pos + fPOINT(72.f, 180.f);
	// 남은 어빌리티 포인트
	str = to_wstring(p->getStatPoint());
	IMAGEMANAGER->statePos(offset); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&str, &drawRect);
}

void windowStatus::show(void)
{
	WINMANAGER->show(this);
	if (_isOpenedDetail)
		_bindWindow->show();
}

UI_LIST_ITER windowStatus::close(void)
{
	_isOpenedDetail = _bindWindow->isShow();
	_bindWindow->close();

	return WINMANAGER->close(this);
}

void windowStatusDetail::render(void)
{
	_pos = _bindWindow->getPos();
	_pos.x += _bindWindow->getSize().x + 1;

	windowBase::render();

	static player* p = GAMESYSTEM->getPlayer();
	static auto drawRect = RectF(0, 0, 130, 14);

	wstring str;
	fPOINT offset = _pos + fPOINT(72.f, 42.f);

	TEXTMANAGER->setFont("statusText");

	// 스텟 공격력

	offset.y += 18.f;
	// 데미지

	offset.y += 18.f;
	// 최종 데미지

	offset.y += 18.f;
	// 크리티컬 발동

	offset.y += 18.f;
	// 크리 데미지

	offset.y += 18.f;
	// 상태이상 내성

	offset.y += 18.f;
	// 방어력

	offset.y += 18.f;
	// 이동속도

	offset.y += 18.f;
	// 스타포스

	offset = _pos + fPOINT(168.f, 60.f);
	// 보스 데미지

	offset.y += 18.f;
	// 방어율 무시

	offset.y += 54.f;
	// 스탠스

	offset.y += 36.f;
	// 점프력
}
