#pragma once
#include "gameNode.h"

//�ε� ������ ����
enum e_LOAD_KIND
{
	LOAD_KIND_IMAGE,
	LOAD_KIND_SOUND,

	LOAD_KIND_END
};

//�� �����ʹ� NULL�� �ʱ�ȭ
struct tagLoadResource
{
	char*		keyName;	// Ű ��

	int*		vInt;		// ���� ��
	float*		vFloat;		// �Ǽ� ��
	bool*		vBool;		// ���� ��
	string*		vString;	// ���ڿ� ��
	wstring*	vWString;	// wide���ڿ� ��

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

	// ---------------- ������ ---------------- //
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
	//�ε� �Ϸ�? (�ε��Ϸ��� ȭ����ȯ)
	BOOL loadingDone(void);

	//�ε������ ���� ��������
	arrLoadItem& getLoadItem(void) { return _vLoadItem; }

	// ���� �ε����� ������ ����
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