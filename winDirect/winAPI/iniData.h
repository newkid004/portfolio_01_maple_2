#pragma once
#include "singletonBase.h"

/*
	<����>
	���� ���α׷��̳� ������ ��ü�� �ʱ� �������� �ʿ��� ������ ���Ե� �ؽ�Ʈ ����
	
	<�뵵>
	�ַ� ������ �ɼ��� �ٷ� ��
	���� ���� �ٲ�� ���

	<����> : Section, key, value
	[Section]
	Name = Value
*/

struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase<iniData>
{
private :
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private :
	arrIniDatas _vIniData;

public :
	HRESULT init(void);
	void release(void);

	// ������ �߰�
	void addData(char* section, char* key, char* value);
	// ���̺�
	void iniSave(char* fileName);

	// ���ڰ� �ε�
	char* loadDataString(char* fileName, char* section, char* key);
	// ������ �ε�
	int loadDataInt(char* fileName, char* section, char* key);

public:
	iniData() {};
	~iniData() {};
};

