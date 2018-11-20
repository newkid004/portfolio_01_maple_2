#include "stdafx.h"
#include "windowToolTip.h"

#include "itemBase.h"

#include "player.h"

HRESULT windowToolTip::init(void)
{
	windowBase::init();

	initImage();
	initFont();
	initImageNumber();

	_itemIconOffset = { 56.f, 73.f };	// center
	_textMemoOffset = { 100.f, 34.f };	// left top

	_bodyHeight = 0;

	return S_OK;
}

void windowToolTip::release(void)
{
	windowBase::release();
}

UI_LIST_ITER windowToolTip::update(void)
{
	list<windowBase*>::iterator iter = _managedIter;
	return ++iter;
}

void windowToolTip::render(void)
{
	if (_bindItem->getContent()->type & itemDef::ITEM_TYPE_EQUIP)
		renderEquip();
	else
		renderNormal();

	close();
}

void windowToolTip::initImage(void)
{
	int refCount = -1;

	// frame
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_top", L"image/UI/toolTip/UI_toolTip_frame_top.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_bot", L"image/UI/toolTip/UI_toolTip_frame_bot.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_body", L"image/UI/toolTip/UI_toolTip_frame_body.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_dot", L"image/UI/toolTip/UI_toolTip_frame_dot.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_deco", L"image/UI/toolTip/UI_toolTip_frame_deco.png");

	// item icon
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_base", L"image/UI/toolTip/UI_toolTip_item_base.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_deco", L"image/UI/toolTip/UI_toolTip_item_deco.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_shadow", L"image/UI/toolTip/UI_toolTip_item_shadow.png");

	IMAGEMANAGER->add("UI_toolTip_equip_class", L"image/UI/toolTip/equip/UI_toolTip_equip_class.png");
	IMAGEMANAGER->add("UI_toolTip_equip_class_text", L"image/UI/toolTip/equip/UI_toolTip_equip_class_text.png", fPOINT(31, 10));
	IMAGEMANAGER->add("UI_toolTip_equip_req", L"image/UI/toolTip/equip/UI_toolTip_equip_req.png", fPOINT(50, 6));
	IMAGEMANAGER->add("UI_toolTip_equip_number", L"image/UI/toolTip/equip/UI_toolTip_equip_number.png", fPOINT(5));
	IMAGEMANAGER->add("UI_toolTip_equip_damage", L"image/UI/toolTip/equip/UI_toolTip_equip_damage.png", fPOINT(20, 26));
}

void windowToolTip::initFont(void)
{
	// itemFont : 굵게, 중앙 정렬
	TEXTMANAGER->add("UI_toolTip_head", L"돋움", 16.f, DWRITE_FONT_WEIGHT_BOLD)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// itemReq : 오른쪽 정렬
	TEXTMANAGER->add("UI_toolTip_equip_req", L"돋움", 12.f)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
}

void windowToolTip::initImageNumber(void)
{
	// 데미지 증가량
	IMGNUMMANAGER->add("UI_toolTip_equip_damage_inc", IMAGEMANAGER->find("UI_toolTip_equip_damage"));
	IMGNUMMANAGER->add("UI_toolTip_equip_damage_dec", IMAGEMANAGER->find("UI_toolTip_equip_damage"), fPOINT(0, 1));

	// 장비 제한
	IMGNUMMANAGER->add("UI_toolTip_equip_req_can",		IMAGEMANAGER->find("UI_toolTip_equip_number"), fPOINT{0, 0}, 0.2f);
	IMGNUMMANAGER->add("UI_toolTip_equip_req_cannot",	IMAGEMANAGER->find("UI_toolTip_equip_number"), fPOINT(0, 1), 0.2f);
	IMGNUMMANAGER->add("UI_toolTip_equip_req_disable",	IMAGEMANAGER->find("UI_toolTip_equip_number"), fPOINT(0, 2), 0.2f);
	IMGNUMMANAGER->add("UI_toolTip_equip_req_yellow",	IMAGEMANAGER->find("UI_toolTip_equip_number"), fPOINT(0, 3), 0.2f);

	if (true) {
		int number[11]; for (int i = 0; i < 11; ++i) number[i] = i;
		float interval[11] = { 19, 14, 18, 17, 20, 16, 18, 18, 19, 19, 18 };
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_damage_inc", number, interval, 11);
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_damage_dec", number, interval, 11);
	} if (true) {
		int number[] = { 1, 7 }; float interval[] = { 2, 4 };
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_req_can", number, interval, 2);
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_req_cannot", number, interval, 2);
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_req_disable", number, interval, 2);
		IMGNUMMANAGER->setInterval("UI_toolTip_equip_req_yellow", number, interval, 2);
	}

}

