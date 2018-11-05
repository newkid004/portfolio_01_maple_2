#pragma once
#include "singletonBase.h"

class windowShop;
class shopBase;
class inventory;
class itemBase;

class shopManager : public singletonBase<shopManager>
{
private :
	windowShop * _bindWindow;
	unordered_map<string, shopBase*> _mShop;

	vector<itemBase*> _lPlayerItemView;

public :
	HRESULT init(void);
	void release(void);

public :
	shopBase * add(string name, shopBase * addition);
	shopBase * find(string name);

	windowShop *& getWindow(void) { return _bindWindow; };
	vector<itemBase*> & getPlayerView(void) { return _lPlayerItemView; };

	void makePlayerView(inventory* inven);

public:
	shopManager() {};
	~shopManager() {};
};

