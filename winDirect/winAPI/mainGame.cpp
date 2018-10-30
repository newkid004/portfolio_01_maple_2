#include "stdafx.h"
#include "mainGame.h"

// scene
#include "sceneTest.h"
#include "sceneLoadingTest.h"
#include "loadingScene.h"
#include "charaterSelectScene.h"
#include "sceneTest2.h"

//=================//
// # init # 초기화 //
//=================//
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);

	// add
	SCENEMANAGER->addScene("test", new sceneTest);
	SCENEMANAGER->addScene("testLoading", new sceneLoadingTest);
	SCENEMANAGER->addScene("loading", new loadingScene);
	SCENEMANAGER->addScene("charaterSelect", new charaterSelectScene);
	SCENEMANAGER->addScene("test2", new sceneTest2);

	// change
	SCENEMANAGER->changeScene("testLoading");
	//SCENEMANAGER->changeScene("test");
	
	return S_OK;
}

//==================// 
// # release # 해제 //
//==================//
void mainGame::release(void)
{
	gameNode::release();
	//동적할당을 했다면 여기에서 SAFE_DELETE() 사용
}

//=====================//
// # update # 업데이트 //
//=====================//
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//=================//
// # render # 렌더 //
//=================//
void mainGame::render(void)
{
#ifdef PROCESS_D3D
	if (true)
	{
		_renderTarget->BeginDraw();
		_renderTarget->Clear(getBackColor());
		// ============================================================

		SCENEMANAGER->render();

		// ============================================================
		_renderTarget->EndDraw();
		
		// ----- 백버퍼 시연 ----- //
		// _dDevice->Present(0, 0, 0, 0);			// 백버퍼 시연
	}

#else

	// ----- 배경 이미지 -----
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	// =============================================================

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	// =============================================================

	// ----- 백버퍼 시연 -----
	// 해상도 변경
	if (WINRATIO != 1.0f)
	{
		this->getBackBuffer()->render(getStrcDC(), WINRATIO);
		this->getStrcBuffer()->render(getHDC());
	}
	// 해상도 변경 안 함
	else
	{
		this->getBackBuffer()->render(getHDC());
	}

#endif // PROCESS_DIRECT
}
