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
	for (auto i = _lButton.begin(); i != _lButton.end();)
	{
		SAFE_DELETE(*i);
		i = _lButton.erase(i);
	}
}

UI_LIST_ITER windowBase::update(void)
{
	UI_LIST_ITER viewIter;
	for (auto i = _lButton.begin(); i != _lButton.end(); ++i)
	{
		viewIter = (*i)->update();
		if (viewIter == WINMANAGER->getIgnoreIter())
			return viewIter;
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

	for (auto i = _lButton.begin(); i != _lButton.end(); ++i)
		(*i)->render();
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
