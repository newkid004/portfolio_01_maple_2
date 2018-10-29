#include "stdafx.h"
#include "timeManager.h"

HRESULT timeManager::init(void)
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

//������ ����
void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

//�ش� HDC�� ���� ��´�
void timeManager::render(HDC hdc)
{
	char str[256];
	std::string strFrame;

	SetBkMode(hdc, TRANSPARENT);

	COLORREF oColor = GetTextColor(hdc);
	int oAlign = GetTextAlign(hdc);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetTextAlign(hdc, TA_LEFT);

#ifdef _DEBUG
	if (_timer != NULL)
	{
		//������ ��´�
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		// //���� Ÿ�� ��´�
		// sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		// TextOut(hdc, 0, 20, str, strlen(str));
		// 
		// //���� �ð� ��´�
		// sprintf_s(str, "ElapsedTime : %f", _timer->getElapsedTime());
		// TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if (_timer != NULL)
	{
		//������ ��´�
		sprintf_s(str, "FramePerSec : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif

	SetTextColor(hdc, oColor);
	SetTextAlign(hdc, oAlign);
}