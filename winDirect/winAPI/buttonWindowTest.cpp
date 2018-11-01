#include "stdafx.h"
#include "buttonWindowTest.h"

#include "windowBase.h"
#include "buttonTest2.h"
#include "buttonTest3.h"


HRESULT buttonWindowTest::init(void)
{
	IMAGEMANAGER->add("invenUI", L"image/UI/invenUI.png");
	IMAGEMANAGER->add("buttonUI", L"image/UI/buttonUI.png", 3, 6);
	IMAGEMANAGER->add("setting", L"image/UI/setting.png");
	initWindow();
	IMAGEMANAGER->resetTransform();
	return S_OK;
}

void buttonWindowTest::release(void)
{
}

void buttonWindowTest::update(void)
{
	WINMANAGER->update();
}

void buttonWindowTest::render(void)
{
	WINMANAGER->render();
}

void buttonWindowTest::initWindow(void)
{
	windowBase* w;
	buttonTest2* b;
	buttonTest3* b3;

	w = new windowBase; w->init();
	b = new buttonTest2; b->init();
	b3 = new buttonTest3; b3->init();

	w->addButton("testButton0", b);
	w->addButton("testButton1", b3);
	w->getPos() = { 500,500 };
	b3->getPos().x += 100;
	WINMANAGER->add("testWindow2", w);
	WINMANAGER->show("testWindow2");

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("invenUI");
	w->getPos().x = WINSIZEX / 4;
	w->getPos().y = WINSIZEY / 4;

	WINMANAGER->add("invenUI", w);
}
