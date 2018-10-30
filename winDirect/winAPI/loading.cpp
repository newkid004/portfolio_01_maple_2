#include "stdafx.h"
#include "loading.h"

HRESULT loadItem::putImage(char* keyName, wchar_t * fileName, int maxFrameX, int maxFrameY, bool isUsePixel)
{
	_kind = LOAD_KIND_IMAGE;

	_resource.keyName = new char[strlen(keyName) + 1];		strcpy(_resource.keyName, keyName);
	_resource.vWString = new wstring[1];				_resource.vWString[0] = fileName;
	_resource.vInt = new int[2];						_resource.vInt[0] = maxFrameX; _resource.vInt[1] = maxFrameY;
	_resource.vBool = new bool[1];						_resource.vBool[0] = isUsePixel;

	return S_OK;
}

HRESULT loadItem::putSound(char* keyName, char * fileName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_resource.keyName = new char[strlen(keyName) + 1];		strcpy(_resource.keyName, keyName);
	_resource.vString = new string[1];					_resource.vString[0] = fileName;
	_resource.vBool = new bool[2];						_resource.vBool[0] = bgm; _resource.vBool[1] = loop;

	return S_OK;
}

HRESULT loading::init(void)
{	
	_currentGauge = 0;
	_frameCount = 0;
	_soundCount = 0;

	return S_OK;
}

void loading::release(void)
{
	for (int i = 0; i < _vLoadItem.size(); i++)
		SAFE_DELETE(_vLoadItem[i]);

	_vLoadItem.clear();
}

void loading::loadImage(char * keyName, wchar_t * fileName, int maxFrameX, int maxFrameY, bool isUsePixel)
{
	loadItem* item = new loadItem; 
	item->putImage(keyName, fileName, maxFrameX, maxFrameY, isUsePixel);
	_vLoadItem.push_back(item);
}

void loading::loadSound(char * keyName, char * fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->putSound(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);

	++_soundCount;
}

BOOL loading::loadingDone(void)
{
	//로딩이 완료 됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE	: inputImage(item->getResource()); break;
	case LOAD_KIND_SOUND	: inputSound(item->getResource()); break;
	}

	_currentGauge++;

	return FALSE;
}

loadItem * loading::getNextItem(void)
{
	if (_vLoadItem.size() <= _currentGauge + 1)
		return NULL;

	return _vLoadItem[_currentGauge + 1];
}

// ----- private ----- //
HRESULT loading::inputImage(tagLoadResource & item)
{
	IMAGEMANAGER->add(
		item.keyName,
		item.vWString[0].c_str(),
		item.vInt[0],
		item.vInt[1]);

	return S_OK;
}

HRESULT loading::inputSound(tagLoadResource & item)
{
	SOUNDMANAGER->addSound(
		item.keyName,
		item.vString[0].c_str(),
		item.vBool[0],
		item.vBool[1]);

	return S_OK;
}

