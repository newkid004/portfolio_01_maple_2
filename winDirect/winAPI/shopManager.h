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

	vector<itemBase*> _vPlayerItemView;
	vector<itemBase*> _vRePurchase;

	image* _imgMeso;

public :
	HRESULT init(void);
	void release(void);

public :
	shopBase * add(string name, shopBase * addition);
	shopBase * find(string name);

	windowShop *& getWindow(void) { return _bindWindow; };
	vector<itemBase*> & getPlayerView(void) { return _vPlayerItemView; };
	vector<itemBase*> & getRePurchase(void) { return _vRePurchase; };

	image* & getImageMeso(void) { return _imgMeso; };

	void makePlayerView(inventory* inven);

public:
	shopManager() {};
	~shopManager() {};
};

