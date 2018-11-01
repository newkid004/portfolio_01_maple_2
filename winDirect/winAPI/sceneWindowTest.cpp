#include "stdafx.h"
#include "sceneWindowTest.h"

#include "windowBase.h"
#include "buttonTest.h"

HRESULT sceneWindowTest::init(void)
{
	IMAGEMANAGER->add("buttonTest", L"image/UI/buttonTest.png", 3, 2);

	initWindow();

	IMAGEMANAGER->resetTransform();

	return S_OK;
}

void sceneWindowTest::release(void)
{
}

void sceneWindowTest::update(void)
{
	WINMANAGER->update();
}

void sceneWindowTest::render(void)
{
	WINMANAGER->render();
}

void sceneWindowTest::initWindow(void)
{
	// defButton == buttonTest<list<windowBase*>::iterator>

	windowBase* w;
	buttonTest * b;

	w = new windowBase; w->init();
	b = new buttonTest; b->init();

	w->addButton(b);
	WINMANAGER->add("testWindow", w);
	WINMANAGER->show("testWindow");
}
