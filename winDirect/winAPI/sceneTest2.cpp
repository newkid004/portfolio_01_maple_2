#include "stdafx.h"
#include "sceneTest2.h"

HRESULT sceneTest2::init()
{
	
	pos.x = 100;
	pos.y = 100;
	return S_OK;
}

void sceneTest2::release()
{
}

void sceneTest2::update()
{
	
	if (KEYMANAGER->down(VK_LEFT))
	{
		pos.x -= 10;
	}
	if (KEYMANAGER->down(VK_RIGHT))
	{
		pos.x += 10;
	}
	if (KEYMANAGER->down(VK_UP))
	{
		pos.y -= 10;
	}
	if (KEYMANAGER->down(VK_DOWN))
	{
		pos.y += 10;
	}
	/*ColorF color = IMAGEMANAGER->find("test")->getBitmapPixel(_ptMouse);
	cout << _ptMouse.x << "        " << _ptMouse.y << endl;
	cout << color.a << "," << color.r << "," << color.g << "," << color.b << endl;
	cout << "----------------------------------------------------------------------" << endl;
	if (colorCompare(&IMAGEMANAGER->find("henesys_pixel")->getBitmapPixel(POINT{0,0}), &ColorF{ 0,150,255,0 }))
	{
		SCENEMANAGER->changeScene("charaterSelect");
	}*/
}

void sceneTest2::render()
{
	IMAGEMANAGER->statePos(0, 0);
	IMAGEMANAGER->find("henesys_background_1")->render();
	IMAGEMANAGER->statePos(0, 130);
	IMAGEMANAGER->find("henesys_background_2")->render();
	IMAGEMANAGER->statePos(0, 270);
	IMAGEMANAGER->find("henesys_background_3")->render();
	IMAGEMANAGER->statePos(0, 320);
	IMAGEMANAGER->find("henesys_background_4")->render();
	IMAGEMANAGER->statePos(0, 370);
	IMAGEMANAGER->find("henesys_background_5")->render();
	IMAGEMANAGER->statePos(0, 400);
	IMAGEMANAGER->find("henesys_background_6")->render();
	IMAGEMANAGER->statePos(-pos.x, -pos.y);
	if (KEYMANAGER->toggle(VK_F1))
	{
		IMAGEMANAGER->find("henesys_pixel")->render();
	}
	else
	{
		IMAGEMANAGER->find("henesys")->render();
	}

	IMAGEMANAGER->statePos(pos);
	IMAGEMANAGER->find("start")->render();
}
