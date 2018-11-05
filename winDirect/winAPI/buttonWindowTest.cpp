#include "stdafx.h"
#include "buttonWindowTest.h"

#include "windowBase.h"
#include "buttonTest2.h"
#include "buttonTest3.h"
#include "settingButtonTest.h"
#include "btnStatUp.h"
#include "btDetails.h"
#include "event_0000_test.h"
#include "windowStatus.h"

HRESULT buttonWindowTest::init(void)
{
	initImage();
	initWindow();
	initSystem();

	return S_OK;
}

void buttonWindowTest::release(void)
{
}

void buttonWindowTest::update(void)
{
	GAMESYSTEM->update();
	WINMANAGER->update();
}

void buttonWindowTest::render(void)
{
	GAMESYSTEM->render();
	WINMANAGER->render();
}

void buttonWindowTest::initImage(void)
{
	IMAGEMANAGER->add("invenUI", L"image/UI/invenUI.png");
	IMAGEMANAGER->add("buttonUI", L"image/UI/buttonUI.png", 3, 6);
	IMAGEMANAGER->add("setting", L"image/UI/setting.png");
	IMAGEMANAGER->add("settingUI", L"image/UI/Shortcuts.png");
	IMAGEMANAGER->add("back", L"image/UI/shortcut_char.png");
	IMAGEMANAGER->add("escUI", L"image/UI/escUI.png", 2, 3);
	IMAGEMANAGER->add("statusUI", L"image/UI/statusUI.png");
	IMAGEMANAGER->add("statUP", L"image/UI/statUP.png", 4, 1);
	IMAGEMANAGER->add("stat_details", L"image/UI/stat_details.png");
	IMAGEMANAGER->add("details", L"image/UI/details.png", 2, 4);

	IMAGEMANAGER->resetTransform();
}

void buttonWindowTest::initWindow(void)
{
	windowBase* w;
	buttonTest2* b;
	buttonTest3* b3;
	settingButtonTest* s;
	btnStatUp* _btnStatUp;
	btDetails* _btDetails;

	w = new windowBase; w->init();
	b = new buttonTest2; b->init();
	b3 = new buttonTest3; b3->init();
	s = new settingButtonTest; s->init();
	_btDetails = new btDetails; _btDetails->init();

	w->addButton("testButton0", b);
	w->addButton("testButton1", b3);
	w->getPos() = { 500,500 };
	b3->getPos().x += 100;
	w->getImage() = IMAGEMANAGER->find("back");
	WINMANAGER->add("testWindow2", w);
	WINMANAGER->show("testWindow2");

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("invenUI");
	w->getPos().x = 720;
	w->getPos().y = 100;

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
	w->getPos().x = 100;
	w->getPos().y = 0;

	WINMANAGER->add("settingUI", w);

	w = new windowStatus; w->init();
	w->getImage() = IMAGEMANAGER->find("statusUI");
	w->getPos().x = 700;
	w->getPos().y = 100;
	
	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,208 };
	w->addButton("btnStrUp", _btnStatUp);

	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,226 };
	w->addButton("btnDexUp", _btnStatUp);

	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,244 };
	w->addButton("btnIntUp", _btnStatUp);

	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,262 };
	w->addButton("btnLukUp", _btnStatUp);

	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,121 };
	w->addButton("btnHpUp", _btnStatUp);
	
	_btnStatUp = new btnStatUp; _btnStatUp->init();
	_btnStatUp->getPos() = { 185,139 };
	w->addButton("btnMpUp", _btnStatUp);

	_btDetails->getPos().x = 130;
	_btDetails->getPos().y = 287;
	w->addButton("btDetails", _btDetails);

	WINMANAGER->add("statusUI", w);

	w = new windowBase; w->init();
	w->getImage() = IMAGEMANAGER->find("stat_details");
	w->getPos().x = WINMANAGER->find("statusUI")->getPos().x + IMAGEMANAGER->find("statusUI")->getFrameSize().x;
	w->getPos().y = WINMANAGER->find("statusUI")->getPos().y;

	WINMANAGER->add("stat_details", w);
}

void buttonWindowTest::initSystem(void)
{
	GAMESYSTEM->addShortcut("test", 0, [](void)->void { if (KEYMANAGER->press('Q')) EVENTMANAGER->add(new event_0000_test(NULL, WINMANAGER->find("settingUI"))); KEYMANAGER->press('Q'); });
	GAMESYSTEM->putShortcut("test", 'Q');
	GAMESYSTEM->addShortcut("test2", 0, [](void)->void { if (KEYMANAGER->press('W')) WINMANAGER->trans("statusUI"); KEYMANAGER->press('W'); });
	GAMESYSTEM->putShortcut("test2", 'W');
}
