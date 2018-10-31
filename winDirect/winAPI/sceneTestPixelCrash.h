#pragma once
#include "gameNode.h"

class sceneTestPixelCrash : public gameNode
{
private :
	fieldBase* _field;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	sceneTestPixelCrash() {};
	~sceneTestPixelCrash() {};
};

