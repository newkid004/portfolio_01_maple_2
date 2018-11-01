#include "stdafx.h"
#include "settingButtonTest.h"

#include "windowBase.h"

HRESULT settingButtonTest::init(void)
{
	_img = IMAGEMANAGER->find("escUI");

	_active = [&](void)->UI_LIST_ITER {  WINMANAGER->trans("settingUI"); return _bindWindow->getIter();  };

	_size = _img->getFrameSize();

	_frame = 0;

	return S_OK;
}

UI_LIST_ITER settingButtonTest::update(void)
{
	fRECT rc;
	rc.LT = _pos + _bindWindow->getPos();
	rc.RB = rc.LT + _size;

	if (IsClickRect(rc, _ptMouse))
	{
		if (KEYMANAGER->up(VK_LBUTTON))
			return _active();
		else if (KEYMANAGER->down(VK_LBUTTON))
			_frame = 1;
		else
			_frame = 1;
	}
	else
		_frame = 0;


	return _bindWindow->getIter();
}

void settingButtonTest::render(void)
{
	IMAGEMANAGER->getTransformState() = TF_POSITION;
	IMAGEMANAGER->statePos(_pos + _bindWindow->getPos());
	_img->frameRender(_frame, 1);
}
