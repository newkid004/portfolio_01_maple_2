#pragma once

class baseObject;
class itemBase;
class enemyBase;
class interactBase;
class npcBase;

struct tagFieldList
{
	list<baseObject*> totalObject;
	list<pair<list<baseObject*>::iterator*, itemBase*>>			item;
	list<pair<list<baseObject*>::iterator*, enemyBase*>>		enemy;
	list<pair<list<baseObject*>::iterator*, interactBase*>>		interact;
	list<pair<list<baseObject*>::iterator*, npcBase*>>			npc;
};

class fieldBase
{
private :
	struct tagPixel
	{
		HBITMAP oBitmap;
		HBITMAP	pBitmap;
		HDC		pDC;
	};

private :
	tagFieldList _fieldList;
	
	image* _imgField;
	tagPixel* _pixel;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

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
	image *& getImage(void) { return _imgField; };

	// bmp파일 사용, field 이미지와 크기가 같아야 함
	void setPixelImage(const char* fileName);
	COLORREF getPixel(int x, int y) { return GetPixel(_pixel->pDC, x, y); };
	COLORREF getPixel(POINT pos) { return GetPixel(_pixel->pDC, pos.x, pos.y); };
	COLORREF getPixel(fPOINT pos) { return GetPixel(_pixel->pDC, (int)pos.x, (int)pos.y); };

private :
	template <typename OBJ> inline void addObject(OBJ arg, list<pair<list<baseObject*>::iterator*, OBJ>> & o_list);
	template <typename OBJ> inline void releaseList(list<pair<list<baseObject*>::iterator*, OBJ>> & o_list, bool isDelete);

	void releasePixelImage(void);

public:
	fieldBase() {};
	~fieldBase() {};
};
