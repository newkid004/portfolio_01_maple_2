#include "stdafx.h"
#include "mapleUtil.h"
#include "player.h"
#include "enemyBase.h"
#include "characterBase.h"


NUM_REAL mapleUtil::dmgP2M(player * sour, enemyBase * dest, float sourRatio)
{
	//최종 공격력 = 공격력 * (1 + (공격력%)) * 무기 상수

	//스탯 = 4(최종 주스텟)+(최종 부스텟)
	
	//순수 주스텟 = {(AP를 직접 투자한 순수 주스탯)*(1+메이플 용사%)+(아이템으로 올라간 순수 주스탯)}

	//최종 주스텟 = 4[순수 주스텟 * (1+주스탯%+올스탯%)+(유니온)+(심볼)+(하이퍼스탯)]

	//최종 부스텟[{(AP를 직접 투자한 순수 부스탯)*(1+메이플용사%)+(아이템으로 올라간 순수 부스탯)}*(1+부스탯%+올스탯%)+(유니온)+(하이퍼스탯)]

	//추가 데미지
	//1 + (데미지%)+(보스데미지%)

	//크리티컬 
	//(최종공격력)*(스탯)*(추가데미지)*0.5*(나머지)				크리티컬x
	//(최종공격력)*(스탯)*(추가데미지)*0.5*(50%+1.35)*(나머지)	크리티컬o

	//방어율 무시 적용값
	//1 - (몬스터의 최종 방어율%)

	//몬스터 최종 방어율
	//1 - (원래 방어율)*(1 - 캐릭터의 방어력 무시율%)

	//피해량
	/*
	(최종 공격력)*(스탯)*(추가 데미지)*(크확%)*{(크뎀%)+1.35}*(방어율 무시 적용값)*(최종 데미지)+
	(최종 공격력)*(스탯)*(추가 데미지)*{(크리티컬이 일어나지 않을 확률%)}*(방어율 무시 적용값)*(최종 데미지)
	*/

	//평균 데미지 = [뒷스공 × 스킬 대미지% × (1+대미지%+xx공격 시 대미지) × {1 - 방어율% × (1-방무%)}] ×
	//{크확 × (1.35+크댐%) + (1-크확%)} ×
	//(1+숙련도%) × {1 - (속성 내성%-속성 내성 무시%)} /
	//{200 × (1+대미지%)}
	
	//데미지 = [ (주스탯 * 4 + 부스탯) * 총 공격력 * 무기상수 * 직업보정상수 / 100 ] * 
	//(스킬 퍼뎀 / 100) * (크리티컬 발동시) 크리티컬 데미지 보정 * [ (100 + 공격력%) / 100 ] * [ (100 + 데미지% + 보공%) / 100 ] *
	//방어율 무시 보정 * 렙차 보정 * 속성 보정 * 숙련도 보정 * [ (모든 최종데미지 계산값% + 100) / 100 ]
	
	//크뎀보정 = [ (120 + 크리티컬 데미지) / 100 ] ~ [ (150 + 크리티컬 데미지) / 100]
	
	//몬스터 방무 = 100 - ( 몬스터 방어율 - 몬스터 방어율 * 총 방어율 무시) (%) //음수시 0
	
	// 기본적으로 마법사는 25%, 근거리 직업은 20%, 마법사 직업군 제외 원거리 직업은 15%로 시작해 모든 마스터리 계열 스킬을 마스터하면 70%
	NUM_REAL dmg = 0;
	//최종 공격력 o
	NUM_REAL finalAtkPower = NULL;
	//순수 주스텟 o
	NUM_REAL pureMainStat = NULL;
	//순수 부스텟 o
	NUM_REAL puerSubStat = NULL;
	//최종 주스텟 o
	NUM_REAL finalMainStat = NULL;
	//최종 부스텟 o
	NUM_REAL finalSubStat = NULL;
	//몬스터 최종 방어율 o
	NUM_REAL ignoreArmor = NULL;
	//방어율 무시 적용값 x
	NUM_REAL ignoreDef = NULL;
	//스탯 x
	NUM_REAL stat = NULL;
	//추가 데미지x
	NUM_REAL plusDmg = NULL;
	//피해량
	NUM_REAL hitDmg = NULL;
	//평균 대미지 x
	NUM_REAL averageDamage = NULL;
	auto i = ((characterBase*)sour);
	if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_WIZARD)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkSpell * (1 + i->getStat().totalStatePersent.spellAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.INT * 1/* +메용% */ + i->getStat().itemStatePoint.INT;
		puerSubStat = i->getStat().permanentSubPoint.LUK * 1/* +메용% */ + i->getStat().itemStateSubPoint.LUK;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.INT + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.LUK + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.spellDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if(i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_WARRIER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.STR * 1/* +메용% */ + i->getStat().itemStatePoint.STR;
		puerSubStat = i->getStat().permanentSubPoint.DEX * 1/* +메용% */ + i->getStat().itemStateSubPoint.DEX;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_ARCHER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.DEX * 1/* +메용% */ + i->getStat().itemStatePoint.DEX;
		puerSubStat = i->getStat().permanentSubPoint.STR * 1/* +메용% */ + i->getStat().itemStateSubPoint.STR;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_THIEF)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.LUK * 1/* +메용% */ + i->getStat().itemStatePoint.LUK;
		puerSubStat = i->getStat().permanentSubPoint.DEX * 1/* +메용% */ + i->getStat().itemStateSubPoint.DEX;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.LUK + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_BEGINNER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.STR * 1/* +메용% */ + i->getStat().itemStatePoint.STR;
		puerSubStat = 1;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 1;
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	ignoreDef = 1 - ignoreArmor;
	stat = 4 * finalMainStat + finalSubStat;
	plusDmg = 1 + i->getStat().totalStatePersent.damage + i->getStat().totalStatePersent.bossDamage; //보스아닐시 보스데미지 0으로 넣기
	hitDmg = finalAtkPower*stat*plusDmg*i->getStat().totalStatePersent.critical*(i->getStat().totalStatePersent.criticalDamage + 1.35)*ignoreDef * 1 +
		finalAtkPower*stat*plusDmg*(100 - i->getStat().totalStatePersent.critical)*ignoreDef * 1;
	averageDamage = (statDamage(sour).x  * sourRatio * (1 + i->getStat().totalStatePersent.damage + 0) * (1 - dest->getStat().totalStatePersent.spellDef * (1 - i->getStat().totalStatePersent.defIgnore))) *
		(i->getStat().totalStatePersent.critical * (1.35 + i->getStat().totalStatePersent.criticalDamage) + (1 - i->getStat().totalStatePersent.critical)) *
		(1 + i->getStat().totalStatePersent.proficiency) * (1 - (dest->getStat().totalStatePersent.elementTolerance - i->getStat().totalStatePersent.elementToleranceIgnore)) /
		(200 * (1 + i->getStat().totalStatePersent.damage));
	return dmg;
}

