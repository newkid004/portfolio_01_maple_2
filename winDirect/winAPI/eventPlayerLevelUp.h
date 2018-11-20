#pragma once
#include "eventBase.h"

class eventPlayerLevelUp : public eventBase
{
public :
	void update(void) override;

public :
	eventPlayerLevelUp() 
	{
		_paramType = makeParamType(
			makeEventParam(
				ET_PLAYER,
				EK_PLAYER_NONE,
				EA_PLAYER_STATUS_NONE,
				EC_PLAYER_STATUS_CHANGE_NONE),
			makeEventParam(
				ET_PLAYER,
				EK_PLAYER_NONE,
				EA_PLAYER_STATUS_LEVEL,
				EC_PLAYER_STATUS_CHANGE_INCREASE));

		_sour = _dest = GAMESYSTEM->getPlayer();

		_timeAlive = -1.f;
	};
	~eventPlayerLevelUp() {};
};
