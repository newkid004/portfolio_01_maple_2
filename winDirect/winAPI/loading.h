#pragma once
#include "gameNode.h"

//�ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//���Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,			//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,			//�Ϲ� �̹���(��ġ��ǥ)
	LOAD_KIND_FRAMEIMAGE_0,		//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,		//������ �̹���(��ġ��ǥ)
	LOAD_KIND_GDIP_IMAGE,		// GDI+ �̹���
	LOAD_KIND_GDIP_FRAMEIMAGE,	// GDI+ ������ �̹���
	LOAD_KIND_SOUND,			//����
	
	LOAD_KIND_TILEMAP,			// Ÿ�ϸ�
	LOAD_KIND_EFFECT,			// ����Ʈ

	LOAD_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;				//�̹��� Ű��
	TCHAR* fileName;		//���� �̸�
	int x, y;					//��ġ ��ǥ
	int width, height;			//����, ����ũ��
	int frameX, frameY;			//������ x, y
	bool trans;					//��� ���ٰ���?
	COLORREF transColor;		//�������� ����
};

//���� ���ҽ� ����ü
struct tagSoundResource
{
	string keyName;
	string soundName;
	bool bgm;
	bool loop;
};

// Ÿ�ϸ� ���ҽ� ����ü
struct tagTileMapResource
{
	string keyName;
};

// ����Ʈ ���ҽ� ����ü
struct tagEffectResource
{
	string	keyName;
	string	imgName;
	POINT	start;
	POINT	end;

	BYTE	alpha;
	float	alphaAdd;

	float	timeLive;
	float	timeAniStart;
	float	timeAfterAlpha;

	int		FPS;
	bool	isLoop;

	POINT	offset;
	fPOINT	speed;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;
	tagTileMapResource _tileMapResource;
	tagEffectResource _effectResource;

public:
	// ---------------- init ---------------- //
	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT initForImage(string keyName, int width, int height);

	//�̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForImage(string keyName, char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForFrameImage(string keyName, char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// GDI+ �̹����� �ʱ�ȭ
	HRESULT initForGDI(string keyName, TCHAR* fileName, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForGDIFrame(string keyName, TCHAR* fileName, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//���� ���Ϸ� �ʱ�ȭ
	HRESULT initForSound(string keyName, string soundName, bool bgm, bool loop);

	// Ÿ�ϸ� ���Ϸ� �ʱ�ȭ
	HRESULT initForTileMap(string keyName);

	// ����Ʈ�� �ʱ�ȭ
	HRESULT initForEffect(string keyName, string imgName, POINT & start, POINT & end, POINT & offset, int & FPS, bool & isLoop, fPOINT & speed, float & timeLive, float & timeAniStart, BYTE & alpha, float & alphaAdd, float & timeAfterAlpha);

	// ---------------- ������ ---------------- //
	//�ε������� ���� ��������
	LOAD_KIND getLoadingKind(void) { return _kind; }

	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource(void) { return _imageResource; }

	//���� ���ҽ� ��������
	tagSoundResource getSoundResource(void) { return _soundResource; }

	// Ÿ�ϸ� ���ҽ� ��������
	tagTileMapResource getTileMapResource(void) { return _tileMapResource; };

	// ����Ʈ ���ҽ� ��������
	tagEffectResource getEffectResource(void) { return _effectResource; };

	loadItem() {}
	~loadItem() {}
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//�ε�ȭ�鿡 ����� �̹��� �� �ε���
	image* _background;
	image* _loadingBarRun;

	int _currentGauge;
	int _frameCount;
	int _soundCount;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� ��Ʈ�� �ʱ�ȭ
	void loadImage(string keyName, int width, int height);

	//�̹��� ���Ϸ� �ʱ�ȭ
	void loadImage(string keyName, char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadFrameImage(string keyName, char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string keyName, char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// GDI+ �̹��� ���� �ʱ�ȭ
	void loadImageGDI(string keyName, TCHAR* fileName, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImageFrameGDI(string keyName, TCHAR* fileName, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//���� ���Ϸ� �ʱ�ȭ
	void loadSound(string keyName, string soundName, bool bgm, bool loop);

	// Ÿ�ϸ� ���Ϸ� �ʱ�ȭ
	void loadTileMap(string keyName);

	// ����Ʈ �ʱ�ȭ
	void loadEffect(string keyName, string imgName, POINT & start, POINT & end, POINT offset = { 0 }, int FPS = 12, bool isLoop = false, fPOINT speed = { 0, 0 }, float timeLive = 0, float timeAniStart = 0, BYTE alpha = 255, float alphaAdd = 0, float timeAfterAlpha = 0);

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

	loading() {}
	~loading() {}
};