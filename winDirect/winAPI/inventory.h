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
	void update(void);
	void render(void);

public :
	itemBase* push(itemBase* item, POINT pos = {-1, -1});	// defalt : front
	itemBase* pop(POINT pos);
	itemBase* find(POINT pos);

	void resize(POINT size);

private :
	void resetFront(void);

public :
	inventory() {};
	~inventory() {};
};