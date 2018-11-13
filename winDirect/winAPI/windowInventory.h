#pragma once
#include "windowBase.h"

#define INVENX 4
#define INVENY 6

#define BUTTON

struct tagShopContent;

class buttonInventory;
class windowInventory : public windowBase
{
private:

	buttonInventory* _currentButton;
protected:
	void initButton(void);



public:
	HRESULT init(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

	void renderInfo(void);

	buttonInventory*& getCurrentButton(void) { return _currentButton; };

	
	windowInventory() {}
	~windowInventory() {}
};

