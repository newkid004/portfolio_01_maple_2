#pragma once
#include "buttonBase.h"
class buttonTest3 : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);
	buttonTest3() {}
	~buttonTest3() {}
};

