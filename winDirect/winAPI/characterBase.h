#pragma once
#include "baseObject.h"
#include "patternBase.h"
#include "buffBase.h"
#include "state.h"

#define SPEED 200
#define GRAVITY 100
struct motionInfo
{
	int		maxFrameX;
	int		frameY;
	float	delay;
};
class characterBase :public baseObject
{
protected:
	patternBase * _currentPattern;				//���� ����

	list<buffBase*> _LbuffList;					//���� ����Ʈ
	list<buffBase*>::iterator _Libuff;

	map<MOVEMENT, motionInfo> _Mmotions;
	state		_state;
	stateBasic	_stateBasic;

protected:
	fPOINT		_velocity;						//�ӵ�			<- �߷� + ���� �ӵ� (�����ӵ�)
	rayStruct	_rayStruct;						//���� ����ü(�浹�˻� ����)

	bool		_isCollision;					//�浹�˻� ���� ����
protected:
	void setRayStruct();						//���� ���� �����϶� ���� ������
	void rayCollision();						//���� �浹

public:

	void setPattern(patternBase* pattern) { _currentPattern = pattern; }

	list<buffBase*>&getBuffList() { return _LbuffList; }
	patternBase* getPattern() { return _currentPattern; }

	stateBasic & getStat(void) { return _stateBasic; };

	void getVelocity() {

		setRayStruct();
		rayCollision();
	}

	characterBase() { _objectKind = (objDef::OBJECT)(_objectKind | (int)objDef::OBJECT_CHARACTER); };
	~characterBase() {};
};

