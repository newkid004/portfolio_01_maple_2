#pragma once
#include "characterBase.h"
enum DIRECTION
{
	LEFT, RIGHT
};

enum e_PLAYER_INVENTORY_TAB
{
	PLAYER_INVENTORY_TAB_EQUIPMENT,
	PLAYER_INVENTORY_TAB_CONSUMABLE,
	PLAYER_INVENTORY_TAB_FIT,
	PLAYER_INVENTORY_TAB_ETC,
	PLAYER_INVENTORY_TAB_CACHE,
	PLAYER_INVENTORY_TAB_COUNT
};
class inventory;

class player : characterBase
{
private:
	animation* _aniBody;
	animation* _aniArm;
	DIRECTION  _dir;
	fPOINT	   _headPosition;
	fPOINT     _facePosition;
	fPOINT     _hairPosition;
	int _flip;

	inventory*	_inven[PLAYER_INVENTORY_TAB_COUNT];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void initInventory(void);
	void releaseInventory(void);

public :
	void keyUpdate(void);
	void setMotions(MOVEMENT movement, int maxFrameX, int frameY, float delay);
	void setAnimation(MOVEMENT movement);
	void setPartPosition(void);

public :	// ----- inventory ----- //
	inventory*& getInventory(int index) { return _inven[index]; };

public :
	player();
	~player() {}
};

