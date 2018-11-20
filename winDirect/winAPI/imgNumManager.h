#pragma once
#include "singletonBase.h"

class imgNumManager : public singletonBase<imgNumManager>
{
private :
	struct tagImageNumber
	{
		image* bindImage;
		fPOINT offset;
		unordered_map<int, float> interval;

		float spaceRatio;
	};

private :
	tagImageNumber* _curImageNumber;
	unordered_map<string, tagImageNumber*> _mImageNumber;

public :
	HRESULT init(void);
	void release(void);

public :
	void add(string name, image* bindImage, fPOINT offset = fPOINT{ 0.f, 0.f }, float spaceRatio = 0.0625f);

	void draw(string * str, fPOINT pos, fRECT * outSize = NULL) { draw(str->c_str(), pos, outSize); };
	void draw(const char* str, fPOINT pos, fRECT * outSize = NULL);

	void drawRight(string * str, fPOINT pos, fRECT * outSize = NULL) { drawRight(str->c_str(), pos, outSize); }
	void drawRight(const char* str, fPOINT pos, fRECT * outSize = NULL) { pos.x -= getSize(str).x; draw(str, pos, outSize); };

	void drawCenter(string * str, fPOINT pos, fRECT * outSize = NULL) { drawCenter(str->c_str(), pos, outSize); }
	void drawCenter(const char* str, fPOINT pos, fRECT * outSize = NULL) { pos.x -= getSize(str).x / 2.f; draw(str, pos, outSize); };

public :
	void setInterval(string name, int number, float interval) { auto f = find(name); if (f == NULL) return; setInterval(f, number, interval); };
	void setInterval(string name, int* number, float* interval, int count) { auto f = find(name); if (!f) return; for (int i = 0; i < count; ++i) setInterval(f, number[i], interval[i]); };
	void setCurImgNumber(string name) { _curImageNumber = find(name); };

	fPOINT getSize(string * str) { return getSize(str->c_str()); };
	fPOINT getSize(const char* str);

private :
	tagImageNumber* find(string name);
	void setInterval(tagImageNumber* imgNum, int number, float interval) { imgNum->interval[number] = interval; };

public:
	imgNumManager() {};
	~imgNumManager() {};
};