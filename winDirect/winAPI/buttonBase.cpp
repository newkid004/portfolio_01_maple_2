#include "stdafx.h"
#include "buttonBase.h"

#include "windowBase.h"

fPOINT buttonBase::getAbsPos(void)
{
	return _pos + _bindWindow->getPos();
}
