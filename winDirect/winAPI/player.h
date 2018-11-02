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
	int _flip;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMotions(MOVEMENT movement, int maxFrameX, int frameY, float delay);
	void setAnimation(MOVEMENT movement);
	player() {}
	~player() {}
};

