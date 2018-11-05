#pragma once
#define INTERVAL_ITEM_IN_SHOP 50.f

class itemBase;

class shopBase
{
private :
	vector<itemBase*> _vItem;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

protected :
	virtual void renderShop(windowShop* winShop);
	virtual void renderPlayer(windowShop* winShop);

public :
	void add(itemBase* addition) { _vItem.push_back(addition); };
	itemBase * find(int index) { return _vItem.size() <= index ? NULL : _vItem[index]; };
	int size(void) { return _vItem.size(); };

public:
	shopBase()  {};
	~shopBase() {};
};

