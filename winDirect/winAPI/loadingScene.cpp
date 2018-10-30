#include "stdafx.h"
#include "loadingScene.h"

#include "animation.h"

HRESULT loadingScene::init(void)
{
	currentFrameY = 0;
	updateTime = 0.01f;
	elapsedTime = 0;

	getBackColor() = C_COLOR_WHITE;

	IMAGEMANAGER->add("charaterSelectBack", L"image/background/charaterSelectBack.png");
	IMAGEMANAGER->add("wizet_loading", L"image/background/wizet.png",1,44);
	IMAGEMANAGER->add("nonePlayerB", L"image/charaterSelect/nonePlayerB.png", 1, 8);
	IMAGEMANAGER->add("nonePlayer", L"image/charaterSelect/nonePlayer.png");
	IMAGEMANAGER->add("start", L"image/testImg.png", 1, 1, true);
	//======================헤네시스=========================
	IMAGEMANAGER->add("henesys", L"image/map/henesys.png", 1, 1, true);
	IMAGEMANAGER->add("henesys_pixel", L"image/map/henesys_pixel.png",1,1,true);
	IMAGEMANAGER->add("henesys_background_1", L"image/background/henesys_background_1.png");
	IMAGEMANAGER->add("henesys_background_2", L"image/background/henesys_background_2.png");
	IMAGEMANAGER->add("henesys_background_3", L"image/background/henesys_background_3.png");
	IMAGEMANAGER->add("henesys_background_4", L"image/background/henesys_background_4.png");
	IMAGEMANAGER->add("henesys_background_5", L"image/background/henesys_background_5.png");
	IMAGEMANAGER->add("henesys_background_6", L"image/background/henesys_background_6.png");


	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, true);


	return S_OK;
}

void loadingScene::release(void)
{
}


void loadingScene::update(void)
{
	elapsedTime += TIMEMANAGER->getElapsedTime();
	if (elapsedTime >= updateTime)
	{
		elapsedTime = 0;
		if (++currentFrameY> IMAGEMANAGER->find("wizet_loading")->getMaxFrame().y)
		{
			//currentFrameY = 0;
		    SCENEMANAGER->changeScene("test2");
		}
	}
}

void loadingScene::render(void)
{
	IMAGEMANAGER->statePos(fPOINT(WINSIZEX / 2.0f - IMAGEMANAGER->find("wizet_loading")->getFrameSize().x/2.0f,
		                          WINSIZEY / 2.0f - IMAGEMANAGER->find("wizet_loading")->getFrameSize().y/2.0f - WINSIZEY/12.0f));
	IMAGEMANAGER->find("wizet_loading")->frameRender(0, currentFrameY);
}
