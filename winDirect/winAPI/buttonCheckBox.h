#pragma once
#include "buttonBase.h"

class buttonCheckBox : public buttonBase
{
private :
	bool _isCheck;

public :
	HRESULT init(void) { _isCheck = false; _img = IMAGEMANAGER->find("UI_checkBox"); _size = _img->getFrameSize(); return S_OK; }
	UI_LIST_ITER update(void) 
	{
		if (IsClickRect(getAbsRect(), _ptMouse))
		{
			if (KEYMANAGER->press(VK_LBUTTON))
			{
				_isCheck = !_isCheck;
				return WINMANAGER->getIgnoreIter();
			}
		}
		return _bindWindow->getIter();
	};
	void render(void)
	{
		IMAGEMANAGER->statePos(_bindWindow->getPos() + _pos);
		_img->frameRender(fPOINT(_isCheck, 0));
	};
	
public :
	bool & getIsCheck(void) { return _isCheck; };

public :
	bool operator==(bool b) { return _isCheck == b; };
	bool operator!=(bool b) { return _isCheck != b; };

public:
	buttonCheckBox() {};
	~buttonCheckBox() {};
};

