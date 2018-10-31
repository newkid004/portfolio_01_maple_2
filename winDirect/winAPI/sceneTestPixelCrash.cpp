#include "stdafx.h"
#include "sceneTestPixelCrash.h"

#include "fieldBase.h"

fPOINT offset = fPOINT(0);
COLORREF color;

HRESULT sceneTestPixelCrash::init(void)
{
	// ----- image ----- //
	IMAGEMANAGER->add("map", L"image/map/henesys.png");

	// ----- field ----- //
	_field = new fieldBase;
	_field->init();
	_field->pushImage(IMAGEMANAGER->find("map"), RO_BACK_0, 1.0f);
	_field->setPixelImage("image/map/henesys_pixel.bmp");

	// ----- text ----- //
	TEXTMANAGER->add("text", L"¹ÙÅÁ", 16.f);

	IMAGEMANAGER->resetTransform();
	getBackColor() = C_COLOR_WHITE;

	return S_OK;
}

void sceneTestPixelCrash::release(void)
{
	_field->release();
	SAFE_DELETE(_field);
}

void sceneTestPixelCrash::update(void)
{
	color = _field->getPixel(fPOINT(_ptMouse.x - offset.x, _ptMouse.y - offset.y));

	if (color == RGB(0, 150, 255))
		offset.x -= TIMEMANAGER->getElapsedTime() * 100;

	IMAGEMANAGER->statePos(offset);
}

void sceneTestPixelCrash::render(void)
{
	_field->getImage(0)->render();

	D2D1_POINT_2F r = { 0.f, 0.f };
	IMAGEMANAGER->resetTransform();
	IMAGEMANAGER->setTransform(&r);

	wstring str1 = to_wstring(_ptMouse.x) + L"\t" + to_wstring(_ptMouse.y);
	wstring str2 = to_wstring(color & 0xff) + L"\t" + to_wstring((color & (0xff << 8)) >> 8) + L"\t" + to_wstring((color & (0xff << 16)) >> 16);

	TEXTMANAGER->drawText(str1.c_str(), str1.length(), D2D1_RECT_F{ 0, 0, 120, 120 }, TEXTMANAGER->find("text"));
	TEXTMANAGER->drawText(str2.c_str(), str2.length(), D2D1_RECT_F{ 0, 40, 200, 120 }, TEXTMANAGER->find("text"));
}
