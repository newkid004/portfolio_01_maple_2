#pragma once
#include "gameNode.h"
#include "player.h"

class playerTestScene : public gameNode
{
	player * _player;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playerTestScene() {}
	~playerTestScene() {}
};

