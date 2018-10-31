#pragma once

class baseObject;
class itemBase;
class enemyBase;
class interactBase;
class npcBase;

class fieldBase
{
private :
	struct tagFieldList
	{
		list<baseObject*> totalObject;
		list<pair<list<baseObject*>::iterator*, itemBase*>>			item;
		list<pair<list<baseObject*>::iterator*, enemyBase*>>		enemy;
		list<pair<list<baseObject*>::iterator*, interactBase*>>		interact;
		list<pair<list<baseObject*>::iterator*, npcBase*>>			npc;
	};

	struct tagPixel
	{
		HBITMAP oBitmap;
		HBITMAP	pBitmap;
		HDC		pDC;
	};

	struct tagFieldImage
	{
		image* img;
		e_RENDER_ORDER ro;

		float offsetRatio;
	};

private :
	tagFieldList _fieldList;

	vector<tagFieldImage> _vFieldImage;
	tagPixel* _pixel;

public :
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

public :
	void releaseTotal(void);
	void releaseItem(void)		{ releaseList(_fieldList.item, true); };
	void releaseEnemy(void)		{ releaseList(_fieldList.enemy, true); };
	// void releaseInteract(void)	{ releaseList(_fieldList.interact, false); };
	void releaseNPC(void)		{ releaseList(_fieldList.npc, false); };

public :
	tagFieldList & getFieldList(void) { return _fieldList; };

	void addItem(itemBase* addition)			{ addObject(addition, _fieldList.item); };
	void addEnemy(enemyBase* addition)			{ addObject(addition, _fieldList.enemy); };
	// void addInteract(interactBase* addition)	{ addObject(addition, _fieldList.interact); };
	void addNPC(npcBase* addition)				{ addObject(addition, _fieldList.npc); };

public :	// ----- image, pixel ----- //
	image* getImage(int index) { return _vFieldImage[index].img; }
	void pushImage(image* img, e_RENDER_ORDER ro, float offsetRatio) { _vFieldImage.push_back(tagFieldImage{ img, ro, offsetRatio }); }

	// bmp파일 사용, field 이미지와 크기가 같아야 함
	void setPixelImage(const char* fileName);
	COLORREF getPixel(int x, int y) { return GetPixel(_pixel->pDC, x, y); };
	COLORREF getPixel(POINT pos) { return GetPixel(_pixel->pDC, pos.x, pos.y); };
	COLORREF getPixel(fPOINT pos) { return GetPixel(_pixel->pDC, (int)pos.x, (int)pos.y); };

public :
	fPOINT getSize(void) { return _vFieldImage[0].img->getSize(); };

private :
	template <typename OBJ> inline void addObject(OBJ arg, list<pair<list<baseObject*>::iterator*, OBJ>> & o_list);
	template <typename OBJ> inline void releaseList(list<pair<list<baseObject*>::iterator*, OBJ>> & o_list, bool isDelete);

	void releasePixelImage(void);

public:
	fieldBase() {};
	~fieldBase() {};
};
