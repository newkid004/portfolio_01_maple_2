#include "stdafx.h"
#include "eventManager.h"

#include "eventBase.h"

void eventManager::release()
{
	deleteAll();
}

void eventManager::update()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end();)
	{
		(*iter)->update();

		if ((*iter)->getTimeAlive() <= 0)
		{
			delete *iter;
			iter = _lEvent.erase(iter);
		}
		else ++iter;
	}
}

void eventManager::render()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end(); ++iter)
	{
		(*iter)->render();
	}
}

void eventManager::add(eventBase * ev)
{
	_lEvent.push_back(ev);
}

void eventManager::deleteAll()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end(); ++iter)
	{
		delete *iter;
	}
}

