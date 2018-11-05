#pragma once
#include "characterBase.h"
enum DIRECTION
{
	LEFT, RIGHT
};
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
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void keyUpdate(void);
	void setMotions(MOVEMENT movement, int maxFrameX, int frameY, float delay);
	void setAnimation(MOVEMENT movement);
	void setPartPosition(void);
	player();
	~player() {}
};