void windowToolTip::renderNormal(void)
{
	fPOINT offsetPos = point2fpos(_ptMouse);

	if (WINSIZEX < offsetPos.x + _imgRef[0]->getSize().x)
		offsetPos.x += WINSIZEX - (offsetPos.x + _imgRef[0]->getSize().x);
	if (WINSIZEY < offsetPos.y + _totalHeight) 
		offsetPos.y += WINSIZEY - (offsetPos.y + _totalHeight);

	// ----- 바탕 ----- //
	IMAGEMANAGER->statePos(offsetPos);
	IMAGEMANAGER->stateScale(1.f);

	// 바탕 : top
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_TOP]->render();
	IMAGEMANAGER->statePos().y += _imgRef[IT_FRAME_TOP]->getSize().y;

	// 바탕 : body
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(1.f, _bodyHeight);
	_imgRef[IT_FRAME_BODY]->render(1.0f, D2D1_POINT_2F{ 0.f, 0.f });
	IMAGEMANAGER->statePos().y += _bodyHeight;

	// 바탕 : bot
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_BOT]->render();

	// ----- 아이콘 ----- //
	fPOINT offsetIconCenter = offsetPos + _itemIconOffset;
	
	// 아이콘 : base
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_BASE]->getCenterPos());
	_imgRef[IT_ITEM_BASE]->render();

	// 아이콘 : shadow
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_SHADOW]->getCenterPos()).y += 30.f;
	_imgRef[IT_ITEM_SHADOW]->render(0.5f);

	// 아이콘 : item
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(2.f);
	IMAGEMANAGER->statePos(offsetIconCenter - _bindItem->getContent()->img->getCenterFramePos());
	_bindItem->getContent()->img->frameRender(_bindItem->getContent()->frame);

	// 아이콘 : deco
	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_DECO]->getCenterPos());
	_imgRef[IT_ITEM_DECO]->render();

	// ----- 문구 ----- //

	// 문구 : name
	IMAGEMANAGER->statePos(offsetPos.x, offsetPos.y + _imgRef[IT_FRAME_TOP]->getSize().y / 2);
	IMAGEMANAGER->setTransform();
	TEXTMANAGER->setTextColor(&C_COLOR_WHITE);
	TEXTMANAGER->drawText(
		&_bindItem->getContent()->name, 
		&RectF(0, 0,
			_imgRef[IT_FRAME_TOP]->getSize().x, 
			50),
		NULL,
		TEXTMANAGER->find("UI_toolTip_head"));

	// 문구 : memo
	IMAGEMANAGER->statePos(offsetPos + _textMemoOffset);
	IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(
		&_bindItem->getContent()->memo,
		&RectF(0, 0,
			_imgRef[IT_FRAME_TOP]->getSize().x,
			_bodyHeight),
		NULL,
		TEXTMANAGER->find("defaultText"));
}

