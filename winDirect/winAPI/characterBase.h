#pragma once
#include "baseObject.h"
#include "state.h"

#define SPEED 200
#define GRAVITY 5

class patternBase;
class buffBase;

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
	state		_state;							//
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

	virtual stateBasic & getBasicStat(void) { return _stateBasic; };
	virtual state & getStat(void) { return _state; };

	void getVelocity() {

		setRayStruct();
		rayCollision();
	}

	characterBase() { _objectKind = (objDef::OBJECT)(_objectKind | (int)objDef::OBJECT_CHARACTER); };
	~characterBase() {};
};

