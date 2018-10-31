#include "stdafx.h"
#include "bulletBase.h"

HRESULT bulletBase::init(void)
{
	_objectKind = objDef::OBJECT_BULLET;

	_ani = NULL; 
	ZeroMemory(&_info, sizeof(_info));

	return S_OK;
}

void bulletBase::update(void)
{
	getDeltaPos(
		_position,
		getRadian(_position, _info.posDest), 
		_info.velocity * TIMEMANAGER->getElapsedTime());
}

void bulletBase::render(void)
{
	function<void(void)>* fBefore = new function<void(void)>;
	*fBefore = [&](void)->void 
	{ 
		IMAGEMANAGER->getTransformState() = bit_pick(TF_ALL, TF_ROTATION | TF_SCALE);
		IMAGEMANAGER->stateFlip(_info.flip); 
	};

	RENDERMANAGER->add(
		RO_SKILL_FRONT,
		_img,
		_position - _ani->getFrameSize() / 2, 
		_ani->getFramePos(), 
		_ani->getFrameSize(), 
		1.0f,
		fBefore,
		NULL);
}
