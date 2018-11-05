#include "stdafx.h"
#include "textManager.h"

#include "gameNode.h"

HRESULT textManager::init(void)
{
	// writeFactory 생성
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(_writeFactory),
		(IUnknown**)&_writeFactory);

	// 텍스트 색상 : black
	_renderTarget->CreateSolidColorBrush(C_COLOR_BLACK, &_brush);

	// 기본 텍스트 생성
	_currentFormat = gameNode::getTextFormat() = add("defaultText", L"돋움체", 12.f);

	return S_OK;
}

void textManager::release(void)
{
	for (auto i = _mTextFormat.begin(); i != _mTextFormat.end();)
	{
		i->second->Release();
		i = _mTextFormat.erase(i);
	}

	_brush->Release();
	_writeFactory->Release();
}

IDWriteTextFormat * textManager::add(string name, wchar_t* fontStyle, float size)
{
	IDWriteTextFormat* t = find(name);
	if (t) return t;

	// textFormat 생성
	_writeFactory->CreateTextFormat(
		fontStyle,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"",
		&t);

	// 텍스트 정렬 : left
	t->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	t->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	_mTextFormat.insert(make_pair(name, t));
	return t;
}

IDWriteTextFormat * textManager::find(string name)
{
	auto i = _mTextFormat.find(name);
	if (i == _mTextFormat.end()) return NULL;

	return i->second;
}

IDWriteTextFormat * textManager::setFont(string name)
{
	IDWriteTextFormat* f = find(name);
	if (f == NULL) return NULL;

	return _currentFormat = f;
}

void textManager::drawText(const wchar_t * text, int length, D2D1_RECT_F* range, function<void(void)> * callBefore, IDWriteTextFormat * format)
{
	if (callBefore)
	{
		(*callBefore)();
		delete callBefore;
	}

	if (format)
	{
	_renderTarget->DrawTextA(
		text,
		length,
		format, 
		*range,
		_brush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP);

		return;
	}

	if (_currentFormat)
	{
		_renderTarget->DrawTextA(
			text,
			length,
			_currentFormat,
			*range,
			_brush,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}
}