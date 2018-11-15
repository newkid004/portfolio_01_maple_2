#pragma once
#include "objectDef.h"
#include "classesDef.h"
#include "itemDef.h"

class image;

//���� ����ü
struct ray
{
	fPOINT	destfPos;
	fPOINT	sourfPos;

	NUM_REAL	distance;

	ray() {
		destfPos = fPOINT{ 0.0f,0.0f };
		sourfPos = fPOINT{ 0.0f,0.0f };
		distance = 0.0f;
	};
};

//���� ����ü ����
typedef struct rayStruct
{
	ray	upperRay;				//������ ray
	ray bottomRay;				//�Ʒ��� ray
	ray rightRay[RAY_NUM];		//������ ray
	ray leftRay[RAY_NUM];		//����	ray
}RAYSTRUCT;


class baseObject
{
protected:
	image*			_img;

	objDef::OBJECT	_objectKind;

	fPOINT			_position;
	fRECT			_collision;
public:
	baseObject() : _img(NULL), _objectKind(objDef::OBJECT_NONE) {};
	~baseObject() {};

public:
	virtual HRESULT init(void) { return S_OK; };
	virtual void release(void) {};
	virtual void update(void) {};
	virtual void render(void) {};
	
public :
	void setObjectKind(objDef::OBJECT objectID)			{ _objectKind = objectID; }


	objDef::OBJECT getObjectKind()						{ return _objectKind; }

	fPOINT getPosition()								{ return _position; }
	POINT  getPosition_re_POINT()						{ return MY_UTIL::pos2point(_position); }

	fRECT& getCollision()							{ return _collision; }
	fRECT getCollisionRect() { return pos2fRect(fPOINT{ _position.x + _collision.LT.x,_position.y + _collision.LT.y },
								fPOINT{ _position.x + _collision.RB.x,_position.y + _collision.RB.y }); }
};

