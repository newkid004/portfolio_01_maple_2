#pragma once
#include "singletonBase.h"

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	int _inputKey;
	BOOL _keyUp[KEYMAX];
	BOOL _keyDown[KEYMAX];

	function<void(void)> * _callWheelUp;
	function<void(void)> * _callWheelDown;
	function<void(void)> * _callDBClick;
public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	void release(void);

public :
	//Ű�� �ѹ��� ���ȴ���
	bool press(int key);
	//�ѹ� ������ �������
	bool up(int key);
	//Ű�� ��� ���� �ִ���
	bool down(int key);
	//���Ű
	bool toggle(int key);

public :
	// ���콺 ��
	void setWheelUp(function<void(void)> * upFunction, bool isDelete = true);
	void setWheelDown(function<void(void)> * downFunction, bool isDelete = true);
	void wheelUp(void) { if (_callWheelUp) (*_callWheelUp)(); };
	void wheelDown(void) { if (_callWheelDown) (*_callWheelDown)(); };

	// ���� Ű
	void setInputKey(int key) { _inputKey = key; };
	int getInputKey(void) { return _inputKey; };

	// ���콺 ����Ŭ��
	void setDBClick(function<void(void)>* dbClickFunction, bool isDelete = true);
	void dbClick(void) {if (_callDBClick)(*_callDBClick)();}

	// Ű �ʱ�ȭ
	void resetFunctional(bool isDelete = false);

public :
	keyManager() {}
	~keyManager() {}
};