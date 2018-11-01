#pragma once
#include "gameNode.h"

class sceneWindowTest : public gameNode
{
public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void initWindow(void);

public:
	sceneWindowTest() {};
	~sceneWindowTest() {};
};

