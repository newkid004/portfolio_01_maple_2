#include "stdafx.h"
#include "itemManager.h"

#include "itemBase.h"

HRESULT itemManager::init(void)
{
	initItemList();

	return S_OK;
}

void itemManager::release(void)
{
	for (auto iter = _mItem.begin(); iter != _mItem.end(); ++iter)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
	}
	_mItem.clear();
}

void itemManager::initItemList(void)
{
}

itemBase * itemManager::add(itemBase * addition)
{
	return add(addition->getContent()->name ,addition);
}

itemBase * itemManager::add(wstring name, itemBase * addition)
{
	itemBase* item = find(name);
	if (item != NULL) return item;

	_mItem.insert(make_pair(name, addition));

	return addition;
}

itemBase * itemManager::find(itemBase * item)
{
	return find(item->getContent()->name);
}

itemBase * itemManager::find(wstring name)
{
	auto & iter = _mItem.find(name);
	if (iter == _mItem.end()) return NULL;

	return iter->second;
}

itemBase * itemManager::create(itemBase * viewItem)
{
	itemBase* i = create(viewItem->getContent()->type);
	*i->getContent() = viewItem->getContent();

	return i;
}

itemBase * itemManager::create(int type)
{
	itemBase* createdItem;

	if (false)
		createdItem = new itemBase;
	else
	{
		createdItem = new itemBase;
		createdItem->getContent() = new itemContentBase;
	}

	createdItem->init();
	return createdItem;
}
