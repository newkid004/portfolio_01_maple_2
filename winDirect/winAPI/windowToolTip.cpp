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

	// itemFont : 굵게, 중앙 정렬
	TEXTMANAGER->add("UI_toolTip_head", L"돋움체", 16.f, DWRITE_FONT_WEIGHT_BOLD)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

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

	// ----- 글자 ----- //

	// 글자 : name
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

	// 글자 : memo
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
}

void windowToolTip::setBindItem(itemBase * item)
{
	_bindItem = item;

	float lineCount = std::count(
		item->getContent()->memo.begin(),
		item->getContent()->memo.end(),
		'\n');

	_bodyHeight = 24.f;		// head interval;
	_bodyHeight += _imgRef[IT_FRAME_TOP]->getSize().y;
	_bodyHeight += _imgRef[IT_FRAME_BOT]->getSize().y;
	_bodyHeight += lineCount * 16.f;

	if (_bodyHeight < INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT)
		_bodyHeight = INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT;

	_totalHeight = _bodyHeight;

	_bodyHeight -= _imgRef[IT_FRAME_TOP]->getSize().y;
	_bodyHeight -= _imgRef[IT_FRAME_BOT]->getSize().y;

}
