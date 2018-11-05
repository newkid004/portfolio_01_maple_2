#pragma once
#include "buttonBase.h"
class btDetails : public buttonBase
{
private:
	int _frameX;
	int _frameY;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);
	btDetails(){}
	~btDetails(){}
};

