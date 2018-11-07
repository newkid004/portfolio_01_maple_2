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
	patternBase * _currentPattern;				//현재 패턴

	list<buffBase*> _LbuffList;					//버프 리스트
	list<buffBase*>::iterator _Libuff;

	map<MOVEMENT, motionInfo> _Mmotions;
	state		_state;
	stateBasic	_stateBasic;

protected:
	fPOINT		_velocity;						//속도			<- 중력 + 현재 속도 (최종속도)
	rayStruct	_rayStruct;						//광선 구조체(충돌검사 광선)

	bool		_isCollision;					//충돌검사 여부 변수
protected:
	void setRayStruct();						//광선 생성 움직일때 마다 생성됨
	void rayCollision();						//광선 충돌

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

