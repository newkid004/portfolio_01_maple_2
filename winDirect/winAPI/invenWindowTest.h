#pragma once
#include "gameNode.h"
class invenWindowTest : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void initWindow(void);
	invenWindowTest(){}
	~invenWindowTest(){}
};

