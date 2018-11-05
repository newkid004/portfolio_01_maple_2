#pragma once

#ifdef PROCESS_D3D

static ColorF				_backColor = C_COLOR_MAGENTA;
static D2D1_SIZE_F			_renderRate;
static IDWriteTextFormat*	_textFormat;

class gameNode
{
private:
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static ColorF & getBackColor(void) { return _backColor; };
	static D2D1_SIZE_F & getRate(void) { return _renderRate; };
	static IDWriteTextFormat* & getTextFormat(void) { return _textFormat; };

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

#else

#include "image.h"
// ����� �̹����� ����������
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _strcBuffer = IMAGEMANAGER->addImage("strcBuffer", (int)WINSIZEX_R, (int)WINSIZEY_R);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	image* getStrcBuffer(void) { return _strcBuffer; }

	// �޸�DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getStrcDC() { return _strcBuffer->getMemDC(); }

	// HDC ���
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};
#endif