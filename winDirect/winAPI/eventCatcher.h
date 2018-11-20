#pragma once
#include "eventDef.h"

class eventBase;

// 각 event의 destParam(type, kind, act, call)에 반응하는 요소
// 해당 event가 실행되기 전, 후에 각자의 active를 실행

typedef function<void(eventBase*)> eventCatcherActive;

class eventCatcher
{
private :
	unsigned long _param;
	function<void(eventBase* bindEvent)> * _beforeActive;
	function<void(eventBase* bindEvent)> * _afterActive;

public :
	virtual HRESULT init(void) { return S_OK; };
	virtual void release(void) { SAFE_DELETE(_beforeActive); SAFE_DELETE(_afterActive); };

public :
	unsigned long & getParam(void) { return _param; }
	function<void(eventBase*)>* & getBeforeActive(void) { return _beforeActive; };
	function<void(eventBase*)>* & getAfterActive(void) { return _afterActive; };

public:
	eventCatcher() : _param(0), _beforeActive(0), _afterActive(0) {};
	virtual ~eventCatcher() {};
};

