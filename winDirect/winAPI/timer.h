#pragma once

class timer
{
private:
	bool			_isHardware;		//���� Ÿ�̸� ���� �ǳ�?
	float			_timeScale;			//����ð��� �����Ѵ�
	float			_timeElapsed;		//������ �ð��� ����ð��� �����
	__int64			_curTime;			//����ð�
	__int64			_lastTime;			//�����ð�
	__int64			_periodFrequency;	//�ð��ֱ�

	unsigned long 	_frameRate;			//FPS (�ʴ� ������ ��)
	unsigned long 	_FPSFrameCount;		//FPS ī��Ʈ
	float			_FPSTimeElapsed;
	float			_worldTime;			//������ ���۵� �� ����� ��ü �ð�

public:
	HRESULT init(void);
	//���� �ð��� ���
	void tick(float lockFPS = 0.0f);
	//���� FPS
	unsigned long getFrameRate(char* str = NULL) const;
	//������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }
	//��ü ��� �ð�
	inline float getWorldTime(void) const { return _worldTime; }

	timer() {}
	~timer() {}
};