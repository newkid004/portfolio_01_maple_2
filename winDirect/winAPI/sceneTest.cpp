#include "stdafx.h"
#include "sceneTest.h"

static fPOINT offset;
static fPOINT pos;
static float rot;
static int flip;
static float scale = 1.0f;

HRESULT sceneTest::init(void)
{
	getBackColor() = C_COLOR_GRAY;
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	_ani = new animation;
	_ani->init(IMAGEMANAGER->find("frame"));
	_ani->setFPS(15.0f);
	_ani->setDefPlayFrame(false, false);

	TEXTMANAGER->add("text", L"µ¸¿òÃ¼", 12.f);
	TEXTMANAGER->setFont("text");

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

	IMAGEMANAGER->getTransformState(TF_ALL);
	IMAGEMANAGER->find("frame")->loopFrameRender(_ani->getFramePos().x / _ani->getFrameSize().x, _ani->getFramePos().y / _ani->getFrameSize().y, &fRECT(pos.x, pos.y, pos.x + 100 * scale, pos.y + 80 * scale), offset, 0.75f);

	IMAGEMANAGER->getTransformState(TF_POSITION);
	IMAGEMANAGER->statePos(WINSIZEX - 300, 10);
	IMAGEMANAGER->setTransform();

	D2D1_RECT_F rc = D2D1_RECT_F{ 0, 0, 300, 200 };
	wstring str;
	str = L"offset : " + to_wstring(offset.x) + L" / " + to_wstring(offset.y);
	TEXTMANAGER->drawText(&str, &rc); 

	str = L"posision : " + to_wstring(pos.x) + L" / " + to_wstring(pos.y); rc.top += 20;
	TEXTMANAGER->drawText(&str, &rc);

	str = L"scale : " + to_wstring(scale); rc.top += 20;
	TEXTMANAGER->drawText(&str, &rc);
}

void sceneTest::updateControl(void)
{
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
