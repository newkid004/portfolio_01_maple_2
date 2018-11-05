#include "stdafx.h"
#include "shopManager.h"

#include "windowBase.h"
#include "shopBase.h"
#include "inventory.h"

HRESULT shopManager::init(void)
{
	_bindWindow = NULL;

	return S_OK;
}

void shopManager::release(void)
{
	for (auto iter = _mShop.begin(); iter != _mShop.end();)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);

		iter = _mShop.erase(iter);
	}
}

shopBase * shopManager::add(string name, shopBase * addition)
{
	shopBase* s = find(name);
	if (s != NULL) return s;

	_mShop.insert(make_pair(name, addition));

	return addition;
}

shopBase * shopManager::find(string name)
{
	auto & iter = _mShop.find(name);
	if (iter == _mShop.end()) return NULL;

	return iter->second;
}

void shopManager::makePlayerView(inventory * inven)
{
	_lPlayerItemView.clear();
	auto & itemArray = inven->getTotalInven();

	for (int y = 0; y < itemArray.size(); ++y)
	{
		for (int x = 0; x < itemArray[y].size(); ++x)
		{
			itemBase* i = itemArray[y][x];
			if (i) _lPlayerItemView.push_back(i);
		}
	}
}
