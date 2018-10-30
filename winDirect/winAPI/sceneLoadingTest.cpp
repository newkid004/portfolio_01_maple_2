#include "stdafx.h"
#include "sceneLoadingTest.h"

#include "loading.h"

HRESULT sceneLoadingTest::init(void)
{
	_loading = new loading; _loading->init();
	_ani = new animation;

	// ----- first load ----- //
	_loadingImage = IMAGEMANAGER->add("wizet_loading", L"image/background/wizet.png", 1, 44);

	// ----- UI ----- //
	_loading->loadImage("charaterSelectBack", L"image/background/charaterSelectBack.png");
	_loading->loadImage("nonePlayerB", L"image/charaterSelect/nonePlayerB.png", 1, 8);
	_loading->loadImage("nonePlayer", L"image/charaterSelect/nonePlayer.png");

	// ----- skill ----- //
	// 0. beginner
	_loading->loadImage("player_skill_0_beginner_icon", L"image/effect/skill/0_beginner/icon.png", 2, 3);
	_loading->loadImage("player_skill_0_beginner_0_three_snail_hit", L"image/effect/skill/0_beginner/0_three_snail/hit.png", 6, 3);
	_loading->loadImage("player_skill_0_beginner_0_three_snail_throwable", L"image/effect/skill/0_beginner/0_three_snail/throwable.png", 6, 3);
	_loading->loadImage("player_skill_0_beginner_1_celeritial_movement_effect", L"image/effect/skill/0_beginner/1_celeritial_movement/effect.png", 12, 1);
	_loading->loadImage("player_skill_0_beginner_2_first_aid_effect", L"image/effect/skill/0_beginner/2_first_aid/effect.png", 13, 1);

	// test
	_loading->loadImage("test", L"image/testImg.png");
	_loading->loadImage("frame", L"image/frame.png", 12, 1);

	// ani
	_ani->init(_loadingImage);
	_ani->setFPS(15.f);
	_ani->setDefPlayFrame(false, true);
	_ani->start();

	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);
	IMAGEMANAGER->disableTransform(bit_pick(TF_ALL, TF_POSITION));
	IMAGEMANAGER->statePos(fPOINT(
		(WINSIZEX - _ani->getFrameSize().x) / 2,
		(WINSIZEY - _ani->getFrameSize().y) / 2));

	return S_OK;
}

void sceneLoadingTest::release(void)
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
	if (_ani)
	{
		_ani->release();
		SAFE_DELETE(_ani);
	}
}

void sceneLoadingTest::update(void)
{
	_ani->update();
	if (_loading->loadingDone() && _ani->isEnd())
	{
		release();
		IMAGEMANAGER->enableTransform(TF_ALL);
		SCENEMANAGER->changeScene("test");
	}
}

void sceneLoadingTest::render(void)
{
	_loadingImage->aniRender(_ani);
}
