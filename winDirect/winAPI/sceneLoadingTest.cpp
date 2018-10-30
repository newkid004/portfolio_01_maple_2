#include "stdafx.h"
#include "sceneLoadingTest.h"

#include "loading.h"

HRESULT sceneLoadingTest::init(void)
{
	_loading = new loading; _loading->init();

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

	return S_OK;
}

void sceneLoadingTest::release(void)
{
}

void sceneLoadingTest::update(void)
{
	if (_loading->loadingDone())
	{
		releaseLoading();
		SCENEMANAGER->changeScene("test");
	}
}

void sceneLoadingTest::render(void)
{
}

void sceneLoadingTest::releaseLoading(void)
{
	if (_loading)
	{
		_loading->release();
		SAFE_DELETE(_loading);
	}
}
