#include "stdafx.h"
#include "luckySeven.h"

HRESULT luckySeven::init()
{
	_cooltime = 0;						//쿨타임

	_isBuff = false;					//버프인지 아닌지의 여부

	return S_OK;
}

void luckySeven::release()
{
}

void luckySeven::render()
{
}
