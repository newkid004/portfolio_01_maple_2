#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init(void)
{


	return S_OK;
}

void iniData::release(void)
{
}

void iniData::addData(char * section, char * key, char * value)
{
	// ini ������ ����ü ���� �� �ʱ�ȭ
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	// ini������ ����ü ���Ϳ� �ֱ�
	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniData::iniSave(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	// sprintf : Ư�� ���ۿ� Ư�� �������� ���ڸ� ���
	sprintf_s(dir, "\\save/%s.ini", fileName);

	// ���� ������ ��������
	// GetCurrentDirectory(�۾� ���丮�� ��� ����ũ��, �۾� ���丮�� ���)
	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	for (int i = 0; i < (int)_vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];

		// ���� ����
		// WritePrivateProfileString
		// ���Ͽ� ����(���ڿ�)�� ���� �ش� ���ǰ� Ű���� ������ �ڵ����� �������ִ� �Լ�
		WritePrivateProfileString(
			vData[0].section,
			vData[0].key,
			vData[0].value,
			str);

		vData.clear();
	}
	_vIniData.clear();
}

char * iniData::loadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	sprintf_s(dir, "\\save\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	char data[64] = { NULL };

	// ���� �б�
	// GetPrivateProfileString
	// ������ ����(���ڿ�)�� �о���� �Լ�
	GetPrivateProfileString(
		section,
		key,
		"",			// section, key ����ġ : defalut��
		data,		// value�� ������ ����
		64,			// ���� ������
		str);

	return data;
}

int iniData::loadDataInt(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(str, sizeof(dir));
	sprintf_s(dir, "\\save\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat_s(str, dir);

	// GetPrivateProfileInt
	// ������ ����(����)�� �о���� �Լ�
	return GetPrivateProfileInt(section, key, 0, str);;
}
