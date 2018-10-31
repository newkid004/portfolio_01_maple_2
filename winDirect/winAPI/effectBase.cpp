#include "stdafx.h"
#include "effectBase.h"

HRESULT effectBase::init(void)
{
	ZeroMemory(&_infoEffect, sizeof(effectInfo));
	return S_OK;
}

void effectBase::update(void)
{
	_infoEffect.ani->update();
}

void effectBase::render(void)
{
	function<void(void)>* fBefore = new function<void(void)>;
	*fBefore = [&](void)->void
	{
		IMAGEMANAGER->getTransformState() = TF_ALL;
		IMAGEMANAGER->stateRotate(_infoEffect.rotation);
		IMAGEMANAGER->stateFlip(_infoEffect.flip);
	};

	RENDERMANAGER->add(
		_infoEffect.renderOrder,
		_infoEffect.image,
		_infoEffect.position + _infoEffect.offset,
		_infoEffect.ani->getFramePos(),
		_infoEffect.ani->getFrameSize(),
		_infoEffect.alpha,
		NULL,
		NULL);
}
