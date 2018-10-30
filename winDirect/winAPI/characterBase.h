#pragma once
#include "baseObject.h"
#include "patternBase.h"
#include "buffBase.h"
#include "state.h"


class characterBase :public baseObject
{
protected:
	patternBase * _currentPattern;				//���� ����

	list<buffBase*> _LbuffList;					//���� ����Ʈ
	list<buffBase*>::iterator _Libuff;

	stateBasic	_stateBasic;

protected:
	fPOINT		_velocity;						//�ӵ�			<- �߷� + �����ӵ� + ���� �ӵ� (�����ӵ�)
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
		_velocity = _currentPattern->getPatternVelocity();
		_velocity.y += 1.0f;

		setRayStruct();
		rayCollision();
	}

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void render() = 0;
	characterBase() { _objectKind = (objDef::OBJECT)(_objectKind | (int)objDef::OBJECT_CHARACTER); };
	~characterBase() {};
};

