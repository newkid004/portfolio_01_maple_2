#include "stdafx.h"
#include "eventManager.h"

#include "eventBase.h"
#include "eventCatcher.h"

HRESULT eventManager::init()
{
	initCatcher();
	auto & i = getEventCatcherArray(0x0000);

	return S_OK;
}

void eventManager::release()
{
	deleteAll();

	releaseCatcher();
}

void eventManager::update()
{
	for (auto iter = _lEvent.begin(); iter != _lEvent.end();)
	{
		V_EVENT_CALL & vCatcher = getEventCatcherArray((*iter)->getParamType());

		// catcherBefore -> event -> catcherAfter
		for (auto cIter : vCatcher) if (cIter->getBeforeActive()) (*cIter->getBeforeActive())(*iter);
		(*iter)->update();
		for (auto cIter : vCatcher) if (cIter->getAfterActive()) (*cIter->getAfterActive())(*iter);

		if ((*iter)->getTimeAlive() <= 0.f)
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

void eventManager::initCatcher(void)
{
}

void eventManager::releaseCatcher(void)
{
	auto iterType = _mEventCatcher.begin();
	for (; iterType != _mEventCatcher.end();)
	{
		auto iterKind = iterType->second.begin();
		for (; iterKind != iterType->second.end();)
		{
			auto iterAct = iterKind->second.begin();
			for (; iterAct != iterKind->second.end();)
			{
				auto iterCall = iterAct->second.begin();
				for (; iterCall != iterAct->second.end();)
				{
					auto & vCatcher = iterCall->second;
					for (int i = 0; i < vCatcher.size(); ++i)
					{
						vCatcher[i]->release();
						SAFE_DELETE(vCatcher[i]);
					}
					vCatcher.clear();

					iterCall = iterAct->second.erase(iterCall);
				}
				iterAct = iterKind->second.erase(iterAct);
			}
			iterKind = iterType->second.erase(iterKind);
		}
		iterType = _mEventCatcher.erase(iterType);
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

V_EVENT_CALL & eventManager::getEventCatcherArray(int param)
{
	return _mEventCatcher
		[param & 0x000f]
		[(param & 0x00f0) >> 4]
		[(param & 0x0f00) >> 8]
		[(param & 0xf000) >> 12];
}

