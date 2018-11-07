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

	// itemFont : 중앙 정렬
	TEXTMANAGER->add("UI_toolTip_head", L"돋움체", 16.f)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	_itemIconOffset = { 56.f, 73.f };	// center
	_textMemoOffset = { 97.f, 33.f };	// left top

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
	renderNormal();
}

void windowToolTip::renderNormal(void)
{
	fPOINT offsetPos = point2fpos(_ptMouse);

	// ----- 바탕 ----- //
	IMAGEMANAGER->statePos(offsetPos);

	// 바탕 : top
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_TOP]->render();
	IMAGEMANAGER->statePos() += _imgRef[IT_FRAME_TOP]->getSize().y;

	// 바탕 : body
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(1.f, _bodyHeight);
	_imgRef[IT_FRAME_BODY]->render();
	IMAGEMANAGER->statePos() += _bodyHeight;

	// 바탕 : bot
	IMAGEMANAGER->getTransformState(TF_POSITION);
	_imgRef[IT_FRAME_BOT]->render();

	// ----- 아이콘 ----- //
	fPOINT offsetIconCenter = offsetPos + _itemIconOffset;
	
	// 아이콘 : base
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_BASE]->getCenterPos());
	_imgRef[IT_ITEM_BASE]->render();

	// 아이콘 : shadow
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_SHADOW]->getCenterPos());
	_imgRef[IT_ITEM_SHADOW]->render();

	// 아이콘 : item
	IMAGEMANAGER->getTransformState(TF_POSITION | TF_SCALE);
	IMAGEMANAGER->stateScale(2.f);
	IMAGEMANAGER->statePos(offsetIconCenter - _bindItem->getContent()->img->getSize());
	_bindItem->getContent()->img->frameRender(_bindItem->getContent()->frame);

	// 아이콘 : deco
	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(offsetIconCenter - _imgRef[IT_ITEM_DECO]->getCenterPos());
	_imgRef[IT_ITEM_DECO]->render();

	// ----- 글자 ----- //

	// 글자 : name
	IMAGEMANAGER->statePos(offsetPos.x, offsetPos.y + _imgRef[IT_FRAME_TOP]->getSize().y);
	TEXTMANAGER->drawText(
		&_bindItem->getContent()->name, 
		&RectF(0, 0, 
			_imgRef[IT_FRAME_TOP]->getSize().x, 
			_imgRef[IT_FRAME_TOP]->getSize().y),
		NULL,
		TEXTMANAGER->find("UI_toolTip_head"));

	// 글자 : memo
	IMAGEMANAGER->statePos(offsetPos + _textMemoOffset);
	TEXTMANAGER->drawText(
		&_bindItem->getContent()->name,
		&RectF(0, 0,
			_imgRef[IT_FRAME_TOP]->getSize().x,
			_bodyHeight),
		NULL,
		TEXTMANAGER->find("shopText"));
}

void windowToolTip::renderEquip(void)
{
}

void windowToolTip::setBindItem(itemBase * item)
{
	_bindItem = item;

	int lineCount = std::count(
		item->getContent()->memo.begin(),
		item->getContent()->memo.end(),
		'\n');

	_bodyHeight = 24.f;		// head interval;
	_bodyHeight += _imgRef[IT_FRAME_TOP]->getSize().y;
	_bodyHeight += _imgRef[IT_FRAME_BOT]->getSize().y;
	_bodyHeight += _bodyHeight * 16.f;

	if (_bodyHeight < INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT)
		_bodyHeight = INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT;

	_bodyHeight -= _imgRef[IT_FRAME_TOP]->getSize().y;
	_bodyHeight -= _imgRef[IT_FRAME_BOT]->getSize().y;
}
