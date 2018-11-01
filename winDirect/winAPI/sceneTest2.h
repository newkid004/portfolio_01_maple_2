#pragma once
#include "gameNode.h"

class playableBase;

struct selectionSlot1
{
	playableBase* pB;
	fPOINT pos;
	int currentFrameY;
	float elapsedTime;
	float updateTime;
};

class sceneTest2 : public gameNode
{
private:
	selectionSlot1 _charater[8];
	fPOINT pos;
	
	int x, y;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	sceneTest2(){}
	~sceneTest2(){}
};

