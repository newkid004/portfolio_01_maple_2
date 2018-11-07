#pragma once
#include "windowBase.h"

#define INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT 105.f

class itemBase;

class windowToolTip : public windowBase
{
private :
	enum e_IMG_TOOLTIP
	{
		IT_FRAME_
	};

private :
	itemBase* _bindItem;
	fPOINT _itemIconOffset;
	fPOINT _textMemoOffset;
	float _BodyHeight;



public :
	HRESULT init(void) override;
	void release(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

public :
	void renderNormal(void);
	void renderEquip(void);

public :
	void putBindItem(itemBase* item);

public:
	windowToolTip() {};
	~windowToolTip() {};
};

