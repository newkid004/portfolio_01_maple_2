#pragma once
#include "singletonBase.h"
#include "eventDef.h"

class eventBase;
class eventCatcher;

typedef vector<eventCatcher*>				V_EVENT_CALL;
typedef unordered_map<int, V_EVENT_CALL>	M_EVENT_ACT;
typedef unordered_map<int, M_EVENT_ACT>		M_EVENT_KIND;
typedef unordered_map<int, M_EVENT_KIND>	M_EVENT_TYPE;
typedef unordered_map<int, M_EVENT_TYPE>	M_EVENT_CATCHER;

class eventManager : public singletonBase<eventManager>
{
private:
	M_EVENT_CATCHER		_mEventCatcher;
	list<eventBase*>	_lEvent;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void initCatcher(void);
	
	void releaseCatcher(void);
	
public :
	void add(eventBase* ev);
	void deleteAll(void);

public :	// ----- catcher ----- //
	M_EVENT_TYPE & getEventCatcherType(int type)						{ return _mEventCatcher[type & 0xf]; };
	M_EVENT_KIND & getEventCatcherKind(M_EVENT_TYPE & mType, int kind)	{ return mType[(kind & 0x00f0) >> 4]; };
	M_EVENT_ACT & getEventCatcherKind(M_EVENT_KIND & mKind, int act)	{ return mKind[(act & 0x0f00) >> 8]; }
	V_EVENT_CALL & getEventCatcherCall(M_EVENT_ACT & mAct, int call)	{ return mAct[(call & 0xf000) >> 12]; };
	V_EVENT_CALL & getEventCatcherArray(int param);
	eventCatcher* & getEventCatcher(V_EVENT_CALL & vCall, int index)	{ return vCall[index]; };
	eventCatcher* & getEventCatcher(int param, int index)				{ return getEventCatcherArray(param)[index]; };

public:
	eventManager() {};
	~eventManager() {};
};
