#pragma once
#include "animation.h"

class animationGroup
{
private:	// �ɹ� ����
	map<string, animation*> _mAnimation;

	string _curAniName;
	animation* _curAni;

	// �� object�� _ani
	// animation* _currentAnimation;

public :	// FW
	HRESULT init(void);
	void update(void);
	void update(float ratio);
	void release(void);

public :	// �ɹ� �Լ� : ����
	animation * add(string key, animation* ani, bool isCurrent = false);
	animation * set(string key, bool isInit = false);
	animation * find(string key);
	animation *& get(void) { return _curAni; };
	string & getCurAniName(void) { return _curAniName; };

public :	// operator
	void operator=(animation* ani) { _curAni = ani; };
	void operator=(animation*& ani) { _curAni = ani; };

public:
	animationGroup() {};
	~animationGroup() {};
};

