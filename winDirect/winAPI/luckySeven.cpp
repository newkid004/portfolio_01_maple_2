#include "stdafx.h"
#include "luckySeven.h"

HRESULT luckySeven::init()
{
	_cooltime = 0;						//��Ÿ��

	_isBuff = false;					//�������� �ƴ����� ����

	return S_OK;
}

void luckySeven::release()
{
}

void luckySeven::render()
{
}
