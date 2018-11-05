#pragma once
#include "singletonBase.h"
#include "animationGroup.h"
class animationGroupManager:public singletonBase<animationGroupManager>
{
private:
	typedef unordered_map<string, animationGroup*> mAnimationGroup;
	typedef unordered_map<string, animationGroup*>::iterator miAnimationGroup;

private:

	mAnimationGroup _mAnimationGroup;
	miAnimationGroup _miAnimationGroup;

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void addAniGroup(string name, animationGroup* aniGroup);
	void delAniGroup(string name);

	animationGroup* findAniGroup(string name);
	animationGroupManager() {}
	~animationGroupManager() {}
};

