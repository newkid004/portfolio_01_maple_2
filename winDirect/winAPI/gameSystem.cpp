#include "stdafx.h"
#include "gameSystem.h"


HRESULT gameSystem::init(void)
{
	initShortcut();

	return S_OK;
}

void gameSystem::release(void)
{
	releaseShortcut();
}

void gameSystem::update(void)
{
	updateShortcut();
}

void gameSystem::render(void)
{
}

void gameSystem::initShortcut(void)
{
	_vShortcutSetting.resize(256, NULL);

	// 방향키 설정
	addShortcut("DIR_UP",		-1, [](void)->void {}); putShortcut("DIR_UP", VK_UP);
	addShortcut("DIR_DOWN",		-1, [](void)->void {}); putShortcut("DIR_DOWN", VK_DOWN);
	addShortcut("DIR_LEFT",		-1, [](void)->void {}); putShortcut("DIR_LEFT", VK_LEFT);
	addShortcut("DIR_RIGHT",	-1, [](void)->void {}); putShortcut("DIR_RIGHT", VK_RIGHT);
}

void gameSystem::releaseShortcut(void)
{
	_vShortcutSetting.clear();
	for (auto i = _mShortcutTotal.begin(); i != _mShortcutTotal.end();)
	{
		SAFE_DELETE(i->second);
		i = _mShortcutTotal.erase(i);
	}
}

void gameSystem::updateShortcut(void)
{
	useShortcut(KEYMANAGER->getInputKey());		// 단축키 사용
}

void gameSystem::addShortcut(string name, int index, const function<void(void)> & active)
{
	tagShortcut* sc = findShortcut(name);
	if (sc != NULL) return;

	sc = new tagShortcut;
	sc->name = name;
	sc->mapindex = index;
	sc->active = active;

	_mShortcutTotal.insert(make_pair(name, sc));
}

void gameSystem::putShortcut(string name, int virtualKey)
{
	tagShortcut* sc = findShortcut(name);
	if (sc == NULL) return;

	tagShortcut** settedSc = &_vShortcutSetting[virtualKey];
	if (*settedSc == NULL)
		sc->putIndex = virtualKey;
	else
		swaper(sc->putIndex, (*settedSc)->putIndex);

	*settedSc = sc;
}

gameSystem::tagShortcut * gameSystem::findShortcut(string name)
{
	auto iter = _mShortcutTotal.find(name);
	if (iter == _mShortcutTotal.end()) return NULL;

	return iter->second;
}