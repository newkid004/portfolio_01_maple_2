#include "stdafx.h"
#include "mainGame.h"

// scene
#include "sceneTest.h"
#include "loadingScene.h"
#include "charaterSelectScene.h"

//=================//
// # init # �ʱ�ȭ //
//=================//
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);

	// add
	SCENEMANAGER->addScene("test", new sceneTest);
	SCENEMANAGER->addScene("loading", new loadingScene);
	SCENEMANAGER->addScene("charaterSelect", new charaterSelectScene);

	// change
	SCENEMANAGER->changeScene("loading");
	//SCENEMANAGER->changeScene("test");
	
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
	if (true)
	{
		_renderTarget->BeginDraw();
		_renderTarget->Clear(getBackColor());
		// ============================================================

		SCENEMANAGER->render();

		// ============================================================
		_renderTarget->EndDraw();
		
		// ----- ����� �ÿ� ----- //
		// _dDevice->Present(0, 0, 0, 0);			// ����� �ÿ�
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
