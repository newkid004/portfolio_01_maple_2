#include "stdafx.h"
#include "windowToolTip.h"

#include "itemBase.h"

HRESULT windowToolTip::init(void)
{
	windowBase::init();

	// frame
	IMAGEMANAGER->add("UI_toolTip_frame_top",	L"image/UI/toolTip/UI_toolTip_frame_top.png");
	IMAGEMANAGER->add("UI_toolTip_frame_bot",	L"image/UI/toolTip/UI_toolTip_frame_bot.png");
	IMAGEMANAGER->add("UI_toolTip_frame_body",	L"image/UI/toolTip/UI_toolTip_frame_body.png");
	IMAGEMANAGER->add("UI_toolTip_frame_dot",	L"image/UI/toolTip/UI_toolTip_frame_dot.png");
	IMAGEMANAGER->add("UI_toolTip_frame_deco",	L"image/UI/toolTip/UI_toolTip_frame_deco.png");
	
	// item icon
	IMAGEMANAGER->add("UI_toolTip_item_base",	L"image/UI/toolTip/UI_toolTip_item_base.png");
	IMAGEMANAGER->add("UI_toolTip_item_deco",	L"image/UI/toolTip/UI_toolTip_item_deco.png");
	IMAGEMANAGER->add("UI_toolTip_item_shadow",	L"image/UI/toolTip/UI_toolTip_item_shadow.png");

	// itemFont : Áß¾Ó Á¤·Ä
	TEXTMANAGER->add("UI_toolTip_head", L"µ¸¿òÃ¼", 16.f)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	_itemIconOffset = { 56.f, 73.f };	// center
	_textMemoOffset = { 97.f, 33.f };	// left top

	_BodyHeight = 0;

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
	wstring & itemMemo = _bindItem->getContent()->memo;

	// ¹ÙÅÁ

	// ¾ÆÀÌÄÜ

	// ±ÛÀÚ
}

void windowToolTip::renderEquip(void)
{
}

void windowToolTip::putBindItem(itemBase * item)
{
	_bindItem = item;
	// _BodyHeight = IMAGEMANAGER->find("");
}
