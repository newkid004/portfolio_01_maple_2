#pragma once
#include "gameNode.h"
class buttonWindowTest : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void initImage(void);
	void initWindow(void);
	void initSystem(void);

public :
	buttonWindowTest(){}
	~buttonWindowTest(){}
};

