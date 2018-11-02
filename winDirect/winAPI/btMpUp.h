#pragma once
#include "buttonBase.h"
class btMpUp : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);
	btMpUp(){}
	~btMpUp(){}
};

