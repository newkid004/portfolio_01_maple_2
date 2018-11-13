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


//windowMovable

HRESULT windowMovable::init(void)
{
	_gapPos = 0;
	_isClick = false;
	_clickRect = { 0,0,0,0 };
	_resizeClickRect = { 0,0,0,0 };

	return windowBase::init();
}

UI_LIST_ITER windowMovable::update(void)
{
	if (_img)
	{
		_clickRect = fRECT(_pos.x,
			_pos.y,
			_pos.x + _img->getSize().x,
			_pos.y + _img->getSize().y/5);
	}
	
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
		if (IsClickRect(_clickRect, _ptMouse) && !_isClick)
		{
			_isClick = true;
			_gapPos = { (_ptMouse.x - _pos.x), (_ptMouse.y - _pos.y) };
			_resizeClickRect = _clickRect;
		}
		else if (IsClickRect(_resizeClickRect, _ptMouse)&& _isClick)
		{
			//창 위치 변경
			_pos = { _ptMouse.x - _gapPos.x , _ptMouse.y - _gapPos.y };

			//마우스와의 거리를 계산후 resizeRect크기변경
			fPOINT mouse = { (float)_ptMouse.x,(float)_ptMouse.y };
			float distance = 4.0f*getDistance(mouse, fPOINT((_clickRect.LT.x+_clickRect.RB.x)/2,(_clickRect.LT.y+_clickRect.RB.y)/2));
			_resizeClickRect = fRECT(_clickRect.LT.x - distance, _clickRect.LT.y - distance,
				_clickRect.RB.x + distance, _clickRect.RB.y + distance);
			this->show();
			return WINMANAGER->getIgnoreIter();
		}
		
		if (IsClickRect(rc, _ptMouse))
		{
			// 윈도우를 맨 앞으로 / 뒷 창 무시
			this->show();
			return WINMANAGER->getIgnoreIter();
		}
	}
	else _isClick = false;

	list<windowBase*>::iterator iter = _managedIter;
	return ++iter;
}
