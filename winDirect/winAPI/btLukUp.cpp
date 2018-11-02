#include "stdafx.h"
#include "btLukUp.h"

#include "windowBase.h"

HRESULT btLukUp::init(void)
{
	_img = IMAGEMANAGER->find("statUP");

	_active = [&](void)->UI_LIST_ITER {WINMANAGER->trans("statusUI"); return _bindWindow->getIter(); };

	_size = _img->getFrameSize();

	_frame = 0;

	return S_OK;
}

UI_LIST_ITER btLukUp::update(void)
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


	return _bindWindow->getIter();
}

void btLukUp::render(void)
{
	IMAGEMANAGER->getTransformState() = TF_POSITION;
	IMAGEMANAGER->statePos(_pos + _bindWindow->getPos());
	_img->frameRender(_frame, 0);
}
