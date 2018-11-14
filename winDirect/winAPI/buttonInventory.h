#pragma once
#include "buttonBase.h"

class windowInventory;

class buttonInventory : public buttonBase
{
protected:
	float _slotX;
	float _slotY;
	virtual itemBase* getRenderContent(void);

	virtual void updateDbClick(void) { KEYMANAGER->setDBClick(GAMESYSTEM->findCallback("UI_shop_button_buy"), false); };
public:
	virtual HRESULT init(fPOINT pos, windowInventory* bindWindow);
	virtual UI_LIST_ITER update(void);
	virtual void render(void) override;

	//int & getSlot(void) { return _slot; };

	buttonInventory() {}
	~buttonInventory() {}
};

