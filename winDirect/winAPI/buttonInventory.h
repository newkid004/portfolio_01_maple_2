#pragma once
#include "buttonBase.h"

class windowInventory;

class buttonInventory : public buttonBase
{
protected:
	float _slotX;
	float _slotY;
	virtual itemBase* getRenderContent(void);

	virtual void updateDbClick(void) { /* 아이템 사용 */ };
public:
	virtual HRESULT init(fPOINT pos, windowInventory* bindWindow);
	virtual UI_LIST_ITER update(void);
	virtual void render(void) override;

	//int & getSlot(void) { return _slot; };

	buttonInventory() {}
	~buttonInventory() {}
};

struct tagInvenContent;

class buttonInvenTab : public buttonBase
{
protected:
	int _type;
	tagInvenContent* _bindContent;
protected:
	virtual HRESULT init(void) override { return S_OK; };

public:
	virtual HRESULT init(int tabType, windowInventory* bindWindow);
	virtual UI_LIST_ITER update(void) override { return _active(); };
	virtual void render(void) override;

protected:
	virtual void initProp(void);
	virtual void initActive(void);

public:
	int & getType(void) { return _type; };

public:
	buttonInvenTab(){}
	~buttonInvenTab(){}
};

class buttonInvenMeso : public buttonBase
{
private:
	int _frame;
public:
	HRESULT init(void);
	UI_LIST_ITER update(void);
	void render(void);

	buttonInvenMeso() {}
	~buttonInvenMeso() {}
};