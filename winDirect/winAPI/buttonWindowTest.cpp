#include "stdafx.h"
#include "buttonWindowTest.h"

#include "windowBase.h"
#include "buttonTest2.h"
#include "buttonTest3.h"
#include "settingButtonTest.h"


HRESULT buttonWindowTest::init(void)
{
	IMAGEMANAGER->add("invenUI", L"image/UI/invenUI.png");
	IMAGEMANAGER->add("buttonUI", L"image/UI/buttonUI.png", 3, 6);
	IMAGEMANAGER->add("setting", L"image/UI/setting.png");
	IMAGEMANAGER->add("settingUI", L"image/UI/Shortcuts.png");
	IMAGEMANAGER->add("back", L"image/UI/shortcut_char.png");
	IMAGEMANAGER->add("escUI", L"image/UI/escUI.png", 2, 3);
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
	settingButtonTest* s;

	w = new windowBase; w->init();
	b = new buttonTest2; b->init();
	b3 = new buttonTest3; b3->init();
	s = new settingButtonTest; s->init();

	w->addButton("testButton0", b);
	w->addButton("testButton1", b3);
	w->getPos() = { 500,500 };
	b3->getPos().x += 100;
	w->getImage() = IMAGEMANAGER->find("back");
	WINMANAGER->add("testWindow2", w);
	WINMANAGER->show("testWindow2");

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("invenUI");
	w->getPos().x = WINSIZEX / 4;
	w->getPos().y = WINSIZEY / 4;

	WINMANAGER->add("invenUI", w);

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("setting");
	w->getPos().x = 700;
	w->getPos().y = 350;
	s->getPos().y = 50;
	w->addButton("testButton10", s);

	WINMANAGER->add("setting", w);

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("settingUI");
	w->getPos().x = 0;
	w->getPos().y = 0;

	WINMANAGER->add("settingUI", w);
}
