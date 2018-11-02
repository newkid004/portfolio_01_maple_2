#include "stdafx.h"
#include "playerTestScene.h"


HRESULT playerTestScene::init(void)
{
	_player = new player;
	_player->init();
	return S_OK;
}

void playerTestScene::release(void)
{
	_player->release();
}

void playerTestScene::update(void)
{
	_player->update();
}

void playerTestScene::render(void)
{
	_player->render();
}

