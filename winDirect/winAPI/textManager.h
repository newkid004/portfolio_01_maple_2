#pragma once
#include "singletonBase.h"

class textManager : public singletonBase<textManager>
{
private :
	unordered_map<string, IDWriteTextFormat*> _mTextFormat;

private :
	ID2D1SolidColorBrush*	_brush;
	IDWriteFactory*			_writeFactory;
	IDWriteTextFormat*		_currentFormat;

public :
	HRESULT init(void);
	void release(void);

public :
	IDWriteTextFormat* add(string name, wchar_t* fontStyle, float size);
	IDWriteTextFormat* find(string name);
	IDWriteTextFormat* setFont(string name);

public :
	void drawText(const wchar_t* text, int length, D2D1_RECT_F range, function<void(void)> * callBefore = NULL, IDWriteTextFormat* format = NULL);

public :
	void setTextColor(D2D1_COLOR_F * color) { _brush->SetColor(*color); };

public:
	textManager() {};
	~textManager() {};
};

