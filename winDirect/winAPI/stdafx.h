
//stdafx.h: ���� ��������� ���� ��������� �ʴ�
//ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
//��� �ִ� ���� ����
#pragma once
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "jsoncpp/lib_json/json_vc71_libmtd.lib")

#include <SDKDDKver.h>

//���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN

// #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//Windows ��� ����
#include <Windows.h>
#include <wincodec.h>

//C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>
#include <ole2.h>
#include <assert.h>

//C++ ��Ÿ�� ��� ����
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

// Direct ��� ����
#include <d2d1.h>

using namespace std;
using namespace D2D1;

//===================================
// # ���� ���� ��������� �̰��� �߰� #
//===================================
// #include "triFunction.h"
#include "utils.h"

// json
#include "jsoncpp/include/json/forwards.h"
#include "jsoncpp/include/json/json.h"

using namespace MY_UTIL;

// �Ŵ���
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtDataManager.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "cameraManager.h"

#include "jsoncpp\include\json\json.h"
#include "JsonSaveLoader.h"

// �Ŵ��� : ���� �߰�
#include "renderManager.h"
#include "winManager.h"
#include "fieldManager.h"
#include "patternManager.h"
#include "skillManager.h"
#include "animationGroupManager.h"
#include "buffManager.h"
#include "npcManager.h"
#include "questManager.h"
#include "shopManager.h"
#include "enemyManager.h"

#include "gameSystem.h"

//========================
// # �̱����� �̰��� �߰� #
//========================
#define RND				randomFunction::getSingleton()
#define KEYMANAGER		keyManager::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define TXTMANAGER		txtDataManager::getSingleton()
#define INIDATA			iniData::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()
#define JSONDATAMANAGER	JsonSaveLoader::getSingleton()
#define RENDERMANAGER	renderManager::getSingleton()
#define WINMANAGER		winManager::getSingleton()
#define FIELDMANAGER	fieldManager::getSingleton()
#define PATTERNMANAGER	patternManager::getSingleton()
#define SKILLMANAGER	skillManager::getSingleton()
#define ANIGROUPMANAGER animationGroupManager::getSingleton()
#define BUFFMANAGER		buffManager::getSingleton()
#define NPCMANAGER		npcManager::getSingleton()
#define QUESTMANAGER	questManager::getSingleton()
#define SHOPMANAGER		shopManager::getSingleton()
#define ENEMYMANAGER	enemyManager::getSingleton()

#define GAMESYSTEM		gameSystem::getSingleton()


//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		(LPTSTR)(TEXT("MapleStory"))

//#define FULLSCREEN
#define PROCESS_D3D

#ifdef FULLSCREEN
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	GetSystemMetrics(SM_CXSCREEN)
#define WINSIZEY	GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	WS_POPUPWINDOW | WS_MAXIMIZE
#else
#define WINSTARTX	10
#define WINSTARTY	10
#define WINSIZEX	1280
#define WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU
#endif

#define WINRATIO	1.0f
#define WINSIZEX_R	(WINSIZEX * WINRATIO)
#define WINSIZEY_R	(WINSIZEY * WINRATIO)
#define CENTERX		(WINSIZEX / 2)
#define CENTERY		(WINSIZEY / 2)

//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = NULL;}}
#define D3D_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

//===============================================
// # ��ũ�� ���� #
//===============================================
#ifdef PROCESS_D3D
	#define C_COLOR_RED			D2D1::ColorF(1.0f, 0.0f, 0.0f)
	#define C_COLOR_GREEN		D2D1::ColorF(0.0f, 1.0f, 0.0f)
	#define C_COLOR_BLUE		D2D1::ColorF(0.0f, 0.0f, 1.0f)
	#define C_COLOR_MAGENTA		D2D1::ColorF(1.0f, 0.0f, 1.0f)
	#define C_COLOR_YELLOW		D2D1::ColorF(1.0f, 1.0f, 0.0f)
	#define C_COLOR_CYAN		D2D1::ColorF(0.0f, 1.0f, 1.0f)
	#define C_COLOR_WHITE		D2D1::ColorF(1.0f, 1.0f, 1.0f)
	#define C_COLOR_BLACK		D2D1::ColorF(0.0f, 0.0f, 0.0f)
	#define C_COLOR_GRAY		D2D1::ColorF(0.5f, 0.5f, 0.5f)
#else
	#define C_COLOR_RED			RGB(255,	0,		0)
	#define C_COLOR_GREEN		RGB(0,		255,	0)
	#define C_COLOR_BLUE		RGB(0,		0,		255)
	#define C_COLOR_MAGENTA		RGB(255,	0,		255)
	#define C_COLOR_YELLOW		RGB(255,	255,	0)
	#define C_COLOR_CYAN		RGB(0,		255,	255)
	#define C_COLOR_WHITE		RGB(255,	255,	255)
	#define C_COLOR_BLACK		RGB(0,		0,		0)
	#define C_COLOR_GRAY		RGB(128,	128,	128)
#endif

//=============
// # �������� #
//=============
// ===== winAPI ===== //
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

// ===== Direct ===== //
extern ID2D1Factory*			_factory;
extern ID2D1HwndRenderTarget*	_renderTarget;

//============================
// # ��ũ�� # (�������� ���)
//============================
#define PTMOUSE		POINT{ _ptMouse.x / (long)WINRATIO, _ptMouse.y / (long)WINRATIO }