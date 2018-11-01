#include "stdafx.h"
#include "winManager.h"
#include "windowBase.h"


HRESULT winManager::init(void)
{
	return S_OK;
}

void winManager::release(void)
{
	_lWindow.clear();
	for (auto iter = _mWindow.begin(); iter != _mWindow.end(); ++iter)
	{
		windowBase * winView = iter->second;
		
		winView->release();
		SAFE_DELETE(winView);
	}
}

void winManager::update(void)
{
	auto iter = _lWindow.begin();

	for (; iter != _lWindow.end(); )
	{
		iter = (*iter)->update();
	} 

}

void winManager::render(void)
{
	auto iter = _lWindow.rbegin();
	for (; iter != _lWindow.rend(); ++iter)
	{
		(*iter)->render();
	}
}

windowBase * winManager::add(string winName, windowBase * winAdd)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter != _mWindow.end()) return iter->second;

	winAdd->getIter() = _lWindow.end();
	winAdd->getName() = winName;

	_mWindow.insert(make_pair(winName, winAdd));

	return winAdd;
}

windowBase * winManager::find(string winName)
{
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	return iter->second;
}

void winManager::show(string winName)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return;

	show(iter->second);
}

void winManager::show(windowBase * winBase)
{
	// 맨 앞으로 창 이동
	_lWindow.push_front(winBase);

	// 닫혀있는지 판별
	if (winBase->getIter() == _lWindow.end())
	{
		// 닫혀있음
		winBase->getIter() = _lWindow.begin();
	}
	else
	{
		// 열려있음
		_lWindow.erase(winBase->getIter());
	}

	// 맨 앞의 iterator 삽입
	winBase->getIter() = _lWindow.begin();
}

UI_LIST_ITER winManager::close(string winName)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	return close(iter->second);
}

UI_LIST_ITER winManager::close(windowBase * winBase)
{
	// 이미 닫혔는지 판별
	if (winBase->getIter() == _lWindow.end())
	{
		// 이미 닫혀있음 -> 나감
		return _lWindow.end();
	}

	// 닫고 초기화
	UI_LIST_ITER nextIter = _lWindow.erase(winBase->getIter());
	winBase->getIter() = _lWindow.end();

	return nextIter;
}

UI_LIST_ITER winManager::trans(string winName)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	return trans(iter->second);
}

UI_LIST_ITER winManager::trans(windowBase * winBase)
{
	// 열렸는지 판별
	if (winBase->isShow())
	{
		// 열려있음 -> 닫음
		winBase->close();
	}
	else
	{
		// 닫혀있음 -> 열림
		winBase->show();
	}

	return winBase->getIter();
}
