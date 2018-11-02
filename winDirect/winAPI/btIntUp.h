#pragma once
#include "buttonBase.h"
class btIntUp : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);
	btIntUp(){}
	~btIntUp(){}
};

