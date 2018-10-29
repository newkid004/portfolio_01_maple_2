#pragma once
struct effectInfo
{
	animation* ani;
	image* image;
	float alpha;
	fPOINT position;			//��ġ
	fPOINT offset;				//���� ����
	float rotation;				//ȸ��
	int flip;					//����
	e_RENDER_ORDER renderOrder; //z����
};

class effectBase
{
protected:
	effectInfo _infoEffect;

public:
	virtual HRESULT init(void);
	virtual void release(void){}
	virtual void update(void);
	virtual void render(void);

	effectInfo &getInfo() { return _infoEffect; }

	effectBase(){}
	~effectBase(){}
};

