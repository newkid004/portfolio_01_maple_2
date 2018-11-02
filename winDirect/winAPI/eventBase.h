#pragma once
#include "eventDef.h"

#define eventBaseCreate2Writter (void* sour, void* dest, unsigned long paramType = 0UL, float timeAlive = 0.f) : eventBase(sour, dest, paramType, timeAlive) {}
#define makeParamType(sour, dest) ((sour << 16) | dest)
#define sourParam(sour) ((sour >> 16) & 0xffff)
#define destParam(dest) (dest & 0xffff)

class eventBase
{
protected:
	void*			_sour;
	void*			_dest;
	
	unsigned long	_paramType;

	float _timeAlive;

public:
	virtual void update() {}
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
