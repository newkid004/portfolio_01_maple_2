#include "stdafx.h"
#include "buttonTest.h"

#include "windowBase.h"

HRESULT buttonTest::init(void)
{
	_img = IMAGEMANAGER->find("buttonTest");
	_active = [&](void)->UI_LIST_ITER { return _bindWindow->close(); };

	_size = _img->getFrameSize();

	_frame = 0;

	return S_OK;
}

UI_LIST_ITER buttonTest::update(void)
{
	fRECT rc;
	rc.LT = _pos + _bindWindow->getPos();
	rc.RB = rc.LT + _size;

	if (IsClickRect(rc, _ptMouse))
	{
		if (KEYMANAGER->up(VK_LBUTTON))
			return _active();
		else if (KEYMANAGER->down(VK_LBUTTON))
			_frame = 2;
		else
			_frame = 1;
	}
	else
		_frame = 0;

	KEYMANAGER->up(VK_LBUTTON);
	KEYMANAGER->down(VK_LBUTTON);

	return _bindWindow->getIter();
}

void buttonTest::render(void)
{
	IMAGEMANAGER->getTransformState() = TF_POSITION;
	IMAGEMANAGER->statePos(_pos + _bindWindow->getPos());

	_img->frameRender(_frame, 0);
}
