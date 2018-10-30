#pragma once
#include "gameNode.h"

//로드 아이템 종류
enum e_LOAD_KIND
{
	LOAD_KIND_IMAGE,
	LOAD_KIND_SOUND,

	LOAD_KIND_END
};

//각 포인터는 NULL로 초기화
struct tagLoadResource
{
	char*		keyName;	// 키 값

	int*		vInt;		// 정수 값
	float*		vFloat;		// 실수 값
	bool*		vBool;		// 조건 값
	string*		vString;	// 문자열 값
	wstring*	vWString;	// wide문자열 값

	tagLoadResource()
	{
		keyName = 0;

		vInt		= 0;
		vFloat		= 0;
		vBool		= 0;
		vString		= 0;
		vWString	= 0;
	}
	~tagLoadResource()
	{
		SAFE_DELETE_ARRAY(keyName);

		SAFE_DELETE_ARRAY(vInt);
		SAFE_DELETE_ARRAY(vFloat);
		SAFE_DELETE_ARRAY(vBool);
		SAFE_DELETE_ARRAY(vString);
		SAFE_DELETE_ARRAY(vWString);
	}
};

class loadItem
{
private:
	e_LOAD_KIND _kind;
	tagLoadResource _resource;

public:
	// ---------------- init ---------------- //
	HRESULT putImage(char* keyName, wchar_t* fileName, int maxFrameX = 1, int maxFrameY = 1, bool isUsePixel = false);
	HRESULT putSound(char* keyName, char* fileName, bool bgm, bool loop);

	// ---------------- 접근자 ---------------- //
	e_LOAD_KIND getLoadingKind(void) { return _kind; }
	tagLoadResource & getResource(void) { return _resource; };

	loadItem() {}
	~loadItem() {}
};

class loading
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	int _currentGauge;
	int _frameCount;
	int _soundCount;

public:
	HRESULT init(void);
	void release(void);

	void loadImage(char* keyName, wchar_t* fileName, int maxFrameX = 1, int maxFrameY = 1, bool isUsePixel = false);
	void loadSound(char* keyName, char* fileName, bool bgm, bool loop);

public :
	//로딩 완료? (로딩완료후 화면전환)
	BOOL loadingDone(void);

	//로드아이템 벡터 가져오기
	arrLoadItem& getLoadItem(void) { return _vLoadItem; }

	// 현재 로드중인 아이템 종류
	loadItem* getItem(void) { if (_vLoadItem.size() <= _currentGauge) return NULL; return _vLoadItem[_currentGauge]; }
	loadItem* getNextItem(void);

public:
	float getProgress(void) { return (float)_currentGauge / (float)_vLoadItem.size(); };
	int& getGaugeValue(void) { return _currentGauge; };
	int& getSoundCount(void) { return _soundCount; };

private :
	HRESULT inputImage(tagLoadResource & item);
	HRESULT inputSound(tagLoadResource & item);

public :
	loading() {}
	~loading() {}
};