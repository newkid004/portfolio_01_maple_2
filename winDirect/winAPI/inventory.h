#pragma once

#define INVEN_SIZE_WIDTH	4
#define INVEN_SIZE_HEGIHT	6

class itemBase;

class inventory
{
private :
	typedef vector<vector<itemBase*>> INVEN_ARRAY;

private :
	INVEN_ARRAY _vInventory;
	POINT _front;

public :
	HRESULT init(void);
	void release(void);

public :
	itemBase* push(itemBase* item, POINT pos = {-1, -1});	// defalt : front
	itemBase* pop(itemBase* item) { return pop(findItemPos(item)); };
	itemBase* pop(POINT pos);
	itemBase* find(POINT pos);
	
	bool isFull(void) { return( _vInventory.size() == _front.y) && (_vInventory[0].size() == _front.x); };
	POINT size(void) { return POINT{ (long)_vInventory[0].size(), (long)_vInventory.size() }; };
	void resize(POINT size);

	vector<vector<itemBase*>> & getTotalInven(void) { return _vInventory; };

private :
	void resetFront(void);
	POINT findItemPos(itemBase* item);

public :
	inventory() {};
	~inventory() {};
};