#include "stdafx.h"
#include "event_0000_test.h"

#include "windowBase.h"

void event_0000_test::update(void)
{
	windowBase* dTarget = (windowBase*)_dest;
	dTarget->trans();
}

void event_0000_test::render(void)
{
}
