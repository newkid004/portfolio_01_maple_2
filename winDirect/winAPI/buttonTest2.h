#pragma once
#include "buttonBase.h"

class buttonTest2 : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);

	buttonTest2(){}
	~buttonTest2(){}
};

