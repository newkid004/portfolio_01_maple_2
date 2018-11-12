#pragma once
#include "singletonBase.h"

class windowBase;

typedef list<windowBase*> UI_LIST;
typedef UI_LIST::iterator UI_LIST_ITER;

class winManager : public singletonBase<winManager>
{
private :
	unordered_map<string, windowBase*>	_mWindow;
	UI_LIST								_lWindow;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	windowBase * add(string winName, windowBase* winAdd);
	windowBase* find(string winName);
	windowBase* getFocus(void) { if (_lWindow.empty()) return NULL; return *_lWindow.begin(); }

	void show(string winName);
	void show(windowBase* winBase);
	UI_LIST_ITER close(string winName);
	UI_LIST_ITER close(windowBase* winBase);
	UI_LIST_ITER trans(string winName);
	UI_LIST_ITER trans(windowBase* winBase);

	UI_LIST_ITER getIgnoreIter(void) { return _lWindow.end(); };

public:
	winManager() {};
	~winManager() {};
};