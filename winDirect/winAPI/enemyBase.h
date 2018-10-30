#pragma once
#include "characterBase.h"
class enemyBase : public characterBase
{
protected:
	int		_enemyKind;

public:
	enemyBase() : _enemyKind(0) {};
	~enemyBase() {};
};

