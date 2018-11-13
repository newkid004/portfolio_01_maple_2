#pragma once
#include "baseObject.h"
#include "itemDef.h"
#include "state.h"

#define INTERVAL_ITEM_IN_INVENTORY		fPOINT(36.f,35.f)
#define INTERVAL_INVENTORY_TASK_BAR		fPOINT(5.0f, 10.0f)

struct itemContentBase
{
	int type;

	image* img;

	fPOINT frame;

	wstring name;
	wstring memo;

	__int64 price;

	itemContentBase() :
		type(0),
		img(NULL),
		frame(0.f),
		price(0)
	{}
	virtual ~itemContentBase() {};

	virtual void operator=(itemContentBase i) { this->operator=(&i); }
	virtual void operator=(itemContentBase* i) 
	{
		this->type			= i->type;
		this->img			= i->img;
		this->frame			= i->frame;
		this->name			= i->name;
		this->memo			= i->memo;
		this->price = i->price;
	};
};

// ----- equipment ----- //
struct tagItemEquipmentInfo
{
	image* img;
	fPOINT offset;
	POINT frame;
};

struct itemContentEquip : public itemContentBase
{
	stateLimit limit;
	stateBasic basic;
	statePoint point;
	itemContentEquip() : itemContentBase() { type |= itemDef::ITEM_TYPE_EQUIP | itemDef::ITEM_TYPE_USEABLE; }

	virtual void operator=(itemContentEquip i) { itemContentBase::operator=(&i); }
	virtual void operator=(itemContentEquip *i) 
	{
		itemContentBase::operator=(i);
		this->limit = i->limit;
		this->basic = i->basic;
		this->point = i->point;
	};
};

struct itemContentWeapon : public itemContentEquip {
	itemContentWeapon() : itemContentEquip() { type |= itemDef::ITEM_TYPE_WEAPON; }
};
struct itemContentArmor : public itemContentEquip {
	itemContentArmor() : itemContentEquip() { type |= itemDef::ITEM_TYPE_ARMOR; }
};

// ----- consumeable ----- //
struct itemContentConsume : public itemContentBase
{
	int count;

	virtual void operator=(itemContentConsume i) { this->operator=(&i); };
	virtual void operator=(itemContentConsume* i)
	{
		itemContentBase::operator=(i);
		this->count = i->count;
	};
};

// ----- item Base ----- //
class itemBase : public baseObject
{
protected :
	itemContentBase * _content = NULL;

public :
	virtual HRESULT init(void) { return S_OK; };
	virtual void release(void) { SAFE_DELETE(_content); };
	virtual void update(void) {};
	virtual void render(void) {};

public :
	virtual void render2Field(float alphaRatio = 1.f);
	virtual void render2shop(fPOINT posOffset, int placement);
	virtual void render2Inventory(fPOINT posOffset, fPOINT placement);

public :
	itemContentBase*& getContent(void)				{ return _content; };
	static int getContentType(itemBase* i)			{ return i->getContent()->type & itemDef::ITEM_TYPE_CHECK; };
	static int getContentType(itemContentBase* i)	{ return i->type & itemDef::ITEM_TYPE_CHECK; };
	static int getInventoryTap2type(int type);

public:
	itemBase() {};
	~itemBase() {};
};

class itemEquip : public itemBase{};

class itemWeapon : public itemEquip
{
public :
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(void);

public:
	itemWeapon() {};
	~itemWeapon() {};
};

class itemArmor : public itemEquip
{
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(void);

public:
	itemArmor() {};
	~itemArmor() {};
};

class itemConsume :public itemBase
{

};

class itemOthers :public itemBase
{

};

class itemCash :public itemBase
{

};