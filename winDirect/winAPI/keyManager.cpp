#include "stdafx.h"
#include "keyManager.h"

HRESULT keyManager::init()
{
	_inputKey = NULL;

	//키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	_callWheelUp = NULL;
	_callWheelDown = NULL;
	_callDBClick = NULL;

	return S_OK;
}

void keyManager::release(void)
{
	if (_callWheelUp != NULL) SAFE_DELETE(_callWheelUp);
	if (_callWheelDown != NULL) SAFE_DELETE(_callWheelDown);
}

bool keyManager::press(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}

	return false;
}

bool keyManager::up(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}

	return false;
}

bool keyManager::down(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool keyManager::toggle(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

void keyManager::setWheelUp(function<void(void)> * upFunction, bool isDelete)
{
	if (isDelete) if (_callWheelUp) SAFE_DELETE(_callWheelUp);
	_callWheelUp = upFunction;
}

void keyManager::setWheelDown(function<void(void)> * downFunction, bool isDelete)
{
	if (isDelete) if (_callWheelDown) SAFE_DELETE(_callWheelDown);
	_callWheelDown = downFunction;
}

void keyManager::setDBClick(function<void(void)>* dbClickFunction, bool isDelete)
{
	if (isDelete) if (_callDBClick)SAFE_DELETE(_callDBClick);
	_callDBClick = dbClickFunction;
}

void keyManager::resetFunctional(bool isDelete)
{
	if (isDelete)
	{
		SAFE_DELETE(_callWheelUp);
		SAFE_DELETE(_callWheelDown);
		SAFE_DELETE(_callDBClick);
	}
	else
	{
		_callWheelUp = NULL;
		_callWheelDown = NULL;
		_callDBClick = NULL;
	}
}
