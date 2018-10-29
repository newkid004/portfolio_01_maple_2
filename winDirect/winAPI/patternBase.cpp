#include "stdafx.h"
#include "patternBase.h"

HRESULT patternBase::init()
{
	return S_OK;
}

void patternBase::update()
{
	//����
	if (_kind == PATTERN_ORDER_CREATE)
	{
		appear();
	}
	//������� ����
	if (_kind == PATTERN_ORDER_RETAIN)
	{
		retain();
	}
	//����
	if (_kind == PATTERN_ORDER_DEAD)
	{
		disappear();
	}
}

void patternBase::appear()
{

}

void patternBase::retain()
{
	if (_order == PATTERN_ORDER_WAIT)
	{

	}
	else if (_order == PATTERN_ORDER_MOVE)
	{

	}
}

void patternBase::disappear()
{
}

void patternBase::release()
{
}