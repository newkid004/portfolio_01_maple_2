#include "stdafx.h"
#include "player.h"

#include "inventory.h"

player::player() : _headPosition(fPOINT(0.0f, 0.0f)),
				   _facePosition(fPOINT(0.0f, 0.0f)),
				   _hairPosition(fPOINT(0.0f, 0.0f)),
				   _tempPos(fPOINT(0.0f, 0.0f)),
				   _acc(0.0f)
{
}

HRESULT player::init(void)
{
	IMAGEMANAGER->add("henesys", L"image/map/henesys.png");
	IMAGEMANAGER->add("henesys_pixel", L"image/map/henesys_pixel.png");
	IMAGEMANAGER->add("p_body", L"image/character/player/body.png", 4, 3);
	IMAGEMANAGER->add("p_arm", L"image/character/player/arm.png", 4, 3);
	IMAGEMANAGER->add("p_head", L"image/character/player/head.png");
	IMAGEMANAGER->add("p_hair", L"image/character/player/hair.png");
	IMAGEMANAGER->add("p_face", L"image/character/player/face.png", 3, 25);
	IMAGEMANAGER->add("p_lHand", L"image/character/player/lHand.png", 4, 3);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	setMotions(M_NONE, 3, 0, 0.510f);
	setMotions(M_WALK, 4, 1, 0.180f);
	setMotions(M_JUMP, 1, 2, 0.1f);

	_aniBody = new animation;
	_aniArm = new animation;
	_aniLhand = new animation;

	_aniBody->init(IMAGEMANAGER->find("p_body"));
	_aniArm->init(IMAGEMANAGER->find("p_arm"));
	_aniLhand->init(IMAGEMANAGER->find("p_lHand"));

 	_position = fPOINT(WINSIZEX / 2, WINSIZEY / 2 - 100);
	_velocity = fPOINT(0.0f, 0.0f);
	_collision = fRECT(_position + 50, _position + 100);
	_state.movement = M_NONE;
	_movement[0] = _movement[1] = M_NONE;
	_dir = LEFT;
	setAnimation(_state.movement);
	initInventory();
	aniStart();
	_money = 0LL;

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
	if (_state.movement == M_JUMP)
	{
		jump();
		if (_position.y > _tempPos.y)
		{
			_position.y = _tempPos.y;
			_velocity = 0;
			_acc = 0.0f;
			setMovement(M_NONE);
			aniStart();
		}
	}
	_velocity *= TIMEMANAGER->getElapsedTime();
	_position += _velocity * TIMEMANAGER->getElapsedTime();
	_velocity = 0;
	_collision = fRECT(_position + 30, _position + 70);

	keyUpdate();
	setPartPosition();
	setRayStruct();
}

void player::render(void)
{
	IMAGEMANAGER->statePos(-500, -500);
	IMAGEMANAGER->find("henesys")->render();
	if (KEYMANAGER->toggle(VK_F1))
	{
		IMAGEMANAGER->find("henesys_pixel")->render();
	}
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

	IMAGEMANAGER->resetTransform();
	for (int i = 0; i < RAY_NUM; i++)
	{
		ID2D1SolidColorBrush*   g_pBlackBrush = NULL;
		_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);
		_renderTarget->DrawLine(
			D2D1::Point2F(_rayStruct.rightRay[i].sourfPos.x, _rayStruct.rightRay[i].sourfPos.y),
			D2D1::Point2F(_rayStruct.rightRay[i].destfPos.x, _rayStruct.rightRay[i].destfPos.y),
			g_pBlackBrush, 0.5f);
		_renderTarget->DrawLine(
			D2D1::Point2F(_rayStruct.leftRay[i].sourfPos.x, _rayStruct.leftRay[i].sourfPos.y),
			D2D1::Point2F(_rayStruct.leftRay[i].destfPos.x, _rayStruct.leftRay[i].destfPos.y),
			g_pBlackBrush, 0.5f);
		_renderTarget->DrawLine(
			D2D1::Point2F(_rayStruct.upperRay[i].sourfPos.x, _rayStruct.upperRay[i].sourfPos.y),
			D2D1::Point2F(_rayStruct.upperRay[i].destfPos.x, _rayStruct.upperRay[i].destfPos.y),
			g_pBlackBrush, 0.5f);
		_renderTarget->DrawLine(
			D2D1::Point2F(_rayStruct.bottomRay[i].sourfPos.x, _rayStruct.bottomRay[i].sourfPos.y),
			D2D1::Point2F(_rayStruct.bottomRay[i].destfPos.x, _rayStruct.bottomRay[i].destfPos.y),
			g_pBlackBrush, 0.5f);
		g_pBlackBrush->Release();
		g_pBlackBrush = NULL;
		if (_rayStruct.rightRay[i].distance > 0)
		{
			int n = 0;
		}
	}
}

void player::initInventory(void)
{
	for (auto & inven : _inven)
	{
		inven = new inventory;
		inven->init();
	}
}

void player::releaseInventory(void)
{
	for (auto & inven : _inven)
	{
		inven->release();
		SAFE_DELETE(inven);
	}
}

void player::keyUpdate(void)
{
	if (KEYMANAGER->press(VK_SPACE))
	{
		aniStart();
	}

	if (KEYMANAGER->press('s'))
	{
		aniStop();
	}

	if (KEYMANAGER->down(VK_LEFT))
	{
		_velocity.x = -SPEED;
		_dir = LEFT;
		if (_movement[0] != M_JUMP && _movement[1] != M_JUMP)
			setMovement(M_WALK);
	}
	if (KEYMANAGER->down(VK_RIGHT))
	{
		_velocity.x = SPEED;
		_dir = RIGHT;
		if (_movement[0] != M_JUMP && _movement[1] != M_JUMP)
			setMovement(M_WALK);
	}

	if (KEYMANAGER->press('c') || KEYMANAGER->press('C'))
	{
		if (_state.movement != M_JUMP)
		{
			_tempPos.y = _position.y;
			aniStop();
			setMovement(M_JUMP);
			aniStart();
		}
	}

	if (KEYMANAGER->press(VK_LEFT) || KEYMANAGER->press(VK_RIGHT))
	{
		aniStart();
	}

	if (!KEYMANAGER->down(VK_LEFT) && !KEYMANAGER->down(VK_RIGHT) &&
		!KEYMANAGER->down(VK_UP)   && !KEYMANAGER->down(VK_DOWN)  &&
		_state.movement != M_NONE && _state.movement != M_JUMP)
	{
		setMovement(M_NONE);
		aniStart();
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
	_aniLhand->setFPS(1.0f / _Mmotions.find(movement)->second.delay);

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

void player::aniStart(void)
{
	_aniBody->start();
	_aniArm->start();
	_aniLhand->start();
}

void player::aniStop(void)
{
	_aniBody->stop();
	_aniArm->stop();
	_aniLhand->stop();
}

void player::jump(void)
{ 
	_velocity.y = -SPEED * 4 + (GRAVITY + _acc);
	_acc += 20;
}
;
void player::setMovement(MOVEMENT movement)
{
	if (movement == M_NONE)
		_movement[0] = _movement[1] = M_NONE;
	else if (movement == M_WALK)
	{
		_movement[0] = M_WALK;
		_movement[1] = M_NONE;
	}
	else if (movement == M_JUMP)
	{
		_movement[0] = M_JUMP;
		_movement[1] = M_NONE;
	}
	else 
		_movement[0] == M_NONE ? _movement[0] = movement : _movement[1] = movement;

	_state.movement = (MOVEMENT)(_movement[0] | _movement[1]);
	setAnimation(_state.movement);
}

