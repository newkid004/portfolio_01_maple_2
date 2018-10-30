#include "stdafx.h"
#include "enemyManager.h"

#include "enemyList.h"

void enemyManager::release(void)
{
	releaseMap(_mEnemy);
	releaseMap(_mBoss);
}

enemyBase * enemyManager::createEnemy(e_ENEMY_KIND kind)
{
	enemyBase * m = find(kind, _mEnemy);
	if (m == NULL) return NULL;

	switch (kind)
	{
	case ENEMY_KIND_0000_SNAIL_GREEN:	m = new enemy_0000_snail; ((enemy_0000_snail*)m)->init(ENEMY_KIND_0000_SNAIL_GREEN); break;
	case ENEMY_KIND_0000_SNAIL_BLUE:	m = new enemy_0000_snail; ((enemy_0000_snail*)m)->init(ENEMY_KIND_0000_SNAIL_BLUE); break;
	case ENEMY_KIND_0000_SNAIL_RED:		m = new enemy_0000_snail; ((enemy_0000_snail*)m)->init(ENEMY_KIND_0000_SNAIL_RED); break;
	}

	return m;
}

bossBase * enemyManager::createBoss(e_BOSS_KIND kind)
{
	bossBase * m = find(kind, _mBoss);
	if (m == NULL) return NULL;

	switch (kind)
	{
	case BOSS_KIND_0000_KING_SLIME:	break;
	case BOSS_KIND_NONE: break;
	}

	return m;
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

template<typename T>
void enemyManager::releaseMap(map<int, T*> _map)
{
	map<int, T*>::iterator i = _map.begin();
	for (; i != _map.end(); )
	{
		i->second->release();
		SAFE_DELETE(i->second);

		i = _map.erase(i);
	}
}
