#pragma once
#include "enemyBase.h"

class enemy_0000_snail : public enemyBase
{
public :
	HRESULT init(void) { init(ENEMY_KIND_0000_SNAIL_GREEN); };
	HRESULT init(e_ENEMY_KIND kind);

public:
	enemy_0000_snail() {};
	~enemy_0000_snail() {};
};

