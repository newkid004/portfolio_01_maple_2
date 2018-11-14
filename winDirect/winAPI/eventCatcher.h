#pragma once
#include "eventDef.h"

class eventBase;

// �� event�� destParam(type, kind, act, call)�� �����ϴ� ���
// �ش� event�� ����Ǳ� ��, �Ŀ� ������ active�� ����

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

