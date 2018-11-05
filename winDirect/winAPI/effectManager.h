#pragma once
#include "singletonBase.h"

class effectBase;

class effectManager : public singletonBase<effectManager>
{
private:
	unordered_map<string, effectBase*> _mEffect;
	unordered_map<string, effectBase*>::iterator _miEffect;
public:
	HRESULT init(void);
	void release(void);
	void update(void){}
	void render(void){}

	void addEffect(string name, effectBase* effect);
	effectBase* findEffect(string name);
	void delEffect(string name);

	effectManager(){}
	~effectManager(){}
};

