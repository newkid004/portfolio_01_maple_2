#pragma once
#include "windowBase.h"

class windowStatusDetail;

class windowStatus : public windowBase
{
protected :
	windowStatusDetail* _bindWindow;
	bool _isOpenedDetail = false;

public :
	HRESULT init(void) override;
	void render(void) override;

public :
	void initEventCatcher(void);
	void initButton(void);

	void renderInfo(void);

public:
	virtual void show(void) override;
	UI_LIST_ITER close(void) override;

public :
	windowStatusDetail* & getBindWindow(void) { return _bindWindow; };
	bool & getIsOpenedDetail(void) { return _isOpenedDetail; };

public:
	windowStatus() {}
	~windowStatus() {}
};

class windowStatusDetail : public windowBase
{
protected :
	windowStatus* _bindWindow;

protected :
	HRESULT init(void) { return S_OK; };

public :
	HRESULT init(windowStatus* bindWindow) 
	{
		_bindWindow = bindWindow;
		_img = IMAGEMANAGER->find("UI_status_detail");
		_size = _img->getSize(); 
		return S_OK; 
	};
	void render(void);

public :
	virtual void show(void) override 
	{
		_pos = _bindWindow->getPos();
		_pos.x += _bindWindow->getSize().x + 1;

		windowBase::show();
	};

public :
	windowStatusDetail() {};
	~windowStatusDetail() {};
};