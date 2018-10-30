#pragma once
#include "gameNode.h"

class loading;

class sceneLoadingTest : public gameNode
{
private :
	loading* _loading;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :
	void releaseLoading(void);

public:
	sceneLoadingTest() {};
	~sceneLoadingTest() {};
};

