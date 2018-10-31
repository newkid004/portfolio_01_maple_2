#pragma once
#include "buttonBase.h"

class buttonTest : public buttonBase
{
private:
	
public:
	HRESULT init(void);

	list<windowBase*>::iterator* update(void);
	void render(fPOINT & offset);
	buttonTest(){}
	~buttonTest(){}
};

