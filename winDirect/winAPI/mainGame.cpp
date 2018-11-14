#include "stdafx.h"
#include "mainGame.h"

// scene
#include "sceneTest.h"
#include "sceneLoadingTest.h"
#include "loadingScene.h"
#include "charaterSelectScene.h"
#include "sceneTest2.h"
#include "sceneTestPixelCrash.h"
#include "sceneWindowTest.h"
#include "buttonWindowTest.h"
#include "playerTestScene.h"
#include "sceneTestShop.h"
#include "sceneTestInventory.h"
#include "sceneTestShopInven.h"

//=================//
// # init # �ʱ�ȭ //
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
	SCENEMANAGER->addScene("testPixelCrash", new sceneTestPixelCrash);
	SCENEMANAGER->addScene("WindowTest", new sceneWindowTest);
	SCENEMANAGER->addScene("buttonWindowTest", new buttonWindowTest);
	SCENEMANAGER->addScene("playerTest", new playerTestScene);
	SCENEMANAGER->addScene("testShop", new sceneTestShop);
	SCENEMANAGER->addScene("testInventory", new sceneTestInventory);
	SCENEMANAGER->addScene("sceneTestShopInven", new sceneTestShopInven);

	// change
	SCENEMANAGER->changeScene("sceneTestShopInven");

	//SCENEMANAGER->changeScene("buttonWindowTest");
	//SCENEMANAGER->changeScene("playerTest");
	return S_OK;
}

//==================// 
// # release # ���� //
//==================//
void mainGame::release(void)
{
	gameNode::release();
	//�����Ҵ��� �ߴٸ� ���⿡�� SAFE_DELETE() ���
}

//=====================//
// # update # ������Ʈ //
//=====================//
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//=================//
// # render # ���� //
//=================//
void mainGame::render(void)
{
#ifdef PROCESS_D3D
	if (_renderTarget)
	{
		_renderTarget->BeginDraw();
		_renderTarget->Clear(getBackColor());
		// ============================================================

		SCENEMANAGER->render();
		TIMEMANAGER->render();

		// ============================================================
		_renderTarget->EndDraw();
	}

#else

	// ----- ��� �̹��� -----
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	// =============================================================

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	// =============================================================

	// ----- ����� �ÿ� -----
	// �ػ� ����
	if (WINRATIO != 1.0f)
	{
		this->getBackBuffer()->render(getStrcDC(), WINRATIO);
		this->getStrcBuffer()->render(getHDC());
	}
	// �ػ� ���� �� ��
	else
	{
		this->getBackBuffer()->render(getHDC());
	}

#endif // PROCESS_DIRECT
}
