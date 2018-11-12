#pragma once
#include "eventDef.h"

class eventBase;

// �� event�� param(type, kind, act, call)�� �����ϴ� ���
// �ش� event�� ����Ǳ� ��, �Ŀ� ������ active�� ����
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

