#include "stdafx.h"
#include "imgNumManager.h"

HRESULT imgNumManager::init(void)
{
	_curImageNumber = NULL;

	return S_OK;
}

void imgNumManager::release(void)
{
	for (auto iter = _mImageNumber.begin(); iter != _mImageNumber.end();)
	{
		iter->second->interval.clear();
		SAFE_DELETE(iter->second);

		iter = _mImageNumber.erase(iter);
	}
}

void imgNumManager::add(string name, image * bindImage, fPOINT offset, float spaceRatio)
{
	auto f = find(name);
	if (f != NULL) return;

	f = new tagImageNumber;
	f->bindImage = bindImage;
	f->offset = offset;
	f->spaceRatio = spaceRatio;

	_mImageNumber.insert(make_pair(name, f));
}

void imgNumManager::draw(const char * str, fPOINT pos, fRECT * outSize)
{
	if (!_curImageNumber) return;

	IMAGEMANAGER->getTransformState(TF_POSITION);
	if (outSize) outSize->LT = pos;

	int curChar;
	for (int i = 0; i < strlen(str); ++i)
	{
		curChar = str[i];
		if ('a' <= curChar && curChar <= 'z') curChar -= 'a' - 'A';
		if ('A' <= curChar && curChar <= 'Z') curChar -= 'A' - '0' - 10;
		curChar -= '0';

		IMAGEMANAGER->statePos(pos);
		_curImageNumber->bindImage->frameRender(_curImageNumber->offset + fPOINT{ (float)curChar, 0.f });

		pos.x += (_curImageNumber->interval[curChar] == 0 ?
			_curImageNumber->bindImage->getFrameSize().x :
			_curImageNumber->interval[curChar]) + 
				_curImageNumber->bindImage->getFrameSize().x * _curImageNumber->spaceRatio;
	}

	if (outSize) { outSize->RB = pos; outSize->RB.y += _curImageNumber->bindImage->getFrameSize().y; }
}

fPOINT imgNumManager::getSize(const char * str)
{
	fPOINT resultSize;
	resultSize.y = _curImageNumber->bindImage->getFrameSize().y;

	int curChar;
	for (int i = 0; i < strlen(str); ++i)
	{
		curChar = str[i];
		if ('a' <= curChar && curChar <= 'z') curChar -= 'a' - 'A';
		if ('A' <= curChar && curChar <= 'Z') curChar -= 'A' - '0' - 10;
		curChar -= '0';

		resultSize.x += (_curImageNumber->interval[curChar] == 0 ?
			_curImageNumber->bindImage->getFrameSize().x :
			_curImageNumber->interval[curChar]) + 
				_curImageNumber->bindImage->getFrameSize().x * _curImageNumber->spaceRatio;
	}
	resultSize.x -= _curImageNumber->bindImage->getFrameSize().x * _curImageNumber->spaceRatio;

	return resultSize;
}

// ----- private ----- //
imgNumManager::tagImageNumber * imgNumManager::find(string name)
{
	auto iter = _mImageNumber.find(name);
	if (iter == _mImageNumber.end()) return NULL;

	return iter->second;
}
