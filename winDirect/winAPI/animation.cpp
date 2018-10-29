#include "stdafx.h"
#include "animation.h"

animation::animation() :
	_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_frameNumWidth(0),
	_frameNumHeight(0),
	_isLoop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_isPlay(FALSE)
{
}


HRESULT animation::init(image * img)
{
	init(
		img->getSize().x,
		img->getSize().y,
		img->getFrameSize().x,
		img->getFrameSize().y);

	return S_OK;
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	// ���� ������ ��
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	// ���� ������ ��
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	// �� ������ ��
	_frameNum = _frameNumWidth * _frameNumHeight;

	// ������ ��ġ ����
	_frameList.clear();
	for (int y = 0; y < _frameNumHeight; y++)
	{
		for (int x = 0; x < _frameNumWidth; x++)
		{
			fPOINT framePos;
			framePos.x = x * _frameWidth;
			framePos.y = y * _frameHeight;
			_frameList.push_back(framePos);
		}
	}

	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{
	if (0 < _frameList.size())
	{
		_frameList.clear();
		_playList.clear();
	}
}

animation * animation::update(float ratio)
{
	frameUpdate(TIMEMANAGER->getElapsedTime() * ratio);
	return this;
}

// �⺻ ������ ����
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	// ���� ������
	_isLoop = loop;
	_playList.clear();

	// ������ ����
	if (reverse)
	{
		// ���� ����
		if (_isLoop)
		{
			// �� �� ������
			for (int i = 0; i < _frameNum; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = _frameNum - 2; i > 0; i--)
				_playList.push_back(i);
		}
		else
		{
			// �� �� ������
			for (int i = 0; i < _frameNum; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = _frameNum - 2; i > 0; i--)
				_playList.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < _frameNum; i++)
			_playList.push_back(i);
	}
}

// ���ϴ� �����Ӹ� ���
void animation::setPlayFrame(int * playArr, int arrLen, BOOL loop)
{
	// ���� ����
	_isLoop = loop;
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
		_playList.push_back(playArr[i]);
}
void animation::setPlayFrame(POINT * playArr, int arrLen, BOOL loop)
{
	// ���� ����
	_isLoop = loop;
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		int playIndex = playArr[i].x + (playArr[i].y * _frameNumWidth);
		_playList.push_back(playIndex);
	}
}
// ������ �߶� ���
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	// ���� ������
	_isLoop = loop;
	_playList.clear();

	// ������ ����
	if (reverse)
	{
		// ���� ����
		if (_isLoop)
		{
			// �� �� ������
			for (int i = start; i <= end; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = end - 2; i > start; i--)
				_playList.push_back(i);
		}
		else
		{
			// �� �� ������
			for (int i = start; i <= end; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = end - 2; i > start; i--)
				_playList.push_back(i);
		}
	}
	else
	{
		for (int i = start; i <= end; i++)
			_playList.push_back(i);
	}
}
void animation::setPlayFrame(POINT start, POINT end, BOOL reverse, BOOL loop)
{
	// ���� ������
	_isLoop = loop;
	_playList.clear();

	int iStart = start.x + (start.y * _frameNumWidth);
	int iEnd = end.x + (end.y * _frameNumWidth);

	// ������ ����
	if (reverse)
	{
		// ���� ����
		if (_isLoop)
		{
			// �� �� ������
			for (int i = iStart; i <= iEnd; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = iEnd - 2; i > iStart; i--)
				_playList.push_back(i);
		}
		else
		{
			// �� �� ������
			for (int i = iStart; i <= iEnd; i++)
				_playList.push_back(i);
			// �� �� ������
			for (int i = iEnd - 2; i > iStart; i--)
				_playList.push_back(i);
		}
	}
	else
	{
		for (int i = iStart; i <= iEnd; i++)
			_playList.push_back(i);
	}
}

// ������ ������Ʈ
void animation::frameUpdate(float elpasedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elpasedTime;

		// ������ ������Ʈ ����
		if (_frameUpdateSec <= _elapsedSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;
			if ((int)_playList.size() <= _nowPlayIndex)
			{
				if (_isLoop)
				{
					_nowPlayIndex = 0;
				}
				else
				{
					_nowPlayIndex--;
					_isPlay = false;
				}
			}
		}

	}
}

void animation::start(void)
{
	_isPlay = true;
	_nowPlayIndex = 0;
}

void animation::stop(void)
{
	_isPlay = false;
	_nowPlayIndex = 0;
}

void animation::pause(void)
{
	_isPlay = false;
}

void animation::resume(void)
{
	_nowPlayIndex = _nowPlayIndex < (int)_playList.size() ? _nowPlayIndex : 0;
	_isPlay = true;
}

// fix
void animation::setAnimationFixed(void)
{
	int playSize = _playList.size();

	// ����
	_vFrameList newFrameList;
	_vPlayList newPlayList;

	newFrameList.resize(playSize);
	newPlayList.resize(playSize);
	for (int i = 0; i < playSize; i++)
	{
		newFrameList[i] = _frameList[_playList[i]];
		newPlayList[i] = i;
	}

	// ����
	_frameList.clear();	_frameList.resize(playSize);
	_playList.clear();	_playList.resize(playSize);

	// ��ü
	copy(newFrameList.begin(), newFrameList.end(), _frameList.begin());
	copy(newPlayList.begin(), newPlayList.end(), _playList.begin());
	_nowPlayIndex = 0;
}

void animation::operator=(animation e)
{
	_frameNum			= e._frameNum;
	
	_frameList			= e._frameList;
	_playList			= e._playList;

	_frameWidth			= e._frameWidth;
	_frameHeight		= e._frameHeight;
	_frameNumWidth		= e._frameNumWidth;
	_frameNumHeight		= e._frameNumHeight;

	_isLoop				= e._isLoop;
	_frameUpdateSec		= e._frameUpdateSec;
	_elapsedSec			= e._elapsedSec;

	_nowPlayIndex		= e._nowPlayIndex;
	
	_isLoop				= e._isLoop;
	_isPlay				= e._isPlay;
}

void animation::operator=(animation * e)
{
	_frameNum			= e->_frameNum;
	
	_frameList			= e->_frameList;
	_playList			= e->_playList;

	_frameWidth			= e->_frameWidth;
	_frameHeight		= e->_frameHeight;
	_frameNumWidth		= e->_frameNumWidth;
	_frameNumHeight		= e->_frameNumHeight;

	_isLoop				= e->_isLoop;
	_frameUpdateSec		= e->_frameUpdateSec;
	_elapsedSec			= e->_elapsedSec;

	_nowPlayIndex		= e->_nowPlayIndex;

	_isLoop				= e->_isLoop;
	_isPlay				= e->_isPlay;
}
