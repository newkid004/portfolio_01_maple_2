#include "stdafx.h"
#include "renderManager.h"
#include "windowBase.h"

HRESULT renderManager::init(void)
{
	return S_OK;
}

void renderManager::release(void)
{
	for (int i = 0; i < RO_COUNT; ++i)
		releaseList(i);
}

void renderManager::update(void)
{
}

void renderManager::render(void)
{
	int renderStateTemp = IMAGEMANAGER->getRenderState(IRS_ALWAYS_RESET_TRANSFORM);
	IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, false);

	for (int i = 0; i < RO_COUNT; ++i)
	{
		renderList(i);
		releaseList(i);
	}

	if (renderStateTemp)
		IMAGEMANAGER->setRenderState(IRS_ALWAYS_RESET_TRANSFORM, true);
}

void renderManager::add(e_RENDER_ORDER order, image * img, fPOINT pos, fPOINT clip, fPOINT size, float alpha, function<void(void)>* callBefore, function<void(void)>* callAfter)
{
	if (img == NULL) return;

	tagRender addable = tagRender(img, pos, clip, size, alpha, callBefore, callAfter);

	if (_renderState & RMS_CLIP_INTO_CAMERA)
	{
		if (clipRender(addable)) _vRenderList[order].push_back(addable);
		return;
	}

	// default
	_vRenderList[order].push_back(addable);
}

void renderManager::setRenderState(e_RENDER_MANAGER_STATE s, int value)
{
	switch (s)
	{
	case RMS_CLIP_INTO_CAMERA: {	// ī�޶� Ŭ������ �ϴ���
		_renderState = value ? bit_put(_renderState, s) : bit_pick(_renderState, s);
	} break;

	}
}

// ----- private ----- //
void renderManager::renderList(int order)
{
	for (tagRender & stRender : _vRenderList[order])
	{
		IMAGEMANAGER->statePos(stRender.pos);

		if (stRender.callBefore)
		{
			(*stRender.callBefore)();
			delete stRender.callBefore;
		}

		stRender.img->render(
			stRender.clip.x,
			stRender.clip.y,
			stRender.size.x,
			stRender.size.y,
			stRender.alpha);

		if (stRender.callAfter)
		{
			(*stRender.callAfter)();
			delete stRender.callAfter;
		}
	}
}

void renderManager::releaseList(int order)
{
	_vRenderList[order].clear();
}

bool renderManager::clipRender(tagRender & r)
{
	static fPOINT & cOffset	= _currentCamera->getOffset();
	static fPOINT & cSize	= _currentCamera->getSize();

	NUM_REAL LTX = cOffset.x - r.pos.x; if (0 < LTX) { r.clip.x += LTX; r.size.x -= LTX; }
	NUM_REAL LTY = cOffset.y - r.pos.y; if (0 < LTY) { r.clip.y += LTY; r.size.y -= LTY; }
	NUM_REAL RBX = r.pos.x + r.size.x - cOffset.x - cSize.x; if (0 < RBX) { r.size.x -= RBX; }
	NUM_REAL RBY = r.pos.y + r.size.y - cOffset.y - cSize.y; if (0 < RBY) { r.size.y -= RBY; }

	if (r.size.x < 0 || r.size.y < 0)
		return false;

	return true;
}