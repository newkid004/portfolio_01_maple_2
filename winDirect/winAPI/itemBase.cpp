#include "stdafx.h"
#include "itemBase.h"

#include "windowShop.h"

#include "player.h"

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
	ITEMMANAGER->getImgShadow()->render();
	_content->img->frameRender(_content->frame);

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
	ITEMMANAGER->getImgShadow()->render();
	_content->img->frameRender(_content->frame);
}

int itemBase::getInventoryTap2type(int type)
{
	if (type & itemDef::ITEM_TYPE_EQUIPMENT)
		return PLAYER_INVENTORY_TAB_EQUIPMENT;
	else if (type & itemDef::ITEM_TYPE_CONSUMABLE)
		return PLAYER_INVENTORY_TAB_CONSUMABLE;
	else if (type & itemDef::ITEM_TYPE_FIT)
		return PLAYER_INVENTORY_TAB_FIT;
	else if (type & itemDef::ITEM_TYPE_ETC)
		return PLAYER_INVENTORY_TAB_ETC;
	else if (type & itemDef::ITEM_TYPE_CACHE)
		return PLAYER_INVENTORY_TAB_CACHE;

	return -1;
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

