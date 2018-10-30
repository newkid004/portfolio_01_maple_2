#include "stdafx.h"
#include "enemyManager.h"

#include "enemyBase.h"

void enemyManager::release(void)
{
	auto i = _mEnemy.begin();
	for (; i != _mEnemy.end(); )
	{
		i->second->release();
		SAFE_DELETE(i->second);

		i = _mEnemy.erase(i);
	}
}

enemyBase * enemyManager::createEnemy(e_ENEMY_KIND kind)
{
	return nullptr;
}


bossBase * enemyManager::createBoss(e_BOSS_KIND kind)
{
	return nullptr;
}

template<typename T>
T * enemyManager::find(int kind, map<int, T*> _map)
{
	map<int, T*>::iterator i = _map.find(kind);
	if (i == _map.end()) return NULL;

	return i->second;

}

template<typename T>
T * enemyManager::add(int kind, T * addition, map<int, T*> _map)
{
	T* m = find(kind, _map);
	if (m) return m;

	_map.insert(make_pair(kind, addition));

	return m;
}
