#include "stdafx.h"
#include "eventPlayerLevelUp.h"

#include "player.h"

void eventPlayerLevelUp::update(void)
{
	++((player*)_dest)->getStat().stateLimit.Lv;
}
