#include "stdafx.h"
#include "player.h"

#include "inventory.h"

player::player() : _headPosition(fPOINT(0.0f, 0.0f)),
				   _facePosition(fPOINT(0.0f, 0.0f)),
				   _hairPosition(fPOINT(0.0f, 0.0f))
{
}

HRESULT player::init(void)
{
	IMAGEMANAGER->add("p_body", L"image/character/player/body.png", 4, 3);
	IMAGEMANAGER->add("p_arm", L"image/character/player/arm.png", 4, 3);
	IMAGEMANAGER->add("p_head", L"image/character/player/head.png");
	IMAGEMANAGER->add("p_hair", L"image/character/player/hair.png");
	IMAGEMANAGER->add("p_face", L"image/character/player/face.png", 3, 25);
	IMAGEMANAGER->add("p_lHand", L"image/character/player/lHand.png", 4, 3);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	setMotions(M_NONE, 3, 0, 0.510f);
	setMotions(M_WALK, 4, 1, 0.180f);
	setMotions(M_JUMP, 0, 2, 0);

	_aniBody = new animation;
	_aniArm = new animation;
	_aniLhand = new animation;

	_aniBody->init(IMAGEMANAGER->find("p_body"));
	_aniArm->init(IMAGEMANAGER->find("p_arm"));
	_aniLhand->init(IMAGEMANAGER->find("p_lHand"));
	
 	_position = fPOINT(WINSIZEX / 2, WINSIZEY / 2);
	_state.movement = M_NONE;
	_movement[0] = _movement[1] = M_NONE;
	_dir = LEFT;
	setAnimation(_state.movement);
	initInventory();

	return S_OK;
}

void player::release(void)
{
	_aniBody->release();
	_aniArm->release();
	_aniLhand->release();

	SAFE_DELETE(_aniBody);
	SAFE_DELETE(_aniArm);
	SAFE_DELETE(_aniLhand);

	releaseInventory();
}

void player::update(void)
{
	keyUpdate();
	setPartPosition();

	switch (_movement[0] | _movement[1])
	{
	case M_NONE: _state.movement = M_NONE; break;
	case M_WALK: _state.movement = M_WALK; break;
	case M_DOWN: _state.movement = M_DOWN; break;
	case M_JUMP: _state.movement = M_JUMP; break;
	case M_DOWNATTACK: _state.movement = M_DOWNATTACK; break;
	case M_JUMPATTACK: _state.movement = M_JUMPATTACK; break;
	}
}

void player::render(void)
{
	_flip = _dir == RIGHT ? IMAGE_FLIP_VERTICAL : 0;
	IMAGEMANAGER->statePos(_position);
	IMAGEMANAGER->stateFlip(_flip);
	IMAGEMANAGER->find("p_body")->aniRender(_aniBody->update());
	IMAGEMANAGER->find("p_arm")->aniRender(_aniArm->update());
	IMAGEMANAGER->find("p_lHand")->aniRender(_aniLhand->update());
	IMAGEMANAGER->statePos(_headPosition);
	IMAGEMANAGER->find("p_head")->render();
	IMAGEMANAGER->statePos(_facePosition);
	IMAGEMANAGER->find("p_face")->frameRender(fPOINT(0,0));
	IMAGEMANAGER->statePos(_hairPosition);
	IMAGEMANAGER->find("p_hair")->render();
}

void player::initInventory(void)
{
	for (auto inven : _inven)
	{
		inven = new inventory;
		inven->init();
	}
}

void player::releaseInventory(void)
{
	for (auto inven : _inven)
	{
		inven->release();
		SAFE_DELETE(inven);
	}
}

void player::keyUpdate(void)
{
	_movement[0] = _movement[1] = M_NONE;
	if (KEYMANAGER->press(VK_SPACE))
	{
		_aniBody->start();
		_aniArm->start();
		_aniLhand->start();
	}

	if (KEYMANAGER->press('s'))
	{
		_aniBody->stop();
		_aniArm->stop();
		_aniLhand->stop();
	}

	if (KEYMANAGER->down(VK_LEFT))
	{
		_position.x -= TIMEMANAGER->getElapsedTime() * 200;
		_dir = LEFT;
		if (_movement[0] != M_JUMP && _movement[1] != M_JUMP)
			setMovement(M_WALK);
	}
	if (KEYMANAGER->down(VK_RIGHT))
	{
		_position.x += TIMEMANAGER->getElapsedTime() * 200; 
		_dir = RIGHT;
		if (_movement[0] != M_JUMP && _movement[1] != M_JUMP)
			setMovement(M_WALK);
	}

	if (KEYMANAGER->press('c'))
	{
		setMovement(M_JUMP);
	}

	if (KEYMANAGER->press(VK_LEFT) || KEYMANAGER->press(VK_RIGHT))
	{
		_aniBody->stop();
		_aniArm->stop();
		_aniLhand->stop();
		setAnimation(_state.movement);
	
		_aniBody->start();
		_aniArm->start();
		_aniLhand->start();
	}

	if (!KEYMANAGER->down(VK_LEFT) && !KEYMANAGER->down(VK_RIGHT) &&
		!KEYMANAGER->down(VK_UP)   && !KEYMANAGER->down(VK_DOWN)  &&
		_state.movement != M_NONE)
	{
		_aniBody->stop();
		_aniArm->stop();
		_aniLhand->stop();
		setMovement(M_NONE);
		setAnimation(_state.movement);
		_aniBody->start();
		_aniArm->start();
		_aniLhand->start();
	}
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
	_aniArm->setFPS(1.0f / _Mmotions.find(movement)->second.delay);

	_aniBody->setPlayFrame(
		PointMake(0, _Mmotions.find(movement)->second.frameY),
		PointMake(_Mmotions.find(movement)->second.maxFrameX - 1, _Mmotions.find(movement)->second.frameY),
		false, true);
	_aniArm->setPlayFrame(
		PointMake(0, _Mmotions.find(movement)->second.frameY),
		PointMake(_Mmotions.find(movement)->second.maxFrameX - 1, _Mmotions.find(movement)->second.frameY),
		false, true);
	_aniLhand->setPlayFrame(
		PointMake(0, _Mmotions.find(movement)->second.frameY),
		PointMake(_Mmotions.find(movement)->second.maxFrameX - 1, _Mmotions.find(movement)->second.frameY),
		false, true);
}

void player::setPartPosition(void)
{
	if (_dir == LEFT)
	{
		_headPosition = fPOINT(_position.x + 33, _position.y + 1);
		_facePosition = fPOINT(_position.x + 24, _position.y - 1);
		_hairPosition = fPOINT(_position.x + 34, _position.y + 1);
	}
	
	if (_dir == RIGHT)
	{
		_headPosition = fPOINT(_position.x + 28, _position.y + 1);
		_facePosition = fPOINT(_position.x + 26, _position.y - 1);
		_hairPosition = fPOINT(_position.x + 31, _position.y + 1);
	}
}

void player::setMovement(MOVEMENT movement)
{
	if (movement == M_NONE)
		_movement[0] = _movement[1] = M_NONE;
	else if (movement == M_WALK)
	{
		_movement[0] = M_WALK;
		_movement[1] = M_NONE;
	}
	else 
		_movement[0] == M_NONE ? _movement[0] = movement : _movement[1] = movement;
}

