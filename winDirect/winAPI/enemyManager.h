#pragma once
#include "singletonBase.h"
#include "enemyDef.h"

class enemyBase;
class bossBase;

class enemyManager : public singletonBase<enemyManager>
{
private :
	map<int, enemyBase*> _mEnemy;
	map<int, bossBase*> _mBoss;

public :
	HRESULT init(void) { return S_OK; };
	void release(void);

public :
	enemyBase * addEnemy(e_ENEMY_KIND kind, enemyBase* addition) { return this->add(kind, addition, _mEnemy); };
	bossBase * addBoss(e_BOSS_KIND kind, bossBase* addition) { return this->add(kind, addition, _mBoss); };

	enemyBase * createEnemy(e_ENEMY_KIND kind);
	bossBase * createBoss(e_BOSS_KIND kind);

private :
	template<typename T> T * find(int kind, map<int, T*> _map);
	template<typename T> T * add(int kind, T* addition, map<int, T*> _map);

public:
	enemyManager() {};
	~enemyManager() {};
};
