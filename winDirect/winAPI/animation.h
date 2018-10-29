#pragma once

class image;

class animation
{
private :
	// ������ ����Ʈ
	typedef vector<fPOINT> _vFrameList;
	// ������ �÷��� ����Ʈ
	typedef vector<int> _vPlayList;

private :
	int _frameNum;				// ������ ��
	_vFrameList _frameList;		// ������ ��ġ ����Ʈ
	_vPlayList _playList;		// �÷��� ����Ʈ

	NUM_REAL _frameWidth;			// ������ ����ũ��
	NUM_REAL _frameHeight;			// ������ ����ũ��
	int _frameNumWidth;			// ���� ������ �� ����
	int _frameNumHeight;		// ���� ������ �� ����

	BOOL _isLoop;				// ���� ����
	NUM_REAL _frameUpdateSec;		// �ʴ� ������ ������Ʈ ��
	NUM_REAL _elapsedSec;			// ������ ���� �ð�

	DWORD _nowPlayIndex;		// ���� �÷��� �ε���
	BOOL _isPlay;				// �÷��� ����

public:
	HRESULT init(image* img);
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);
	animation * update(float ratio = 1.0f);

	void setDefPlayFrame(BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(int * playArr = NULL, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(POINT * playArr, int arrLen = 0, BOOL loop = NULL);
	void setPlayFrame(int start, int end, BOOL reverse = NULL, BOOL loop = NULL);
	void setPlayFrame(POINT start, POINT end, BOOL reverse = NULL, BOOL loop = NULL);
	void setFrameIndex(int i) { _nowPlayIndex = i; };
	void setFrameIndex(int x, int y) { _nowPlayIndex = x + (y * _frameNumWidth); };
	void setFrameIndex(POINT pos) { setFrameIndex(pos.x, pos.y); };
	
	// �ʴ� ������ ���� Ƚ��
	void setFPS(float framePerSec) { _frameUpdateSec = 1.0f / framePerSec; };
	void setElapsedSec(float eTime) { _elapsedSec = eTime; };
	void frameUpdate(float elpasedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	// �÷��� ����
	inline BOOL & isPlay(void) { return _isPlay; }
	inline BOOL & isLoop(void) { return _isLoop; }
	inline BOOL isEnd(void) { return _nowPlayIndex == (_playList.size() - 1); }
	// ������ ��ġ
	inline fPOINT & getFramePos(void) { return _frameList[_playList[_nowPlayIndex]]; };
	inline fPOINT & getFramePosIndex(void) { fPOINT & p = _frameList[_playList[_nowPlayIndex]]; return fPOINT{ p.x / _frameWidth, p.y / _frameHeight }; }
	inline int & getFramePlay(void) { return _playList[_nowPlayIndex]; };
	// ������ ũ��
	inline NUM_REAL & getFrameWidth(void) { return _frameWidth; };
	inline NUM_REAL & getFrameHeight(void) { return _frameHeight; };
	inline fPOINT & getFrameSize(void) { return fPOINT{ _frameWidth, _frameHeight }; };
	// ���� ������� �������� ����
	inline DWORD & getNowPlayIndex(void) { return _nowPlayIndex; };
	// ���� �������� minFrame
	inline int & getMinPlayIndex(void) { return *_playList.begin(); };
	// ���� �������� maxFrame : reverse ����
	inline int & getMaxPlayIndex(void) { return *(_playList.end() - 1);};
	inline int getPlaySize(void) { return _playList.size(); };

	// �� ��� �����Ӹ� ����� �޸� ����
	void setAnimationFixed(void);

public :	// operator
	void operator=(animation e);
	void operator=(animation* e);

	animation();
	~animation() {};
};

