#pragma once
#include "singletonBase.h"
#include "camera.h"

class cameraManager : public singletonBase<cameraManager>
{
private :
	typedef unordered_map<string, camera*>			mapCamera;
	typedef unordered_map<string, camera*>::iterator	mapiCamera;

private :
	mapCamera _mCamera;

public:
	HRESULT init(void);
	void release(void);

	camera* find(string keyName);

	camera* addCamera(string keyName);
	camera* addCamera(string keyName, fPOINT offset);
	camera* addCamera(string keyName, fPOINT offset, fPOINT size);
	camera* addCamera(string keyName, fPOINT offset, fPOINT size, fPOINT minPos, fPOINT maxPos);

	cameraManager() {};
	~cameraManager() {};
};

