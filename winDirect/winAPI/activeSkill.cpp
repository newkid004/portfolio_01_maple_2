#include "stdafx.h"
#include "activeSkill.h"

HRESULT activeSkill::init()
{
	_skillType = skillBase::SKILLTYPE::ACTIVE;
	return S_OK;
}

void activeSkill::release()
{
}

void activeSkill::render()
{
}


//*************************** ������ų ********************************//
HRESULT buffSkill::init()
{
	return S_OK;
}

void buffSkill::release()
{
}

void buffSkill::render()
{
}


//*************************** ���ݽ�ų ********************************//
HRESULT attackSkill::init()
{
	return S_OK;
}

void attackSkill::release()
{
}

void attackSkill::render()
{
}


//*************************** ������ų *******************************//
HRESULT moveSkill::init()
{
	return S_OK;
}

void moveSkill::release()
{
}

void moveSkill::render()
{
}
