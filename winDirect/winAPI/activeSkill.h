#pragma once
#include "skillBase.h"
class activeSkill:public skillBase
{
protected:
	NUM_REAL					_cooltime;						//��Ÿ��

	bool						_isBuff;						//�������� �ƴ����� ����
public:
	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	activeSkill() {}
	~activeSkill() {}
};


class buffSkill :public activeSkill
{
protected:
	NUM_REAL		_aliveTime;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void render();

	buffSkill() {}
	~buffSkill() {}
};

class attackSkill :public activeSkill
{
protected:
	NUM_REAL					_hitbyhitTime;					//������ �ߴ� �ӵ�

	int							_hitNum;						//�� ���Ϳ� ������ Ÿ��
	int							_hitMonsterNum;					//������ �ִ� ���� ��
public:
	virtual HRESULT init();
	virtual void release();
	virtual void render();

	attackSkill() {}
	~attackSkill() {}
};

class moveSkill : public activeSkill
{
protected:
	NUM_REAL			_velocity;
	NUM_REAL			_angle;
	NUM_REAL			_airTime;
public:	
	virtual HRESULT init();
	virtual void release();
	virtual void render();
};