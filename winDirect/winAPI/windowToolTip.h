#pragma once
#include "windowBase.h"

#define INTERVAL_DEFAULT_TOOLTIP_FRAME_HEIGHT 125.f

class itemBase;

class windowToolTip : public windowBase
{
private :
	enum e_IMG_TOOLTIP
	{
		IT_FRAME_TOP,
		IT_FRAME_BOT,
		IT_FRAME_BODY,
		IT_FRAME_DOT,
		IT_FRAME_DECO,

		IT_ITEM_BASE,
		IT_ITEM_DECO,
		IT_ITEM_SHADOW,

		IT_TOTAL_COUNT
	};

private :
	itemBase* _bindItem;
	fPOINT _itemIconOffset;
	fPOINT _textMemoOffset;
	float _bodyHeight;
	float _totalHeight;

	image* _imgRef[IT_TOTAL_COUNT];

public :
	HRESULT init(void) override;
	void release(void) override;
	UI_LIST_ITER update(void) override;
	void render(void) override;

public :
	void renderNormal(void);
	void renderEquip(void);

public :
	void setBindItem(itemBase* item);

public:
	windowToolTip() {};
	~windowToolTip() {};
};

