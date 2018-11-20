#pragma once
#include "gameNode.h"

class player;
class itemBase;

class sceneTestShopInven : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	void initResource(void);
	void initItem(void);
	void initPlayer(void);
	void initWindow(void);
	void initShop(void);
	void initShortcut(void);

	void updateControl(void);

	void renderText(void);

public:
	itemBase* createItem(wstring name, wstring memo, fPOINT & frame);
	wstring getRandomItemName(void);


public:
	sceneTestShopInven(){}
	~sceneTestShopInven(){}
};

