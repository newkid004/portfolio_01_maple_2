#pragma once
#include "buttonBase.h"

class buttonTest : public buttonBase
{
private:
	int _frame;
	
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);

public :
	buttonTest(){}
	~buttonTest(){}
};

