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

	//Ű�� �ѹ��� ���ȴ���
	bool press(int key);
	//�ѹ� ������ �������
	bool up(int key);
	//Ű�� ��� ���� �ִ���
	bool down(int key);
	//���Ű
	bool toggle(int key);

	// ���콺 ��
	void setWheelUp(function<void(void)> * upFunction);
	void setWheelDown(function<void(void)> * downFunction);
	void wheelUp(void) { if (_callWheelUp) (*_callWheelUp)(); };
	void wheelDown(void) { if (_callWheelDown) (*_callWheelDown)(); };

	// ���� Ű
	void setInputKey(int key) { _inputKey = key; };
	int getInputKey(void) { return _inputKey; };

	// ���콺 ����Ŭ��
	void setDBClick(function<void(void)>* dbClickFunction);
	void dbClick(void) {if (_callDBClick)(*_callDBClick)();}
	keyManager() {}
	~keyManager() {}
};