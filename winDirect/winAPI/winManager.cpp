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

	// normal
	for (; iter != _lWindow.end(); )
	{
		iter = (*iter)->update();
	} 

	// always
	iter = _lWindow.begin();
	for (; iter != _lWindow.end(); ++iter)
		(*iter)->updateAlways();
}

void winManager::render(void)
{
	auto iter = _lWindow.rbegin();

	while (iter != _lWindow.rend())
	{
		(*iter)->render();
		auto baseIter = iter.base();
		
		if (baseIter == _lWindow.begin())
			break;

		++iter;
	}
}

windowBase * winManager::add(string winName, windowBase * winAdd)
{
	// ��Ͽ� ����ִ��� �Ǻ�
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
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return;

	show(iter->second);
}

void winManager::show(windowBase * winBase)
{
	// �� ������ â �̵�
	_lWindow.push_front(winBase);

	// �����ִ��� �Ǻ�
	if (winBase->getIter() == _lWindow.end())
	{
		// ��������
		winBase->getIter() = _lWindow.begin();
	}
	else
	{
		// ��������
		_lWindow.erase(winBase->getIter());
	}

	// �� ���� iterator ����
	winBase->getIter() = _lWindow.begin();
}

UI_LIST_ITER winManager::close(string winName)
{
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	return close(iter->second);
}

UI_LIST_ITER winManager::close(windowBase * winBase)
{
	// �̹� �������� �Ǻ�
	if (winBase->getIter() == _lWindow.end())
	{
		// �̹� �������� -> ����
		return _lWindow.end();
	}

	// �ݰ� �ʱ�ȭ
	UI_LIST_ITER nextIter = _lWindow.erase(winBase->getIter());
	winBase->getIter() = _lWindow.end();

	return nextIter;
}

UI_LIST_ITER winManager::trans(string winName)
{
	// ��Ͽ� ����ִ��� �Ǻ�
	auto iter = _mWindow.find(winName);
	if (iter == _mWindow.end()) return _lWindow.end();

	return trans(iter->second);
}

UI_LIST_ITER winManager::trans(windowBase * winBase)
{
	// ���ȴ��� �Ǻ�
	if (winBase->isShow())
	{
		// �������� -> ����
		winBase->close();
	}
	else
	{
		// �������� -> ����
		winBase->show();
	}

	return winBase->getIter();
}
