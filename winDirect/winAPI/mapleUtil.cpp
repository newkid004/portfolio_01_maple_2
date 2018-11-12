#include "stdafx.h"
#include "mapleUtil.h"
#include "player.h"
#include "enemyBase.h"
#include "characterBase.h"


NUM_REAL mapleUtil::dmgP2M(player * sour, enemyBase * dest, float sourRatio)
{
	//���� ���ݷ� = ���ݷ� * (1 + (���ݷ�%)) * ���� ���

	//���� = 4(���� �ֽ���)+(���� �ν���)
	
	//���� �ֽ��� = {(AP�� ���� ������ ���� �ֽ���)*(1+������ ���%)+(���������� �ö� ���� �ֽ���)}

	//���� �ֽ��� = 4[���� �ֽ��� * (1+�ֽ���%+�ý���%)+(���Ͽ�)+(�ɺ�)+(�����۽���)]

	//���� �ν���[{(AP�� ���� ������ ���� �ν���)*(1+�����ÿ��%)+(���������� �ö� ���� �ν���)}*(1+�ν���%+�ý���%)+(���Ͽ�)+(�����۽���)]

	//�߰� ������
	//1 + (������%)+(����������%)

	//ũ��Ƽ�� 
	//(�������ݷ�)*(����)*(�߰�������)*0.5*(������)				ũ��Ƽ��x
	//(�������ݷ�)*(����)*(�߰�������)*0.5*(50%+1.35)*(������)	ũ��Ƽ��o

	//����� ���� ���밪
	//1 - (������ ���� �����%)

	//���� ���� �����
	//1 - (���� �����)*(1 - ĳ������ ���� ������%)

	//���ط�
	/*
	(���� ���ݷ�)*(����)*(�߰� ������)*(ũȮ%)*{(ũ��%)+1.35}*(����� ���� ���밪)*(���� ������)+
	(���� ���ݷ�)*(����)*(�߰� ������)*{(ũ��Ƽ���� �Ͼ�� ���� Ȯ��%)}*(����� ���� ���밪)*(���� ������)
	*/

	//��� ������ = [�޽��� �� ��ų �����% �� (1+�����%+xx���� �� �����) �� {1 - �����% �� (1-�湫%)}] ��
	//{ũȮ �� (1.35+ũ��%) + (1-ũȮ%)} ��
	//(1+���õ�%) �� {1 - (�Ӽ� ����%-�Ӽ� ���� ����%)} /
	//{200 �� (1+�����%)}
	
	//������ = [ (�ֽ��� * 4 + �ν���) * �� ���ݷ� * ������ * ����������� / 100 ] * 
	//(��ų �۵� / 100) * (ũ��Ƽ�� �ߵ���) ũ��Ƽ�� ������ ���� * [ (100 + ���ݷ�%) / 100 ] * [ (100 + ������% + ����%) / 100 ] *
	//����� ���� ���� * ���� ���� * �Ӽ� ���� * ���õ� ���� * [ (��� ���������� ��갪% + 100) / 100 ]
	
	//ũ������ = [ (120 + ũ��Ƽ�� ������) / 100 ] ~ [ (150 + ũ��Ƽ�� ������) / 100]
	
	//���� �湫 = 100 - ( ���� ����� - ���� ����� * �� ����� ����) (%) //������ 0
	
	// �⺻������ ������� 25%, �ٰŸ� ������ 20%, ������ ������ ���� ���Ÿ� ������ 15%�� ������ ��� �����͸� �迭 ��ų�� �������ϸ� 70%
	NUM_REAL dmg = 0;
	//���� ���ݷ� o
	NUM_REAL finalAtkPower = NULL;
	//���� �ֽ��� o
	NUM_REAL pureMainStat = NULL;
	//���� �ν��� o
	NUM_REAL puerSubStat = NULL;
	//���� �ֽ��� o
	NUM_REAL finalMainStat = NULL;
	//���� �ν��� o
	NUM_REAL finalSubStat = NULL;
	//���� ���� ����� o
	NUM_REAL ignoreArmor = NULL;
	//����� ���� ���밪 x
	NUM_REAL ignoreDef = NULL;
	//���� x
	NUM_REAL stat = NULL;
	//�߰� ������x
	NUM_REAL plusDmg = NULL;
	//���ط�
	NUM_REAL hitDmg = NULL;
	//��� ����� x
	NUM_REAL averageDamage = NULL;
	auto i = ((characterBase*)sour);
	if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_WIZARD)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkSpell * (1 + i->getStat().totalStatePersent.spellAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.INT * 1/* +�޿�% */ + i->getStat().itemStatePoint.INT;
		puerSubStat = i->getStat().permanentSubPoint.LUK * 1/* +�޿�% */ + i->getStat().itemStateSubPoint.LUK;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.INT + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.LUK + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.spellDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if(i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_WARRIER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.STR * 1/* +�޿�% */ + i->getStat().itemStatePoint.STR;
		puerSubStat = i->getStat().permanentSubPoint.DEX * 1/* +�޿�% */ + i->getStat().itemStateSubPoint.DEX;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_ARCHER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.DEX * 1/* +�޿�% */ + i->getStat().itemStatePoint.DEX;
		puerSubStat = i->getStat().permanentSubPoint.STR * 1/* +�޿�% */ + i->getStat().itemStateSubPoint.STR;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_THIEF)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.LUK * 1/* +�޿�% */ + i->getStat().itemStatePoint.LUK;
		puerSubStat = i->getStat().permanentSubPoint.DEX * 1/* +�޿�% */ + i->getStat().itemStateSubPoint.DEX;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.LUK + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 4 * (puerSubStat * (1 + i->getStat().itemStatePersent.DEX + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	else if (i->getStat().stateLimit.classes == classesDef::CLASSES::CLASSES_BEGINNER)
	{
		finalAtkPower = (i->getStat().totalStateBasic.atkMelee * (1 + i->getStat().totalStatePersent.meleeAtk) * 1.0);
		pureMainStat = i->getStat().permanentPoint.STR * 1/* +�޿�% */ + i->getStat().itemStatePoint.STR;
		puerSubStat = 1;
		finalMainStat = 4 * (pureMainStat * (1 + i->getStat().itemStatePersent.STR + i->getStat().itemStatePersent.allStatePoint) + 0 + 0 + 0);
		finalSubStat = 1;
		ignoreArmor = 1 - dest->getStat().totalStatePersent.meleeDef*(1 - i->getStat().totalStatePersent.defIgnore);
	}
	ignoreDef = 1 - ignoreArmor;
	stat = 4 * finalMainStat + finalSubStat;
	plusDmg = 1 + i->getStat().totalStatePersent.damage + i->getStat().totalStatePersent.bossDamage; //�����ƴҽ� ���������� 0���� �ֱ�
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
	���� �⺻ �����%
	�Ϲݸ��� 10%
	���ĸ��� 25%
	�����,�������� ���ı�� 35%
	�븻����,ȥ���� 40%
	�븻����,�ű׳ʽ� 50%
	�븻 ��ũ��ü 70%
	���� 100%
	ī���� ��ũ�� ��ü 180%
	ī���� ���� 300%
	���
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
	//�ս��� = ���õ� �� �޽���
	//�޽��� = ���� ��� �� (4���� ���� + �� ����) �� 0.01 �� (���ݷ�,����) �� (1+������) �� (1+���� ������)

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
	//�޽���
	NUM_REAL backStatDamage = 1.0*(4 * *mainStat + *subStat)*0.01 * (*atkType) * (1 + i->getStat().totalStatePersent.damage);
	//�ս���
	NUM_REAL frontStatDamage = i->getStat().totalStatePersent.proficiency * backStatDamage;
	return fPOINT(backStatDamage, frontStatDamage);
}
