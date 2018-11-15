#include "stdafx.h"
#include "windowToolTip.h"

#include "itemBase.h"

HRESULT windowToolTip::init(void)
{
	windowBase::init();

	int refCount = -1;

	// frame
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_top", L"image/UI/toolTip/UI_toolTip_frame_top.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_bot", L"image/UI/toolTip/UI_toolTip_frame_bot.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_body", L"image/UI/toolTip/UI_toolTip_frame_body.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_dot", L"image/UI/toolTip/UI_toolTip_frame_dot.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_frame_deco",	L"image/UI/toolTip/UI_toolTip_frame_deco.png");
	
	// item icon
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_base", L"image/UI/toolTip/UI_toolTip_item_base.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_deco", L"image/UI/toolTip/UI_toolTip_item_deco.png");
	_imgRef[++refCount] = IMAGEMANAGER->add("UI_toolTip_item_shadow",	L"image/UI/toolTip/UI_toolTip_item_shadow.png");

	// itemFont : ����, �߾� ����
	TEXTMANAGER->add("UI_toolTip_head", L"����ü", 16.f, DWRITE_FONT_WEIGHT_BOLD)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

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

void windowToolTip::renderNormal(void)
{
	fPOINT offsetPos = point2fpos(_ptMouse);

	if (WINSIZEX < offsetPos.x + _imgRef[0]->getSize().x)
		offsetPos.x += WINSIZEX - (offsetPos.x + _imgRef[0]->getSize().x);
	if (WINSIZEY < offsetPos.y + _totalHeight) 
		offsetPos.y += WINSIZEY - (offsetPos.y + _totalHeight);

	// ----- ���� ----- //
	IMAGEMANAGER->statePos(offsetPos);
	IMAGEMANAGER->stateScale(1.f);

	// ���� : top
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_TOP]->render();
	IMAGEMANAGER->statePos().y += _imgRef[IT_FRAME_TOP]->getSize().y;

	// ���� : body
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(1.f, _bodyHeight);
	_imgRef[IT_FRAME_BODY]->render(1.0f, D2D1_POINT_2F{ 0.f, 0.f });
	IMAGEMANAGER->statePos().y += _bodyHeight;

	// ���� : bot
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_BOT]->render();

	// ----- ������ ----- //
	fPOINT offsetIconCenter = offsetPos + _itemIconOffset;
	
	// ������ : base
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_BASE]->getCenterPos());
	_imgRef[IT_ITEM_BASE]->render();

	// ������ : shadow
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_SHADOW]->getCenterPos()).y += 30.f;
	_imgRef[IT_ITEM_SHADOW]->render(0.5f);

	// ������ : item
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(2.f);
	IMAGEMANAGER->statePos(offsetIconCenter - _bindItem->getContent()->img->getCenterFramePos());
	_bindItem->getContent()->img->frameRender(_bindItem->getContent()->frame);

	// ������ : deco
	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_DECO]->getCenterPos());
	_imgRef[IT_ITEM_DECO]->render();

	// ----- ���� ----- //

	// ���� : name
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

	// ���� : memo
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

	// ----- ���� ----- //
	IMAGEMANAGER->statePos(offsetPos);
	IMAGEMANAGER->stateScale(1.f);

	// ���� : top
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_TOP]->render();
	IMAGEMANAGER->statePos().y += _imgRef[IT_FRAME_TOP]->getSize().y;

	// ���� : body
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(1.f, _bodyHeight);
	_imgRef[IT_FRAME_BODY]->render(1.0f, D2D1_POINT_2F{ 0.f, 0.f });
	IMAGEMANAGER->statePos().y += _bodyHeight;

	// ���� : bot
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_BOT]->render();

	// ----- ���м� ----- //
	fPOINT offsetLine = offsetPos; offsetLine.y += 37.f;
	
	// ���м� : req
	IMAGEMANAGER->statePos(offsetLine);
	_imgRef[IT_FRAME_DOT]->render();

	// ���м� : info
	IMAGEMANAGER->statePos().y += 147.f;
	_imgRef[IT_FRAME_DOT]->render();

	// ----- ������ ----- //
	fPOINT offsetIconCenter = offsetPos + _itemIconOffset;

	// ������ : base
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_BASE]->getCenterPos());
	_imgRef[IT_ITEM_BASE]->render();

	// ������ : shadow
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_SHADOW]->getCenterPos()).y += 30.f;
	_imgRef[IT_ITEM_SHADOW]->render(0.5f);

	// ������ : item
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(2.f);
	IMAGEMANAGER->statePos(offsetIconCenter - _bindItem->getContent()->img->getCenterFramePos());
	_bindItem->getContent()->img->frameRender(_bindItem->getContent()->frame);

	// ������ : deco
	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_DECO]->getCenterPos());
	_imgRef[IT_ITEM_DECO]->render();

	// ----- ���� ----- //
	// ���� : name
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
}

void windowToolTip::setBindItem(itemBase * item)
{
	_bindItem = item;

	if (_bindItem->getContent()->type & itemDef::ITEM_TYPE_EQUIP)
	{
		float lineCount = 2;	// def line : type, upgrade

		itemContentEquip* con = (itemContentEquip*)_bindItem->getContent();

		// basic
		for (int i = 0; i < sizeof(stateBasic) / sizeof(int) - 1; ++i)
		{
			if (i < 4)	lineCount += 0 < *((unsigned int*)con + i);
			else		lineCount += 0 < *((NUM_REAL*)con + i);
		}

		// point
		for (int i = 0; i < sizeof(statePoint) / sizeof(int); ++i)
			lineCount += 0 < *((unsigned int*)con + i);

		_bodyHeight += _imgRef[IT_FRAME_TOP]->getSize().y;
		_bodyHeight += _imgRef[IT_FRAME_BOT]->getSize().y;
		_bodyHeight = 37.f;					// head interval, line;
		_bodyHeight += 147.f;				// equip req
		_bodyHeight += lineCount * 16.f;	// equip status
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
		_bodyHeight += lineCount * 16.f;	// item info

		if (_bodyHeight < INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT)
			_bodyHeight = INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT;

		_totalHeight = _bodyHeight;

		_bodyHeight -= _imgRef[IT_FRAME_TOP]->getSize().y;
		_bodyHeight -= _imgRef[IT_FRAME_BOT]->getSize().y;
	}
}