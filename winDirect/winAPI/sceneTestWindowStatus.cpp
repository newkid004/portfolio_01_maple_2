#include "stdafx.h"
#include "sceneTestWindowStatus.h"

#include "player.h"
#include "windowStatus.h"

#include "eventList.h"

static fPOINT pos = fPOINT(150, 100);

HRESULT sceneTestWindowStatus::init(void)
{
	initResource();
	initPlayer();
	initWindow();

	return S_OK;
}

void sceneTestWindowStatus::release(void)
{
}

void sceneTestWindowStatus::update(void)
{
	WINMANAGER->update();
	EVENTMANAGER->update();

	updateControl();
}

void sceneTestWindowStatus::render(void)
{
	WINMANAGER->render();
	EVENTMANAGER->render();
}

void sceneTestWindowStatus::initResource(void)
{
	// window
	IMAGEMANAGER->add("UI_status_layout", L"image/UI/status/UI_status_layout.png");
	IMAGEMANAGER->add("UI_status_layout_begin", L"image/UI/status/UI_status_layout_begin.png");
	IMAGEMANAGER->add("UI_status_detail", L"image/UI/status/UI_status_detail.png");
	IMAGEMANAGER->add("UI_status_button_detail", L"image/UI/status/UI_status_button_detail.png", 2, 4);

	// button
	IMAGEMANAGER->add("UI_increase", L"image/UI/UI_increase.png", 4);
}

void sceneTestWindowStatus::initPlayer(void)
{
	player* & p = GAMESYSTEM->getPlayer();
	p = new player; p->init();
}

void sceneTestWindowStatus::initWindow(void)
{
	windowStatus* winStatus = new windowStatus;
	winStatus->init();

	WINMANAGER->add("status", winStatus);
}

void sceneTestWindowStatus::updateControl(void)
{
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 100;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 100;

	if (KEYMANAGER->press('1'))		EVENTMANAGER->add(new eventPlayerLevelUp);

	if (KEYMANAGER->press('Q')) WINMANAGER->trans("status");

	WINMANAGER->find("status")->getPos() = pos;
}
