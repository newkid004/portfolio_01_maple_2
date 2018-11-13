#pragma once
#include "gameNode.h"

class player;
class itemBase;

class sceneTestInventory : public gameNode
{
private:
	player* _player;
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void initImage(void);
	void initWindow(void);

	void initItem(void);
	void initPlayer(void);
	void updateControl(void);

public:
	itemBase* createItem(wstring name, wstring memo, fPOINT & frame);
	wstring getRandomItemName(void);

	sceneTestInventory(){}
	~sceneTestInventory(){}
};

