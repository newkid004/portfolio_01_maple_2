#include "stdafx.h"
#include "btDetails.h"

#include  "windowBase.h"
HRESULT btDetails::init(void)
{
	_img = IMAGEMANAGER->find("details");

	_active = [&](void)->UI_LIST_ITER {WINMANAGER->trans("stat_details"); return _bindWindow->getIter(); };

	_size = _img->getFrameSize();

	_frameX = _frameY = 0;

	return S_OK;
}

UI_LIST_ITER btDetails::update(void)
{
	fRECT rc;
	rc.LT = _pos + _bindWindow->getPos();
	rc.RB = rc.LT + _size;

	if (IsClickRect(rc, _ptMouse))
	{
		if (KEYMANAGER->up(VK_LBUTTON))
		{
			if (_frameX == 0)
				_frameX = 1;
			else
				_frameX = 0;
			return _active();
		}
		else if (KEYMANAGER->down(VK_LBUTTON))
			_frameY = 2;
		else
			_frameY = 1;
	}
	else
		_frameY = 0;


	return _bindWindow->getIter();
}

void btDetails::render(void)
{
	IMAGEMANAGER->getTransformState() = TF_POSITION;
	IMAGEMANAGER->statePos(_pos + _bindWindow->getPos());
	_img->frameRender(_frameX, _frameY);
}
