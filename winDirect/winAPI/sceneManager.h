#pragma once
#include "singletonBase.h"

class gameNode;

class 
sceneManager : public singletonBase<sceneManager>
{
public :
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private :
	static gameNode* _currentScene;		// ���� ��
	static gameNode* _loadingScene;		// �ε� ��
	static gameNode* _readyScene;		// ��ü ������� ��

	mapSceneList _mSceneList;			// �� ����Ʈ
	mapSceneList _mLoadingSceneList;	// �ε� �� ����Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// �� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	// �� ����
	HRESULT changeScene(string sceneName, bool isInit = true);

	// �� �ʱ�ȭ
	HRESULT initScene(string sceneName);

	// �� ��������
	gameNode* find(string sceneName);

	// friend
	// ���������� �㹰������� Ű����
	// private���� ��� ������ ����
	// Ŭ���� �ܺο��� �ۼ��� �Լ� or ���� ���ٰ���
	// friend ������ �ܹ������� �̷����

	// LPVOID : void* ��(� Ÿ���̵� ��ȯ����)
	// �ε� ������ �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager() {};
	~sceneManager() {};
};

