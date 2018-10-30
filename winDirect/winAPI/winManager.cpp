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
	for (auto iter = _lWindow.begin(); iter != _lWindow.end();)
	{
		auto nextIter = (*iter)->update();
		
		if (nextIter)
			iter = *nextIter;
		else
			++iter;
	}
}

void winManager::render(void)
{
	UI_LIST::reverse_iterator iter = _lWindow.rbegin();
	for (; iter != _lWindow.rend(); ++iter)
	{
		(*iter)->render();
	}
}

windowBase * winManager::add(string winName, windowBase * winAdd)
{
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter != _mWindow.end()) return iter->second;

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
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return;

	// �̹� ���ȴ��� �Ǻ�
	windowBase* winBase = iter->second;
	if (winBase->getIter() != NULL)
	{
		// �̹� �������� -> ���� ��ġ ����
		_lWindow.erase(*winBase->getIter());
	}

	// �� �տ� â ���
	_lWindow.push_front(winBase);
	winBase->getIter() = &_lWindow.begin();
}

void winManager::show(windowBase * winBase)
{
	show(winBase->getIter());
}

void winManager::show(UI_LIST_ITER *& winIter)
{
	// ** �浹 ���� ** //
	// �� �տ� â ���� ��, ���� ��ġ ����
	_lWindow.push_front(**winIter);
	_lWindow.erase(*winIter);
	winIter = &_lWindow.begin();
}

winManager::UI_LIST_ITER*  winManager::close(string winName)
{
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return NULL;

	// �̹� �������� �Ǻ�
	windowBase* winBase = iter->second;
	if (winBase->getIter() == NULL)
	{
		// �̹� �������� -> ����
		return NULL;
	}

	// �ݰ� �ʱ�ȭ
	winManager::UI_LIST_ITER* nextIter = &_lWindow.erase(*winBase->getIter());
	winBase->getIter() = NULL;

	return nextIter;
}

winManager::UI_LIST_ITER* winManager::close(windowBase * winBase)
{
	return close(winBase->getIter());
}

winManager::UI_LIST_ITER* winManager::close(UI_LIST_ITER *& winIter)
{
	// ** �浹 ���� ** //
	// �ݰ� �ʱ�ȭ
	auto nextIter = &_lWindow.erase(*winIter);
	winIter = NULL;

	return nextIter;
}
