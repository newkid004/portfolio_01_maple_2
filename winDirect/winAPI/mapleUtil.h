#pragma once

class enemyBase;
class player;

struct fPOINT;

struct mapleUtil
{
	static NUM_REAL dmgP2M(player* sour, enemyBase* dest, float skillPer = 1.0f);
	static NUM_REAL dmgM2P(enemyBase* sour, player* dest, float sourRatio = 1.0f);
	static fPOINT statDamage(player* info);
};

