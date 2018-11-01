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

	// 이미 열렸는지 판별
	windowBase* winBase = iter->second;
	if (winBase->getIter() != _lWindow.end())
	{
		// 이미 열려있음 -> 기존 위치 삭제
		_lWindow.erase(winBase->getIter());
	}

	// 맨 앞에 창 띄움
	_lWindow.push_front(winBase);
	winBase->getIter() = _lWindow.begin();
}

void winManager::show(windowBase * winBase)
{
	show(winBase->getIter());
}

void winManager::show(UI_LIST_ITER & winIter)
{
	// ** 충돌 위험 ** //
	// 맨 앞에 창 삽입 후, 기존 위치 삭제
	_lWindow.push_front(*winIter);
	_lWindow.erase(winIter);
	winIter = _lWindow.begin();
}

UI_LIST_ITER winManager::close(string winName)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	// 이미 닫혔는지 판별
	windowBase* winBase = iter->second;
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

UI_LIST_ITER winManager::close(windowBase * winBase)
{
	return close(winBase->getIter());
}

UI_LIST_ITER winManager::close(UI_LIST_ITER & winIter)
{
	// ** 충돌 위험 ** //
	// 닫고 초기화
	UI_LIST_ITER nextIter = _lWindow.erase(winIter);
	winIter = _lWindow.end();

	return nextIter;
}

UI_LIST_ITER winManager::trans(string winName)
{
	// 목록에 담겨있는지 판별
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	// 열렸는지 판별
	windowBase* winBase = iter->second;
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