NUM_REAL mapleUtil::dmgM2P(enemyBase * sour, player * dest, float sourRatio)
{
	/*
	몬스터 기본 방어율%
	일반몬스터 10%
	몬파몬스터 25%
	무기고,연무장의 정식기사 35%
	노말자쿰,혼테일 40%
	노말힐라,매그너스 50%
	노말 핑크빈본체 70%
	여제 100%
	카오스 핑크빈 본체 180%
	카오스 벨룸 300%
	등등
	*/
	NUM_REAL dmg = 0;
	if (((characterBase*)sour)->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_WIZARD)
	{

	}
	else
	{

	}
	return dmg;
}

fPOINT mapleUtil::statDamage(player * info)
{
	//앞스공 = 숙련도 × 뒷스공
	//뒷스공 = 무기 상수 × (4×주 스탯 + 부 스탯) × 0.01 × (공격력,마력) × (1+데미지) × (1+최종 데미지)

	auto i = ((characterBase*)info);

	unsigned int* mainStat = NULL;
	unsigned int* subStat = NULL;
	NUM_REAL* atkType = NULL;

	if ((int)i->getStat().stateLimit.classes & (int)classesDef::CLASSES::CLASSES_WIZARD)
	{
		mainStat = &i->getStat().totalStatePoint.INT;
		subStat = &i->getStat().totalStatePoint.LUK;
		atkType = &i->getStat().totalStateBasic.atkSpell;
		
	}
	else if ((int)i->getStat().stateLimit.classes & (int)classesDef::CLASSES::CLASSES_WARRIER)
	{
		mainStat = &i->getStat().totalStatePoint.STR;
		subStat = &i->getStat().totalStatePoint.DEX;
		atkType = &i->getStat().totalStateBasic.atkMelee;
	}
	else if ((int)i->getStat().stateLimit.classes & (int)classesDef::CLASSES::CLASSES_ARCHER)
	{
		mainStat = &i->getStat().totalStatePoint.DEX;
		subStat = &i->getStat().totalStatePoint.STR;
		atkType = &i->getStat().totalStateBasic.atkMelee;
	}
	else if ((int)i->getStat().stateLimit.classes & (int)classesDef::CLASSES::CLASSES_THIEF)
	{
		mainStat = &i->getStat().totalStatePoint.LUK;
		subStat = &i->getStat().totalStatePoint.DEX;
		atkType = &i->getStat().totalStateBasic.atkMelee;
	}
	else if ((int)i->getStat().stateLimit.classes & (int)classesDef::CLASSES::CLASSES_BEGINNER)
	{
		mainStat = &i->getStat().totalStatePoint.STR;
		subStat = &i->getStat().totalStatePoint.DEX;
		atkType = &i->getStat().totalStateBasic.atkMelee;
	}
	//뒷스공
	NUM_REAL backStatDamage = 1.0*(4 * *mainStat + *subStat)*0.01 * (*atkType) * (1 + i->getStat().totalStatePersent.damage);
	//앞스공
	NUM_REAL frontStatDamage = i->getStat().totalStatePersent.proficiency * backStatDamage;
	return fPOINT(backStatDamage, frontStatDamage);
}
