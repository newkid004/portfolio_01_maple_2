#pragma once
#include "gameNode.h"

class loading;

class sceneLoadingTest : public gameNode
{
private :
	image * _loadingImage;
	animation* _ani;
	loading* _loading;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	sceneLoadingTest() {};
	~sceneLoadingTest() {};
};

