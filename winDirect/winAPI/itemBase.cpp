#include "stdafx.h"
#include "itemBase.h"

#include "shopBase.h"

// ----- ItemBase ----- //
void itemBase::render2Field(float alphaRatio)
{
	RENDERMANAGER->add(RO_ITEM, _content->img,
		_position - _content->img->getCenterFramePos(),
		_content->frame,
		_content->img->getFrameSize(),
		alphaRatio);
}

void itemBase::render2shop(fPOINT posOffset, int placement)
{
	posOffset.y += placement * INTERVAL_ITEM_IN_SHOP;

	fPOINT renderPos = posOffset;
	renderPos -= _content->img->getCenterFramePos();
	
	fPOINT textPos = posOffset + fPOINT(22, -17);
	fPOINT mesoPos = posOffset + fPOINT(34, 15);

	// Icon
	IMAGEMANAGER->statePos(renderPos);
	_content->img->frameRender(_content->frameShadow);

	// Name
	D2D1_RECT_F rc = {0, 0, 200, 16};
	IMAGEMANAGER->statePos(textPos); IMAGEMANAGER->setTransform();
	TEXTMANAGER->drawText(&_content->name, &rc);
	
	// Price
	IMAGEMANAGER->statePos(mesoPos - SHOPMANAGER->getImageMeso()->getSize()).y;
	SHOPMANAGER->getImageMeso()->render();
	IMAGEMANAGER->statePos() += fPOINT(SHOPMANAGER->getImageMeso()->getSize().x + 3, -2); IMAGEMANAGER->setTransform();
	wstring strMeso = to_wstring(_content->price);
	wstring strComma; insertComma(&strMeso, &strComma);
	strComma += L" ¸Þ¼Ò";
	TEXTMANAGER->drawText(&strComma, &rc);
}

void itemBase::render2Inventory(fPOINT posOffset, fPOINT placement)
{
	fPOINT renderPos = posOffset + placement * INTERVAL_ITEM_IN_INVENTORY;

	IMAGEMANAGER->statePos(renderPos);
	_content->img->frameRender(_content->frameShadow);
}

// ----- Weapon ----- //
HRESULT itemWeapon::init(void)
{
	_content = new itemContentWeapon();
	return S_OK;
}

void itemWeapon::update(void)
{
}

void itemWeapon::render(void)
{
}

// ----- Armor ----- //
HRESULT itemArmor::init(void)
{
	_content = new itemContentArmor();
	return S_OK;
}

void itemArmor::update(void)
{
}

void itemArmor::render(void)
{
}

