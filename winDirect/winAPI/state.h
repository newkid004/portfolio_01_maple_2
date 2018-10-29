#pragma once
#include "stdafx.h"
#include "classesDef.h"


enum MOVEMENT
{
	M_NONE				= 0x0000,
	M_WAKE				= 0x0001,
	M_DOWN				= 0x0002,
	M_JUMP				= 0x0004,
	M_ATTACK			= 0x0008,
	M_INV				= 0x0010,
	M_FLY				= 0x0020,
	M_DEAD			    = 0x0040,
	M_SPWAN				= 0x0080,
};

struct stateBasic
{
	unsigned int		hp;								//����	hp
	unsigned int		maxHp;							//���� �ִ� hp

	unsigned int		mp;								//����	mp
	unsigned int		maxMp;							//���� �ִ� mp

	NUM_REAL			atkMelee;						//���� �������ݷ�
	NUM_REAL			atkSpell;						//���� �������ݷ�

	NUM_REAL			defMelee;						//���� ��������
	NUM_REAL			defSpell;						//���� ��������

	NUM_REAL			moveSpeed;						//���� �̵��ӵ�
	NUM_REAL			jumpSpeed;						//���� �����ӵ�

	stateBasic()
	{
		ZeroMemory(this, sizeof(stateBasic));
	}
};

struct stateLimit
{
	classesDef::CLASSES	classes;						//�з�(����)
	int					Lv;								//����

	stateLimit()
	{
		ZeroMemory(this, sizeof(stateLimit));
	}
};

struct statePoint
{
	unsigned int		STR;							//�ֽ��� ��(����)
	unsigned int		DEX;							//�ֽ��� ��ø(�ü�)
	unsigned int		INT;							//�ֽ��� ����(������)
	unsigned int		LUK;							//�ֽ��� ��(����)

	statePoint()
	{
		ZeroMemory(this, sizeof(statePoint));
	}
};

struct statePersent
{
	NUM_REAL		damage;								//������ �ۼ�Ʈ
	NUM_REAL		meleeAtk;							//���ݷ� �ۼ�Ʈ
	NUM_REAL		spellAtk;							//����	�ۼ�Ʈ
	NUM_REAL		bossDamage;							//���� ���ݷ� �ۼ�Ʈ

	NUM_REAL		meleeDef;							//���� ���� �ۼ�Ʈ
	NUM_REAL		spellDef;							//���� ���� �ۼ�Ʈ

	NUM_REAL		allStatePoint;						//�ֽ���(���) �ۼ�Ʈ
	
	NUM_REAL		STR;								//�ֽ���(��) �ۼ�Ʈ
	NUM_REAL		DEX;								//�ֽ���(��ø) �ۼ�Ʈ
	NUM_REAL		INT;								//�ֽ���(����) �ۼ�Ʈ
	NUM_REAL		LUK;								//�ֽ���(��)  �ۼ�Ʈ

	NUM_REAL		critical;							//ũ��Ƽ��Ȯ�� �ۼ�Ʈ
	NUM_REAL		criticalDamage;						//ũ��Ƽ�õ����� �ۼ�Ʈ

	NUM_REAL		maxHp;								//�ִ� Hp �ۼ�Ʈ
	NUM_REAL		maxMp;								//�ִ� mp �ۼ�Ʈ

	statePersent()
	{
		ZeroMemory(this, sizeof(statePersent));
	}
};

struct state
{
	MOVEMENT			movement;

	stateLimit			stateLimit;

	stateBasic			permanentBasic;
	stateBasic			adjStateBasic;
	stateBasic			totalStateBasic;

	statePoint			permanentPoint;
	statePoint			itemStatePoint;
	statePoint			totalStatePoint;

	statePersent		permanentPersent;
	statePersent		itemStatePersent;
	statePersent		totalStatePersent;
};
