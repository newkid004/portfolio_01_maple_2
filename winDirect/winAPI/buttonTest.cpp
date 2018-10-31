#include "stdafx.h"
#include "buttonTest.h"
#include "windowBase.h"

HRESULT buttonTest::init(void)
{
	_active = [&](void)->void { _bindWindow->close(); };
	return S_OK;
}

list<windowBase*>::iterator * buttonTest::update(void)
{
	fRECT fRc;
	fRc.LT = _pos + _bindWindow->getPos();
	fRc.RB = fRc.LT + _size;

	if (IsClickRect(fRc, _ptMouse))
	{
		if (KEYMANAGER->press(VK_LBUTTON))
		{

		}
	}
	
	return nullptr;
}

void buttonTest::render(fPOINT & offset)
{

}
