#include "stdafx.h"
#include "fieldBase.h"

#include "baseObject.h"
#include "enemyBase.h"
#include "npcBase.h"
#include "itemBase.h"

HRESULT fieldBase::init(void)
{
	_vFieldImage.reserve(6);
	_pixel = NULL;

	return S_OK;
}

void fieldBase::release(void)
{
	_vFieldImage.clear();

	releasePixelImage();
	releaseTotal();
}

void fieldBase::update(void)
{
}

void fieldBase::render(void)
{
}

void fieldBase::releaseTotal(void)
{
	releaseItem();
	releaseEnemy();
	// releaseInteract();
	releaseNPC();
}

void fieldBase::setPixelImage(const char * fileName)
{
	releasePixelImage();
	_pixel = new tagPixel;

	// imgField 정의 필요
	HDC hdc = GetDC(_hWnd);
	_pixel->pDC = CreateCompatibleDC(hdc);
	_pixel->pBitmap = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, _vFieldImage[0].img->getSize().x, _vFieldImage[0].img->getSize().y, LR_LOADFROMFILE);
	_pixel->oBitmap = (HBITMAP)SelectObject(_pixel->pDC, _pixel->pBitmap);
}

template<typename OBJ>
inline void fieldBase::addObject(OBJ input, list<pair<list<baseObject*>::iterator*, OBJ>> & o_list)
{
	_fieldList.totalObject.push_front(input);
	o_list.push_front(make_pair(&_fieldList.totalObject.begin(), input));
}

template<typename OBJ>
inline void fieldBase::releaseList(list<pair<list<baseObject*>::iterator*, OBJ>>& o_list, bool isDelete)
{
	for (auto & iter = o_list.begin(); iter != o_list.end();)
	{
		auto totalIter = iter->first;
		OBJ  viewObject = iter->second;

		if (isDelete)
		{
			viewObject->release();
			SAFE_DELETE(viewObject);
		}

		_fieldList.totalObject.erase(*totalIter);
		iter = o_list.erase(iter);
	}
}

void fieldBase::releasePixelImage(void)
{
	if (!_pixel) return;

	SelectObject(_pixel->pDC, _pixel->oBitmap);
	DeleteObject(_pixel->pBitmap);
	DeleteDC(_pixel->pDC);

	delete _pixel;
	_pixel = NULL;
}