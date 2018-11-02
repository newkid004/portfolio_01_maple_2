#include "stdafx.h"
#include "player.h"


HRESULT player::init(void)
{
	IMAGEMANAGER->add("p_body", L"image/character/player/body.png", 4, 2);
	IMAGEMANAGER->add("p_arm", L"image/character/player/arm.png", 4, 2);
	IMAGEMANAGER->add("p_head", L"image/character/player/head.png");
	IMAGEMANAGER->add("p_hair", L"image/character/player/hair.png");
	IMAGEMANAGER->add("p_face", L"image/character/player/face.png", 3, 25);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	setMotions(M_NONE, 3, 0, 0.510f);
	setMotions(M_WALK, 4, 1, 0.180f);

	_aniBody = new animation;
	_aniArm = new animation;

	_aniBody->init(IMAGEMANAGER->find("p_body"));
	_aniArm->init(IMAGEMANAGER->find("p_arm"));

	_aniBody->setFPS(1.0f / _Mmotions.find(M_NONE)->second.delay);
	_aniArm->setFPS(1.0f / _Mmotions.find(M_NONE)->second.delay);

	_aniBody->setPlayFrame(
		PointMake(0, _Mmotions.find(M_NONE)->second.frameY),
		PointMake(_Mmotions.find(M_NONE)->second.maxFrameX - 1, _Mmotions.find(M_NONE)->second.frameY),
		false, true);
	_aniArm->setPlayFrame(
		PointMake(0, _Mmotions.find(M_NONE)->second.frameY),
		PointMake(_Mmotions.find(M_NONE)->second.maxFrameX - 1, _Mmotions.find(M_NONE)->second.frameY),
		false, true);

 	_position = fPOINT(WINSIZEX / 2, WINSIZEY / 2);
	_state.movement = M_NONE;
	_dir = LEFT;
	return S_OK;
}

void player::release(void)
{
	_aniBody->release();
	_aniArm->release();

	SAFE_DELETE(_aniBody);
	SAFE_DELETE(_aniArm);
}

void player::update(void)
{
	if (KEYMANAGER->press(VK_SPACE))
	{
		_aniBody->start();
		_aniArm->start();
	}

	if (KEYMANAGER->press('s'))
	{
		_aniBody->stop();
		_aniArm->stop();
	}

	if (KEYMANAGER->down(VK_LEFT)) {
		_position.x -= TIMEMANAGER->getElapsedTime() * 200; _dir = LEFT;
	}
	else if (KEYMANAGER->down(VK_RIGHT)) {
		_position.x += TIMEMANAGER->getElapsedTime() * 200; _dir = RIGHT;
	}

	if (KEYMANAGER->press(VK_LEFT) || KEYMANAGER->press(VK_RIGHT))
	{
		_aniBody->stop();
		_aniArm->stop();
		_state.movement = M_WALK;
		setAnimation(_state.movement);
		_flip = _dir == RIGHT ? IMAGE_FLIP_VERTICAL : 0;
		
		IMAGEMANAGER->stateFlip(_flip);
		_aniBody->start();
		_aniArm->start();
	}
	
	if (!KEYMANAGER->down(VK_LEFT) && !KEYMANAGER->down(VK_RIGHT) &&
		!KEYMANAGER->down(VK_UP) && !KEYMANAGER->down(VK_DOWN) && 
		_state.movement != M_NONE)
	{
		_aniBody->stop();
		_aniArm->stop();
		_state.movement = M_NONE;
		setAnimation(_state.movement);
		_aniBody->start();
		_aniArm->start();
	}

}

void player::render(void)
{
	IMAGEMANAGER->statePos(_position);
	IMAGEMANAGER->find("p_body")->aniRender(_aniBody->update());
	IMAGEMANAGER->find("p_arm")->aniRender(_aniArm->update());
	IMAGEMANAGER->statePos(fPOINT(_position.x + 34, _position.y));
	IMAGEMANAGER->find("p_head")->render();
	IMAGEMANAGER->statePos(fPOINT(_position.x + 24, _position.y - 3));
	IMAGEMANAGER->find("p_face")->frameRender(fPOINT(0,0));
	IMAGEMANAGER->statePos(fPOINT(_position.x + 35, _position.y));
	IMAGEMANAGER->find("p_hair")->render();
}

void player::setMotions(MOVEMENT movement, int maxFrameX, int frameY, float delay)
{
	motionInfo _mInfo;
	_mInfo.maxFrameX = maxFrameX;
	_mInfo.frameY = frameY;
	_mInfo.delay = delay;

	_Mmotions.insert(make_pair(movement, _mInfo));
}

void player::setAnimation(MOVEMENT movement)
{
	_aniBody->setFPS(1.0f / _Mmotions.find(movement)->second.delay);
	_aniArm->setFPS(1.0f / _Mmotions.find(movement)->second.delay);

	_aniBody->setPlayFrame(
		PointMake(0, _Mmotions.find(movement)->second.frameY),
		PointMake(_Mmotions.find(movement)->second.maxFrameX - 1, _Mmotions.find(movement)->second.frameY),
		false, true);
	_aniArm->setPlayFrame(
		PointMake(0, _Mmotions.find(movement)->second.frameY),
		PointMake(_Mmotions.find(movement)->second.maxFrameX - 1, _Mmotions.find(movement)->second.frameY),
		false, true);
}