void windowToolTip::renderEquip(void)
{
	fPOINT offsetPos = point2fpos(_ptMouse);

	if (WINSIZEX < offsetPos.x + _imgRef[0]->getSize().x)
		offsetPos.x += WINSIZEX - (offsetPos.x + _imgRef[0]->getSize().x);
	if (WINSIZEY < offsetPos.y + _totalHeight)
		offsetPos.y += WINSIZEY - (offsetPos.y + _totalHeight);

	// ----- 바탕 ----- //
	IMAGEMANAGER->statePos(offsetPos);
	IMAGEMANAGER->stateScale(1.f);

	// 바탕 : top
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_TOP]->render();
	IMAGEMANAGER->statePos().y += _imgRef[IT_FRAME_TOP]->getSize().y;

	// 바탕 : body
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(1.f, _bodyHeight);
	_imgRef[IT_FRAME_BODY]->render(1.0f, D2D1_POINT_2F{ 0.f, 0.f });
	IMAGEMANAGER->statePos().y += _bodyHeight;

	// 바탕 : bot
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_BOT]->render();

	// ----- 구분선 ----- //
	fPOINT offsetLine = offsetPos; offsetLine.y += 37.f;
	
	// 구분선 : req
	IMAGEMANAGER->statePos(offsetLine);
	_imgRef[IT_FRAME_DOT]->render();

	// 구분선 : info
	IMAGEMANAGER->statePos().y += 124.f;
	_imgRef[IT_FRAME_DOT]->render();

	// ----- 아이콘 ----- //
	fPOINT offsetIconCenter = offsetPos + fPOINT{ 56.f, 90.f };

	// 아이콘 : base
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_BASE]->getCenterPos());
	_imgRef[IT_ITEM_BASE]->render();

	// 아이콘 : shadow
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_SHADOW]->getCenterPos()).y += 30.f;
	_imgRef[IT_ITEM_SHADOW]->render(0.5f);

	// 아이콘 : item
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(2.f);
	IMAGEMANAGER->statePos(offsetIconCenter - _bindItem->getContent()->img->getCenterFramePos());
	_bindItem->getContent()->img->frameRender(_bindItem->getContent()->frame);

	// 아이콘 : deco
	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_DECO]->getCenterPos());
	_imgRef[IT_ITEM_DECO]->render();

	// ----- 제한 ----- //

	// 제한 : 공격력 증가
	static wstring str;
	str = L"공격력 증가량";
	IMAGEMANAGER->statePos(offsetPos + fPOINT(0.f, 45.f));
	IMAGEMANAGER->setTransform();
	TEXTMANAGER->setTextColor(&D2D1::ColorF(0.5f, 0.5f, 0.5f));
	TEXTMANAGER->drawText(
		&str,
		&RectF(0, 0,
			250.f,
			20.f),
		NULL,
		TEXTMANAGER->find("UI_toolTip_equip_req"));

	IMGNUMMANAGER->setCurImgNumber("UI_toolTip_equip_damage_dec");
	IMGNUMMANAGER->drawRight("A987654321234567890", offsetPos + fPOINT(250, 60));

	// 제한 : 레벨, 스텟
	fPOINT offsetReq = IMAGEMANAGER->statePos(offsetPos + fPOINT(100.f, 100.f)); offsetReq.y += 15.f;
	static fPOINT offsetNumber = fPOINT(71, 0);
	static int viewType = 0;
	itemContentEquip* bindContent = (itemContentEquip*)_bindItem->getContent();

	unsigned int* viewPlayer;
	unsigned int* viewReq;
	for (int i = 0; i < 5; ++i)
	{
		switch (i)
		{
		case 0: viewPlayer = &GAMESYSTEM->getPlayer()->getStat().stateLimit.Lv;			viewReq = &bindContent->limit.Lv;		break;
		case 1: viewPlayer = &GAMESYSTEM->getPlayer()->getStat().totalStatePoint.STR;	viewReq = &bindContent->limitPoint.STR; IMAGEMANAGER->statePos(offsetReq); break;
		case 2: viewPlayer = &GAMESYSTEM->getPlayer()->getStat().totalStatePoint.DEX;	viewReq = &bindContent->limitPoint.DEX; IMAGEMANAGER->statePos(offsetReq + fPOINT(0, 9)); break;
		case 3: viewPlayer = &GAMESYSTEM->getPlayer()->getStat().totalStatePoint.INT;	viewReq = &bindContent->limitPoint.INT; IMAGEMANAGER->statePos(offsetReq + fPOINT(80, 0)); break;
		case 4: viewPlayer = &GAMESYSTEM->getPlayer()->getStat().totalStatePoint.LUK;	viewReq = &bindContent->limitPoint.LUK; IMAGEMANAGER->statePos(offsetReq + fPOINT(80, 9)); break;
		}

		// 종류 출력
		viewType = *viewReq == 0 ? 2 : *viewPlayer < *viewReq;
		IMAGEMANAGER->find("UI_toolTip_equip_req")->frameRender(fPOINT(viewType, i));

		// 수치 출력
		IMGNUMMANAGER->setCurImgNumber(
			viewType == 2 ? "UI_toolTip_equip_req_disable" : 
			viewType ? "UI_toolTip_equip_req_cannot" : 
			i == 0 ? "UI_toolTip_equip_req_yellow" : "UI_toolTip_equip_req_can");
		IMGNUMMANAGER->drawRight(viewType == 2 ? "000" : to_string(*viewReq).c_str(), IMAGEMANAGER->statePos() + offsetNumber);
	}

	// 제한 : 직업
	fPOINT offsetClass = IMAGEMANAGER->statePos(offsetLine + fPOINT(12, 97));
	IMAGEMANAGER->find("UI_toolTip_equip_class")->render();

	fPOINT viewFrame;
	viewFrame.x = (int)bindContent->limit.classes & (int)GAMESYSTEM->getPlayer()->getStat().stateLimit.classes ? 1 : 0;
	for (int i = 1; i < 0x10; i <<= 1)
	{
		++viewFrame.y;
		if ((int)bindContent->limit.classes & i)
		{
			switch (i)
			{
			case 1: IMAGEMANAGER->statePos(offsetClass + fPOINT{ 60, 7 });	break;
			case 2: IMAGEMANAGER->statePos(offsetClass + fPOINT{ 93, 7 });	break;
			case 4: IMAGEMANAGER->statePos(offsetClass + fPOINT{ 137, 7 });	break;
			case 8: IMAGEMANAGER->statePos(offsetClass + fPOINT{ 171, 7 });	break;
			}
			IMAGEMANAGER->find("UI_toolTip_equip_class_text")->frameRender(viewFrame);
		}
	}

	// ----- 문구 ----- //
	// 문구 : name
	IMAGEMANAGER->statePos(offsetPos.x, offsetPos.y + _imgRef[IT_FRAME_TOP]->getSize().y / 2);
	IMAGEMANAGER->setTransform();
	TEXTMANAGER->setTextColor(&C_COLOR_WHITE);
	TEXTMANAGER->drawText(
		&_bindItem->getContent()->name,
		&RectF(0, 0,
			_imgRef[IT_FRAME_TOP]->getSize().x,
			50),
		NULL,
		TEXTMANAGER->find("UI_toolTip_head"));

	// 문구 : 정보
	IMAGEMANAGER->statePos(offsetPos + fPOINT(15, 166));
	IMAGEMANAGER->setTransform();
	TEXTMANAGER->setFont("defaultText");
	fPOINT offsetInfo = offsetPos + fPOINT(12, 167); // interval = 15 y
	str = L"장비분류 : ";
	switch (_bindItem->getContent()->type & 0xff)
	{
	case itemDef::ITEM_TYPE_WEAPON: {
	} break;
	case itemDef::ITEM_TYPE_ARMOR: {
		switch (_bindItem->getContent()->kind & 0xff)
		{
		case itemDef::ITEM_KIND_HAT				: str += L"모자"; break;
		case itemDef::ITEM_KIND_GLOVE			: str += L"장갑"; break;
		case itemDef::ITEM_KIND_UPPERCLOTHES	: str += L"상의"; break;
		case itemDef::ITEM_KIND_LOWERCLOTHES	: str += L"하의"; break;
		case itemDef::ITEM_KIND_SHOES			: str += L"신발"; break;
		case itemDef::ITEM_KIND_CAPE			: str += L"망토"; break;
		}
	} break;
	}
	TEXTMANAGER->drawText(&str, &RectF(0, 0, 260, 20)); IMAGEMANAGER->statePos().y += 15.f; IMAGEMANAGER->setTransform();

	// 문구 : 스탯 포인트
	statePoint * refPoint = &((itemContentEquip*)_bindItem->getContent())->point;
	for (int i = 0; i < sizeof(statePoint) / sizeof(int); ++i)
	{
		if (!*((unsigned int*)refPoint + i)) continue;

		switch (i)
		{
		case 0: str = L"STR : "; break;
		case 1: str = L"DEX : "; break;
		case 2: str = L"INT : "; break;
		case 3: str = L"LUK : "; break;
		}
		str += to_wstring(*((unsigned int*)refPoint + i));
		TEXTMANAGER->drawText(&str, &RectF(0, 0, 260, 20)); IMAGEMANAGER->statePos().y += 15.f; IMAGEMANAGER->setTransform();
	}
	
	// 문구 : 기타 능력치
	stateBasic* refState = &((itemContentEquip*)_bindItem->getContent())->basic;
	for (int i = 1; i < sizeof(stateBasic) / sizeof(int) - 1; ++i)
	{
		if (i < 4)	{ if (!*((unsigned int*)refState + i))	continue; }
		else		{ if (!*((NUM_REAL*)refState + i))		continue; }

		switch (i)
		{
		case 1: str = L"Max HP : ";			str += to_wstring(*((unsigned int*)refState + i));	break;
		case 3: str = L"Max MP : ";			str += to_wstring(*((unsigned int*)refState + i));	break;
		case 4: str = L"공격력 : ";			str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		case 5: str = L"마력 : ";			str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		case 6: str = L"물리방어력 : ";		str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		case 7: str = L"마법방어력 : ";		str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		case 8: str = L"이동속도 : ";		str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		case 9: str = L"점프력 : ";			str += to_wstring((int)*((NUM_REAL*)refState + i));	break;
		}
		TEXTMANAGER->drawText(&str, &RectF(0, 0, 260, 20)); IMAGEMANAGER->statePos().y += 15.f; IMAGEMANAGER->setTransform();
	}

	// 문구 : 업그레이드
	IMAGEMANAGER->statePos().y += 15.f;
	IMAGEMANAGER->setTransform();
	str = L"업그레이드 가능 횟수 : " + to_wstring(bindContent->up_max - bindContent->up_count);
	TEXTMANAGER->drawText(&str, &RectF(0, 0, 260, 20));
}

