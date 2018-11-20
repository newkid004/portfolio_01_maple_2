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
	_currentFormat = gameNode::getTextFormat() = add("defaultText", L"돋움", 12.f);

	IDWriteTextFormat* text;
	text = add("defaultText_right", L"돋움", 12.f);	text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	text = add("defaultText_center", L"돋움", 12.f);	text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	text = add("statusText", L"돋움", 11.f);
	text = add("shopText", L"돋움", 10.f);

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

IDWriteTextFormat * textManager::add(string name, wchar_t* fontStyle, float size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	IDWriteTextFormat* t = find(name);
	if (t) return t;

	// textFormat 생성
	_writeFactory->CreateTextFormat(
		fontStyle,
		NULL,
		weight,
		style,
		stretch,
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