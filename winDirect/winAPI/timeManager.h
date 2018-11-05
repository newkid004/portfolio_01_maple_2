#pragma once
#include "singletonbase.h"
#include "timer.h"

class timeManager : public singletonBase <timeManager>
{
private:
	timer * _timer;

public:
	HRESULT init(void);
	void release(void);
	//������ ����
	void update(float lock = 0.0f);
	//�ش� HDC�� ���� ��´�
	void render(HDC hdc);
	void render(void);
	//��ü �ð� �����´�
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
	//������ ��� �ð�
	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	// FPS
	inline unsigned long getFPS(void) const { return _timer->getFrameRate(); }

	timeManager() {}
	~timeManager() {}
};