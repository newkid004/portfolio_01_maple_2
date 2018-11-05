#pragma once
#include "singletonBase.h"

class itemBase;

class itemManager : public singletonBase<itemManager>
{
private :
	unordered_map<wstring, itemBase*> _mItem;

public :
	HRESULT init(void);
	void release(void);

public :
	void initItemList(void);

public :
	itemBase* add(itemBase* addition);
	itemBase* add(wstring name, itemBase* addition);
	itemBase* find(itemBase* item);
	itemBase* find(wstring name);

public:
	itemManager() {};
	~itemManager() {};
};

