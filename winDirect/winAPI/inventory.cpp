#include "stdafx.h"
#include "inventory.h"

#include "itemBase.h"

HRESULT inventory::init(void)
{
	_vInventory.resize(INVEN_SIZE_HEGIHT);
	for (auto & inven : _vInventory)
		inven.resize(INVEN_SIZE_WIDTH, NULL);

	_front = { 0, 0 };

	return S_OK;
}

void inventory::release(void)
{
	for (auto & inven : _vInventory)
		inven.clear();
	_vInventory.clear();
}

void inventory::update(void)
{
}

void inventory::render(void)
{
}

itemBase * inventory::push(itemBase * item, POINT pos)
{
	if (pos.x <= -1 || pos.y <= -1)
		pos = _front;

	_vInventory[pos.y][pos.x] = item;

	if (pos.x == _front.x && pos.y == _front.y)
		resetFront();

	return item;
}

itemBase * inventory::pop(POINT pos)
{
	itemBase* item = find(pos);
	_vInventory[pos.y][pos.x] = NULL;

	if (pos.y < _front.y)		_front = pos;
	else if (pos.x < _front.x)	_front = pos;

	return item;
}

itemBase * inventory::find(POINT pos)
{
	if (_vInventory.size() <= pos.y) return NULL;
	if (_vInventory[pos.y].size() <= pos.x) return NULL;

	return _vInventory[pos.y][pos.x];
}

void inventory::resize(POINT size)
{
	if (_vInventory.size() < size.y)	{ _vInventory.resize(size.y); _vInventory[size.y - 1].resize(size.x, NULL); }
	if (_vInventory[0].size() < size.x)
	{
		for (int i = 0; i < size.x; ++i)
			_vInventory[i].resize(size.x, NULL);
	}

	// 크기 변경 후, 앞 대상 재배치
	if (0 < _front.y)
	{ 
		_front.y = 0; 
		resetFront(); 
	}
}

// ----- private ----- //
void inventory::resetFront(void)
{
	for (; _front.y < _vInventory.size(); ++_front.y)
	{
		auto & inven = _vInventory[_front.y];
		for (_front.x = 0; _front.x < inven.size(); ++_front.x)
		{
			if (inven[_front.x] == NULL)
				return;
		}
	}
}
