#pragma once
#include "windowBase.h"
class windowStatus : public windowBase
{
private:
	bool _isDetailsOpen = false;
public:
	virtual void show(void) override { WINMANAGER->show(this); if (_isDetailsOpen)WINMANAGER->find("stat_details")->show(); };
	UI_LIST_ITER close(void) override 
	{
		_isDetailsOpen = WINMANAGER->find("stat_details")->isShow();
		WINMANAGER->find("stat_details")->close();
		return WINMANAGER->close(this);
	};
public:
	windowStatus(){}
	~windowStatus(){}
};

