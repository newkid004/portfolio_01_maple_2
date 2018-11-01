#include "stdafx.h"
#include "invenWindowTest.h"

#include "windowBase.h"

HRESULT invenWindowTest::init(void)
{
	IMAGEMANAGER->add("invenUI", L"image/UI/invenUI.png");
	initWindow();
	return S_OK;
}

void invenWindowTest::release(void)
{
}

void invenWindowTest::update(void)
{
	WINMANAGER->update();
}

void invenWindowTest::render(void)
{
	WINMANAGER->render();
}

void invenWindowTest::initWindow(void)
{

	windowBase* w;
	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("invenUI");
	w->getPos().x = WINSIZEX / 4;
	w->getPos().y = WINSIZEY / 4;

	WINMANAGER->add("invenUI", w);

	//w->show();
}
