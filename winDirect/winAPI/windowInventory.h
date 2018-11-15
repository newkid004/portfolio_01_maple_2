#pragma once
#include "windowBase.h"

#define INVENX 4
#define INVENY 6

struct tagInvenContent
{
	int tabIndex;

	fPOINT firstItemPos;

	tagInvenContent()
	{
		tabIndex = 0;
	}
};

class buttonInventory;
class buttonInvenTab;

class windowInventory : public windowMovable
{
private:
	int _tabIndex;
	tagInvenContent _conInven;

	buttonInventory* _currentButton;
protected:
	void initButton(void);

public:
	HRESULT init(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

	void renderInfo(void);

	int getTabIndex() { return _tabIndex; }
	void selectInven(int index);

	tagInvenContent & getContentInven(void) { return _conInven; };

	buttonInventory*& getCurrentButton(void) { return _currentButton; };


	windowInventory() {}
	~windowInventory() {}
};