void windowToolTip::setBindItem(itemBase * item)
{
	_bindItem = item;

	if (_bindItem->getContent()->type & itemDef::ITEM_TYPE_EQUIP)
	{
		float lineCount = 2;	// def line : type, upgrade

		itemContentEquip* con = (itemContentEquip*)_bindItem->getContent();

		// basic
		stateBasic* sBasic = &con->basic;
		for (int i = 1; i < sizeof(stateBasic) / sizeof(int) - 1; ++i)
		{
			if (i < 4)	lineCount += 0 < *((unsigned int*)sBasic + i);
			else		lineCount += 0 < *((NUM_REAL*)sBasic + i);
		}

		// point
		statePoint* sPoint = &con->point;
		for (int i = 0; i < sizeof(statePoint) / sizeof(int); ++i)
			lineCount += 0 < *((unsigned int*)sPoint + i);

		_bodyHeight += _imgRef[IT_FRAME_TOP]->getSize().y;
		_bodyHeight += _imgRef[IT_FRAME_BOT]->getSize().y;
		_bodyHeight = 37.f;					// head interval, line;
		_bodyHeight += 154.f;				// equip req
		_bodyHeight += lineCount * 15.f;	// equip status
	}
	else
	{
		float lineCount = std::count(
			item->getContent()->memo.begin(),
			item->getContent()->memo.end(),
			'\n');

		_bodyHeight += _imgRef[IT_FRAME_TOP]->getSize().y;
		_bodyHeight += _imgRef[IT_FRAME_BOT]->getSize().y;
		_bodyHeight = 24.f;					// head interval;
		_bodyHeight += lineCount * 18.f;	// item info

		if (_bodyHeight < INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT)
			_bodyHeight = INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT;
	}
	_totalHeight = _bodyHeight;

	_bodyHeight -= _imgRef[IT_FRAME_TOP]->getSize().y;
	_bodyHeight -= _imgRef[IT_FRAME_BOT]->getSize().y;
}