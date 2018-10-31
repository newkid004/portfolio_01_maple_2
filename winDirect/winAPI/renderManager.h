#pragma once
#include "singletonBase.h"

enum e_RENDER_ORDER
{
	// 뒷배경
	RO_BACK_0,
	RO_BACK_1,
	RO_BACK_2,
	RO_BACK_3,

	// 장식물
	RO_DECO_0,
	RO_DECO_1,

	// 포탈
	RO_PORTAL,

	// 보스
	RO_BOSS,

	// 몬스터
	RO_MONSTER,

	// 스킬 : 뒤
	RO_SKILL_BACK,

	// 플레이어
	RO_PLAYER,

	// 스킬 : 앞
	RO_SKILL_FRONT,

	// 앞배경
	RO_FRONT_0,
	RO_FRONT_1,

	// 데미지
	RO_DAMAGE,

	// 아이템
	RO_ITEM,

	// 스킬 : 제일 앞
	RO_SKILL_FRONTEST,

	// 렌더 종류 개수
	RO_COUNT
};

enum e_RENDER_MANAGER_STATE
{
	RMS_CLIP_INTO_CAMERA = 0x0001,

	RMS_NONE = 0
};

class renderManager : public singletonBase<renderManager>
{
private :
	struct tagRender
	{
		image * img;
		fPOINT pos;
		fPOINT clip;
		fPOINT size;

		float alpha;

		function<void(void)>* callBefore;
		function<void(void)>* callAfter;

		tagRender() :
			img(NULL),
			pos(0.0f),
			clip(0.0f),
			size(0.0f),
			alpha(1.0f),
			callBefore(NULL),
			callAfter(NULL)
		{};

		tagRender(image* inImage) : 
			tagRender()
		{
			this->img = inImage;
			this->size = img->getSize();
		};

		tagRender(image* inImage, fPOINT inPos) : 
			tagRender(inImage) 
		{ 
			this->pos = inPos; 
		};

		tagRender(image* img, fPOINT pos, fPOINT sour, fPOINT dest, float alpha = 1.0f, 
			function<void(void)>* callBefore = NULL, function<void(void)>* callAfter = NULL)
		{
			this->img		= img;
			this->pos		= pos;
			this->clip		= sour;
			this->size		= dest;

			this->alpha		= alpha;

			this->callBefore = callBefore;
			this->callAfter = callAfter;
		};
	};

private:
	int					_renderState;
	camera*				_currentCamera;
	vector<tagRender>	_vRenderList[RO_COUNT];

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void add(e_RENDER_ORDER order, image * img, fPOINT pos, fPOINT clip, fPOINT size, float alpha = 1.0f, function<void(void)>* callBefore = NULL, function<void(void)>* callAfter = NULL);

	void setCamera(camera* c) { _currentCamera = c; };

	void setRenderState(e_RENDER_MANAGER_STATE s, int value);
	int  getRenderState(e_RENDER_MANAGER_STATE s) { return 0 < (_renderState & s); };

private :
	void renderList(int order);
	void releaseList(int order);
	bool clipRender(tagRender & r);

public:
	renderManager() {};
	~renderManager() {};
};

