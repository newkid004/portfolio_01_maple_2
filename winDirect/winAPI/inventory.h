#pragma once

class itemBase;

class inventory
{
private :
	set<POINT, itemBase*> _mInventory;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	inventory() {};
	~inventory() {};
};