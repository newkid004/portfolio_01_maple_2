#pragma once
#include "eventDef.h"

class eventBase;

// 각 event의 param(type, kind, act, call)에 반응하는 요소
// 해당 event가 실행되기 전, 후에 각자의 active를 실행
class eventCatcher
{
private :
	int _param;
	function<void(eventBase* bindEvent)> * _beforeActive;
	function<void(eventBase* bindEvent)> * _afterActive;

public :
	virtual HRESULT init(void) {};
	virtual void release(void) { SAFE_DELETE(_beforeActive); SAFE_DELETE(_afterActive); };

public :
	int & getIndex(void) { return _param; }
	function<void(eventBase*)>* & getBeforeActive(void) { return _beforeActive; };
	function<void(eventBase*)>* & getAfterActive(void) { return _afterActive; };

public:
	eventCatcher() : _param(0), _beforeActive(0), _afterActive(0) {};
	virtual ~eventCatcher() {};
};

