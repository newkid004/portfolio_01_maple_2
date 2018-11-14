#pragma once
#include "gameNode.h"

class sceneTestWindowStatus : public gameNode
{
public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void initResource(void);
	void initPlayer(void);
	void initWindow(void);

	void updateControl(void);

public:
	sceneTestWindowStatus() {};
	~sceneTestWindowStatus() {};
};

