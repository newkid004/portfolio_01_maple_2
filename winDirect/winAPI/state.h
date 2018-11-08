#pragma once
#include "stdafx.h"
#include "classesDef.h"

enum ELEMENT
{
	ELEMENT_NONE				= 0x0000,		//���Ӽ�
	ELEMENT_MELEE				= 0x0001,		//���� �Ӽ�
	ELEMENT_SPELL				= 0x0002,		//���� �Ӽ�
	ELEMENT_FIRE				= 0x0004,		//�� �Ӽ�
	ELEMENT_ICE					= 0x0008,		//���� �Ӽ�
	ELEMENT_ELECTRICITY			= 0x0010,		//���� �Ӽ�
	ELEMENT_POSION				= 0x0020,		//�� �Ӽ�
	ELEMENT_LIGHT				= 0x0040,		//�� �Ӽ�
	ELEMENT_DARKNESS			= 0x0080,		//�� �Ӽ�
	ELEMENT_DARK				= 0x0100,		//�� �Ӽ�
};

enum MOVEMENT
{
	M_NONE				= 0x0000,
	M_ATTACK			= 0x0001,
	M_WALK				= 0x0002,
	M_DOWN				= 0x0010,
	M_DOWNATTACK		= 0x0011,
	M_JUMP				= 0x0020,
	M_JUMPATTACK		= 0x0021,
	M_INV				= 0x0030,
	M_FLY				= 0x0040,
	M_DEAD			    = 0x0060,
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

	ELEMENT				element;						//���� �Ӽ�

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

struct subStatePoint
{
	unsigned int		STR;							//�ν��� ��
	unsigned int		DEX;							//�ν��� ��ø
	unsigned int		INT;							//�ν��� ����
	unsigned int		LUK;							//�ν��� ��

	subStatePoint()
	{
		ZeroMemory(this, sizeof(subStatePoint));
	}
};

struct statePersent
{
	NUM_REAL		damage;								//������ �ۼ�Ʈ
	NUM_REAL		meleeAtk;							//���ݷ� �ۼ�Ʈ
	NUM_REAL		spellAtk;							//����	�ۼ�Ʈ
	NUM_REAL		bossDamage;							//���� ���ݷ� �ۼ�Ʈ
	NUM_REAL		defIgnore;							//���� ���� �ۼ�Ʈ
	NUM_REAL		elementToleranceIgnore;				//�Ӽ����� ���� �ۼ�Ʈ
	NUM_REAL		finalDamage;						//���� ������ �ۼ�Ʈ

	NUM_REAL		meleeDef;							//���� ���� �ۼ�Ʈ
	NUM_REAL		spellDef;							//���� ���� �ۼ�Ʈ
	NUM_REAL		elementTolerance;					//�Ӽ� ���� �ۼ�Ʈ

	NUM_REAL		allStatePoint;						//�ֽ���(���) �ۼ�Ʈ
	
	NUM_REAL		STR;								//�ֽ���(��) �ۼ�Ʈ
	NUM_REAL		DEX;								//�ֽ���(��ø) �ۼ�Ʈ
	NUM_REAL		INT;								//�ֽ���(����) �ۼ�Ʈ
	NUM_REAL		LUK;								//�ֽ���(��)  �ۼ�Ʈ

	NUM_REAL		critical;							//ũ��Ƽ��Ȯ�� �ۼ�Ʈ
	NUM_REAL		criticalDamage;						//ũ��Ƽ�õ����� �ۼ�Ʈ

	NUM_REAL		maxHp;								//�ִ� Hp �ۼ�Ʈ
	NUM_REAL		maxMp;								//�ִ� mp �ۼ�Ʈ
	NUM_REAL		proficiency;						//���õ� �ۼ�Ʈ

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
	stateBasic			totalStateBasic;		//

	statePoint			permanentPoint;			// ���� ���� �ֽ���
	statePoint			itemStatePoint;			// ������ ��� ��ų ���� ��� �� ������Ѽ� �ö� �ֽ���
	statePoint			totalStatePoint;		// �ΰ��� ���� ��Ż �ֽ���

	subStatePoint		permanentSubPoint;		// ���� ���� �ֽ���
	subStatePoint		itemStateSubPoint;		// ������ ��� ��ų ���� ��� �� ������Ѽ� �ö� �ֽ���
	subStatePoint		totalStateSubPoint;		// �ΰ��� ���� ��Ż �ֽ���

	statePersent		permanentPersent;
	statePersent		itemStatePersent;
	statePersent		totalStatePersent;		//


};
