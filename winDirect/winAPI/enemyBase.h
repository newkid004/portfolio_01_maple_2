#pragma once
#include "characterBase.h"
class enemyBase : public characterBase
{
protected:
	int			_enemyKind;
	NUM_REAL	_exp;

public :
	int & getKind(void) { return _enemyKind; };
	NUM_REAL & getEXP(void) { return _exp; };

public:
	enemyBase() : _enemyKind(0), _exp(0.f) {};
	~enemyBase() {};
};

