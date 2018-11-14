#pragma once
#include "gameNode.h"
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
class fieldBase;
class player : public characterBase
{
private:
	animation* _aniBody;
	animation* _aniArm;
	animation* _aniLhand;
	DIRECTION  _dir;
	MOVEMENT   _movement[2];
	fPOINT	   _headPosition;
	fPOINT     _facePosition;
	fPOINT     _hairPosition;
	fPOINT	   _tempPos;
	fieldBase* _fieldBase;
	ID2D1SolidColorBrush*   g_pBlackBrush;
	inventory* _inven[PLAYER_INVENTORY_TAB_COUNT];
	__int64		_money;
	int			_statPoint = 0;

	int		 _flip;
	NUM_REAL _acc;
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
	void setMovement(MOVEMENT movement);
	void setPartPosition(void);
	void aniStart(void);
	void aniStop(void);
	void move(void);
	void jump(void);
	void pixelCollision(void);
	void convertToFixedVel(void) { _velocity *= TIMEMANAGER->getElapsedTime(); }
	void convertToUnFixedVel(void) { _velocity /= TIMEMANAGER->getElapsedTime(); }

public :	// ----- inventory, item ----- //
	inventory*& getInventory(int index) { return _inven[index]; };
	__int64 & getMoney(void) { return _money; };
	int & getStatPoint(void) { return _statPoint; };

public :
	player();
	~player() {}
};

