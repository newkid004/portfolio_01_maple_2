#pragma once
#include "stdafx.h"
#include "classesDef.h"

enum ELEMENT
{
	ELEMENT_NONE				= 0x0000,		//무속성
	ELEMENT_MELEE				= 0x0001,		//물리 속성
	ELEMENT_SPELL				= 0x0002,		//마법 속송
	ELEMENT_FIRE				= 0x0004,		//불 속성
	ELEMENT_ICE					= 0x0008,		//얼음 속성
	ELEMENT_ELECTRICITY			= 0x0010,		//전기 속성
	ELEMENT_POSION				= 0x0020,		//독 속성
	ELEMENT_LIGHT				= 0x0040,		//성 속성
	ELEMENT_DARKNESS			= 0x0080,		//암 속성
	ELEMENT_DARK				= 0x0100,		//흑 속성
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
	unsigned int		hp;								//현재	hp
	unsigned int		maxHp;							//현재 최대 hp

	unsigned int		mp;								//현재	mp
	unsigned int		maxMp;							//현재 최대 mp

	NUM_REAL			atkMelee;						//현재 물리공격력
	NUM_REAL			atkSpell;						//현재 마법공격력

	NUM_REAL			defMelee;						//현재 물리방어력
	NUM_REAL			defSpell;						//현재 마법방어력

	NUM_REAL			moveSpeed;						//현재 이동속도
	NUM_REAL			jumpSpeed;						//현재 점프속도

	ELEMENT				element;						//고유 속성

	stateBasic()
	{
		ZeroMemory(this, sizeof(stateBasic));
	}
};

struct stateLimit
{
	classesDef::CLASSES	classes;						//분류(직업)
	

	int					Lv;								//레벨

	stateLimit()
	{
		ZeroMemory(this, sizeof(stateLimit));
	}
};

struct statePoint
{
	unsigned int		STR;							//주스텟 힘(전사)
	unsigned int		DEX;							//주스텟 민첩(궁수)
	unsigned int		INT;							//주스텟 지력(마법사)
	unsigned int		LUK;							//주스텟 운(도적)

	statePoint()
	{
		ZeroMemory(this, sizeof(statePoint));
	}
};

struct subStatePoint
{
	unsigned int		STR;							//부스텟 힘
	unsigned int		DEX;							//부스텟 민첩
	unsigned int		INT;							//부스텟 지력
	unsigned int		LUK;							//부스텟 운

	subStatePoint()
	{
		ZeroMemory(this, sizeof(subStatePoint));
	}
};

struct statePersent
{
	NUM_REAL		damage;								//데미지 퍼센트
	NUM_REAL		meleeAtk;							//공격력 퍼센트
	NUM_REAL		spellAtk;							//마력	퍼센트
	NUM_REAL		bossDamage;							//보스 공격력 퍼센트
	NUM_REAL		defIgnore;							//방어력 무시 퍼센트
	NUM_REAL		elementToleranceIgnore;				//속성내성 무시 퍼센트
	NUM_REAL		finalDamage;						//최종 데미지 퍼센트

	NUM_REAL		meleeDef;							//물리 방어력 퍼센트
	NUM_REAL		spellDef;							//마법 방어력 퍼센트
	NUM_REAL		elementTolerance;					//속성 내성 퍼센트

	NUM_REAL		allStatePoint;						//주스텟(모든) 퍼센트
	
	NUM_REAL		STR;								//주스텟(힘) 퍼센트
	NUM_REAL		DEX;								//주스텟(민첩) 퍼센트
	NUM_REAL		INT;								//주스텟(지력) 퍼센트
	NUM_REAL		LUK;								//주스텟(운)  퍼센트

	NUM_REAL		critical;							//크리티컬확률 퍼센트
	NUM_REAL		criticalDamage;						//크리티컬데미지 퍼센트

	NUM_REAL		maxHp;								//최대 Hp 퍼센트
	NUM_REAL		maxMp;								//최대 mp 퍼센트
	NUM_REAL		proficiency;						//숙련도 퍼센트

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

	statePoint			permanentPoint;			// 직접 찍은 주스텟
	statePoint			itemStatePoint;			// 아이템 장비 스킬 버프 등등 다 적용시켜서 올라간 주스텟
	statePoint			totalStatePoint;		// 두개다 더한 토탈 주스텟

	subStatePoint		permanentSubPoint;		// 직접 찍은 주스텟
	subStatePoint		itemStateSubPoint;		// 아이템 장비 스킬 버프 등등 다 적용시켜서 올라간 주스텟
	subStatePoint		totalStateSubPoint;		// 두개다 더한 토탈 주스텟

	statePersent		permanentPersent;
	statePersent		itemStatePersent;
	statePersent		totalStatePersent;		//


};
