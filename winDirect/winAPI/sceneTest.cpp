#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init(void)
{
	getBackColor() = C_COLOR_GRAY;
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	_ani = new animation;
	_ani->init(IMAGEMANAGER->find("frame"));
	_ani->setFPS(15.0f);
	_ani->setDefPlayFrame(false, false);

	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
	updateControl();
}

void sceneTest::render(void)
{
	IMAGEMANAGER->find("frame")->aniRender(_ani->update());
}

void sceneTest::updateControl(void)
{
	static fPOINT pos;
	static float rot;
	static int flip;

	if (KEYMANAGER->down('W'))	rot -= TIMEMANAGER->getElapsedTime() * 180;
	if (KEYMANAGER->down('S'))	rot += TIMEMANAGER->getElapsedTime() * 180;

	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 1000;

	if (KEYMANAGER->press('A')) flip ^= IMAGE_FLIP_HORIZON;
	if (KEYMANAGER->press('D')) flip ^= IMAGE_FLIP_VERTICAL;

	if (KEYMANAGER->press(VK_SPACE)) _ani->start();

	IMAGEMANAGER->statePos(pos);
	IMAGEMANAGER->stateRotate(rot);
	IMAGEMANAGER->stateFlip(flip);
}
