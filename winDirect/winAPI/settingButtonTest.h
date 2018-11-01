#pragma once
#include "buttonBase.h"
class settingButtonTest : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);
	settingButtonTest(){}
	~settingButtonTest(){}
};

