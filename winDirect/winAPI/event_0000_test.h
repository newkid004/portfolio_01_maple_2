#pragma once
#include "eventBase.h"

// sour : none
// dest : window
// active : 임의 윈도우 trans

class event_0000_test : public eventBase
{
public :
	void update(void);
	void render(void);

protected :
	event_0000_test() {};

public:
	event_0000_test eventBaseCreate2Writter;
	~event_0000_test() {}
};