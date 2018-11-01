#pragma once
#include "gameNode.h"
class buttonWindowTest : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void initWindow(void);

	buttonWindowTest(){}
	~buttonWindowTest(){}
};

