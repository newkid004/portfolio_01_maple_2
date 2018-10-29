#include "stdafx.h"
#include "timer.h"
#include <MMSystem.h>

//TimeGetTime �Լ��� ����ϱ� ���� ���̺귯��
#pragma comment (lib, "winmm.lib")

HRESULT timer::init(void)
{
	//_periodFrequency ���� �ʴ� �ľ� �� �� �ִ� �ð��� ����
	//�и��������� ��� �����ϴٸ� 1000�� ���� ��
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//�ʴ� �ð��� ��� �� �� �ִ� �ð��ֱ�
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		//timeGetTime�� �и����� ���� �ð����� �ʴ� 1000
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;
	_timeElapsed = 0;

	return S_OK;
}

//���� �ð��� ����Ѵ�
void timer::tick(float lockFPS)
{
	//�����ǳ�?
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//�������� ������ Time�Լ��� ���
		_curTime = timeGetTime();
	}

	//������ �ð��� ����ð��� ����� �����Ѵ�
	_timeElapsed = (_curTime - _lastTime) * _timeScale;


	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			//������ �ð��� ����ð��� ������� �����Ѵ�
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//������ �ð��� ����Ѵ�
	_lastTime = _curTime;

	//�ʴ� ������ ī��Ʈ ������Ų��
	_FPSFrameCount++;

	//�ʴ� ������ �ð� ����� �����Ѵ�
	_FPSTimeElapsed += _timeElapsed;

	//��ü �ð� ����� �����Ѵ�
	_worldTime += _timeElapsed;

	//������ 1�ʸ��� �ʱ�ȭ �Ѵ�
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

//���� FPS
unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "fps : %d", _frameRate);
	}
	return _frameRate;
}