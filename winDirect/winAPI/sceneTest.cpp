#include "stdafx.h"
#include "sceneTest.h"

static fPOINT offset;

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
	_ani->update();

	IMAGEMANAGER->find("frame")->loopRender(&fRECT(20, 30, 300, 900));
}

void sceneTest::updateControl(void)
{
	static fPOINT pos;
	static float rot;
	static int flip;
	static float scale = 1.0f;

	if (KEYMANAGER->down('W'))	rot -= TIMEMANAGER->getElapsedTime() * 180;
	if (KEYMANAGER->down('S'))	rot += TIMEMANAGER->getElapsedTime() * 180;

	if (KEYMANAGER->down(VK_LEFT))	pos.x -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_RIGHT))	pos.x += TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_UP))	pos.y -= TIMEMANAGER->getElapsedTime() * 1000;
	if (KEYMANAGER->down(VK_DOWN))	pos.y += TIMEMANAGER->getElapsedTime() * 1000;

	if (KEYMANAGER->press('A')) flip ^= IMAGE_FLIP_HORIZON;
	if (KEYMANAGER->press('D')) flip ^= IMAGE_FLIP_VERTICAL;

	if (KEYMANAGER->down('E')) scale += TIMEMANAGER->getElapsedTime() * 3;
	if (KEYMANAGER->down('Q')) scale -= TIMEMANAGER->getElapsedTime() * 3;

	if (KEYMANAGER->down('I')) offset.y -= TIMEMANAGER->getElapsedTime() * 200;
	if (KEYMANAGER->down('K')) offset.y += TIMEMANAGER->getElapsedTime() * 200;
	if (KEYMANAGER->down('J')) offset.x -= TIMEMANAGER->getElapsedTime() * 200;
	if (KEYMANAGER->down('L')) offset.x += TIMEMANAGER->getElapsedTime() * 200;

	if (KEYMANAGER->press(VK_SPACE)) _ani->start();

	if (KEYMANAGER->press(VK_F1)) IMAGEMANAGER->getTransformState() ^= TF_FLIP;
	if (KEYMANAGER->press(VK_F2)) IMAGEMANAGER->getTransformState() ^= TF_SCALE;
	if (KEYMANAGER->press(VK_F3)) IMAGEMANAGER->getTransformState() ^= TF_ROTATION;
	if (KEYMANAGER->press(VK_F4)) IMAGEMANAGER->getTransformState() ^= TF_POSITION;

	IMAGEMANAGER->statePos(pos);
	IMAGEMANAGER->stateRotate(rot);
	IMAGEMANAGER->stateFlip(flip);
	IMAGEMANAGER->statScale(scale, scale);
}
