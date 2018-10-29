#include "stdafx.h"
#include "mainGame.h"

//=============
// # �������� #
//=============
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

ID2D1Factory * _factory = NULL;
ID2D1HwndRenderTarget*	_renderTarget = NULL;

mainGame* _mg;

//==================
// # �Լ� ���漱�� #
//==================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//==================
// # Direct #
//==================
// IDirect3D9*			_d3d9;
// int					_dHVP;
// IDirect3DDevice9*	_dDevice = 0;

//===================
// # ������ �����Լ� #
//===================
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	_mg = new mainGame();

	//�ν��Ͻ��� ���������� ��´�
	_hInstance = hInstance;

	//WNDCLASS: ������ â�� ������ �����ϱ� ���� ����ü
	//������â ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;									   //Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;									   //������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);				   //���콺 Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);			   //������
	wndClass.hInstance = hInstance;								   //�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;					   //������ ���ν���
	wndClass.lpszClassName = WINNAME;							   //Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;								   //�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;		   //������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//����̽� ��� ����ü (ȭ�� ���÷��̰��� ����ü)
	DEVMODE dm;

	ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;			//32��Ʈ Ʈ���÷�
	dm.dmPelsWidth = 1980;			//���� �ػ�
	dm.dmPelsHeight = 1020;			//���� �ػ�
	dm.dmDisplayFrequency = 60;		//����� 60Hz
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//ȭ���� ����Ǹ� �ڵ����� ���� ȭ���� �ػ󵵷� ����
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	//ȭ�鿡 ������ ������ â�� ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ�� X��ǥ
		WINSTARTY,				//������ ȭ�� Y��ǥ
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//�������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� ������ NULL
								//�ʿ信 ���ؼ� ��������� ������ NULL
		);

	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
#else
	//ȭ�鿡 ������ ������ â�� ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ�� X��ǥ
		WINSTARTY,				//������ ȭ�� Y��ǥ
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//�������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� ������ NULL
								//�ʿ信 ���ؼ� ��������� ������ NULL
		);

	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

#endif		// #ifdef FULLSCREEN

	// // ===== Direct ===== //
	// ----- ���丮 ��ü ���� : �̱� ������
	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory))
		return 0;

	RECT r;
	GetClientRect(_hWnd, &r);	// ���� �����츦 ��� ��� �������
	if (S_OK != _factory->CreateHwndRenderTarget(								// ���� Ÿ�� ����
		RenderTargetProperties(),												// ���� Ÿ�� ���� ���� : default
		HwndRenderTargetProperties(_hWnd, SizeU(RectWidth(r), RectHeight(r))),	// ��� ��� ������ �ڵ�
		&_renderTarget))														// ���� Ÿ�� ����
		return 0;
	
	// antialias ����
	_renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);	// ���

	//ȭ�鿡 ������â �����ֱ�
	ShowWindow(_hWnd, nCmdShow);

	//MSG: �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;

	// �ʱ�ȭ : ���� ��, ����
	if (FAILED(_mg->init()))		// ���ΰ��� Ŭ������ �ʱ�ȭ
	{
		return 0;
	}

	//���ӿ�
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	//�Ϲ� ���α׷��ֿ�
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();

	// D2D ����
	_factory->Release();
	_renderTarget->Release();

	//������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//===================
// # ������ ���ν��� # 
//===================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//=============================================================
// # ������ ũ�� ���� # (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//=============================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}