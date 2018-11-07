#pragma once
#include "eventDef.h"

#define eventBaseCreate2Writter (void* sour, void* dest, unsigned long paramType = 0UL, float timeAlive = 0.f) : eventBase(sour, dest, paramType, timeAlive) {}
#define makeSourParam(param) ((param & 0xffffUL) << 16)
#define makeDestParam(param) (param & 0xffffUL)
#define makeParamType(sour, dest) (makeSourParam(sour) | makeDestParam(dest))
#define sourParam(param) ((param & 0xffff0000UL) >> 16)
#define destParam(param) (param & 0xffffUL)
#define makeEventParam(type, kind, act, call) ((type & 0x000f) | (kind & 0x00f0) | (act & 0x0f00) | (call & 0xf000))

class eventBase
{
protected:
	void*			_sour;
	void*			_dest;
	
	unsigned long	_paramType;

	float _timeAlive;

public:
	virtual void update() { _timeAlive -= TIMEMANAGER->getElapsedTime(); };
	virtual void render() {}

public: // getter, setter
	float getTimeAlive() { return _timeAlive; }

protected :
	eventBase() {};

public :
	eventBase(void* sour, void* dest, unsigned long paramType = 0UL, float timeAlive = 0.f) 
	{
		_sour = sour;
		_dest = dest;
		_paramType = paramType;
		_timeAlive = timeAlive;
	}
	virtual ~eventBase() {}
};
