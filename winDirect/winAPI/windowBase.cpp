#include "stdafx.h"
#include "windowBase.h"
#include "winManager.h"

#include "buttonBase.h"

// ----- Window Base ----- //
HRESULT windowBase::init(void)
{
	_img = NULL;
	_managedIter = WINMANAGER->getIgnoreIter();

	return S_OK;
}

void windowBase::release(void)
{
	for (auto i = _mButton.begin(); i != _mButton.end();)
	{
		SAFE_DELETE(i->second);
		i = _mButton.erase(i);
	}
}

UI_LIST_ITER windowBase::update(void)
{
	UI_LIST_ITER viewIter;
	for (auto i = _mButton.begin(); i != _mButton.end(); ++i)
	{
		viewIter = i->second->update();
		if (viewIter == WINMANAGER->getIgnoreIter())
			return viewIter;
	}

	// 윈도우 내 마우스 클릭
	if (KEYMANAGER->down(VK_LBUTTON))
	{
		fRECT rc(_pos, _pos + _img->getSize());
		if (IsClickRect(rc, _ptMouse))
		{
			// 윈도우를 맨 앞으로 / 뒷 창 무시
			this->show();

			return WINMANAGER->getIgnoreIter();
		}
	}

	list<windowBase*>::iterator iter = _managedIter;
	return ++iter;
}

void windowBase::render(void)
{
	if (_img)
	{
		IMAGEMANAGER->getTransformState() = TF_POSITION;
		IMAGEMANAGER->statePos(_pos);
		_img->render();
	}

	for (auto i = _mButton.begin(); i != _mButton.end(); ++i)
		i->second->render();
}

buttonBase * windowBase::addButton(string name, buttonBase * addition)
{
	buttonBase* b = findButton(name);
	if (b != NULL) return b;

	addition->getWindow() = this;
	_mButton.insert(make_pair(name, addition));

	return addition;
}

buttonBase * windowBase::findButton(string name)
{
	auto & iter = _mButton.find(name);
	if (iter == _mButton.end()) return NULL;

	return iter->second;
}


// ----- Window Shop ----- //
#include "shopBase.h"
HRESULT windowShop::init(void)
{
	windowBase::init();
	_scroll = 0;
	_shop = NULL;

	return S_OK;
}

void windowShop::render(void)
{
	windowBase::render();
	
	if (_shop) _shop->render();
}
