#pragma once
#include "activeSkill.h"
class luckySeven : public activeSkill
{

public:
	HRESULT	init();
	void release();
	void render();
	luckySeven(){}
	~luckySeven(){}
};

