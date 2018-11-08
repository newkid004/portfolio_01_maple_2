#pragma once
#include "state.h"

class skillBase
{
public:
	enum class SKILLTYPE
	{
		ACTIVE, PASSIVE
	};

protected:
	typedef struct spend {
		NUM_REAL					_spendHp;						//hp �Ҹ� ���
		NUM_REAL					_spendMP;						//mp �Ҹ� ���

		NUM_REAL					_spendMoney;					//�� �Ҹ� ���

		int							_spendWeapon_Thief;				//ǥâ �Ҹ� ���
		int							_spendWeapon_Archer;			//ȭ�� �Ҹ� ���

	}SPEND;

protected:
	wstring						_name;								//��ų �̸�
	wstring						_explain;							//��ų ����

	SKILLTYPE					_skillType;							//��ų Ÿ�� (�нú�,��Ƽ��)		<- �ǵ��� ����
	SPEND						_spendStruct;						//��ų ��� ��� ����ü

	stateBasic					_adjStateBasic;						//hp,mp,���ݷ�,����,����,�������� ���� ���� ��ġ
	statePoint					_adjStatePoint;						//�ֽ���(str,dex,int,luk)���� ��ġ
	statePersent				_adjStatePersent;					//�ۼ�Ʈ ��ġ(�ֽ���,���ݷ�,����,maxHp,maxMp,ũ��Ƽ�� Ȯ��,ũ��Ƽ�� ������, �ѵ�����,�������ݷµ����� etc..)

	int							_Lv;
public:
	
	SKILLTYPE	getSkillType()		{ return _skillType; }
	SPEND		getSpendStruct()	{ return _spendStruct; }

	virtual HRESULT	init();
	virtual void release();
	virtual void render();

	skillBase() {};
	~skillBase() {};
};

