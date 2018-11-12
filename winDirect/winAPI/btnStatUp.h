#pragma once
#include "buttonBase.h"
class btnStatUp : public buttonBase
{
protected:
	int _frame;
public:
	HRESULT init(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;
public:
	btnStatUp(){}
	~btnStatUp(){}
};



