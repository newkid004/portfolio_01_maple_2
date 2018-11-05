#pragma once
#include "singletonBase.h"
// fmod �߰�
#include "inc/fmod.hpp"

#pragma comment (lib, "lib/fmodex_vc.lib")
/*
FMOD
- ���忣�� ���̺귯��
- �𸮾�, ����Ƽ���� ���̼��� ������� ���� �⺻ ����Ǿ� ����
*/

#define MAX_SOUND 64
#define TEMP_SOUND 5
#define TOTAL_SOUND_COUNT (MAX_SOUND + TEMP_SOUND)

using namespace FMOD;

class cSound
{
public :
	System* _system;
	Sound* _sound;
	Channel* _channel;

	ChannelGroup* _cGroup = NULL;

public :
	HRESULT init(System* system);
	void release(void);
	void update(void);

public :
	// ���� ����
	void play(float volume = -1.0f, float pitch = 0.0f);
	void stop(void);
	void pause(void);
	void resum(void);

	bool isPlaySound(void);
	bool isPauseSound(void);

	void setVolume(float volume);
	float getVolume(void);

	void setMute(bool isMute) { _channel->setMute(isMute); };
	bool getMute(void);

	unsigned int getPlayPos(void);
	void setPlayPos(unsigned int posMs) { _channel->setPosition(posMs, FMOD_TIMEUNIT_MS); };

	unsigned int getSoundLength();

public:
	cSound() {};
	~cSound() {};
};

class soundManager : public singletonBase<soundManager>
{
private:
	int _maxSoundCustom;
	
	System* _system;
	unordered_map<string, cSound*> _mSound;

	ChannelGroup* _cgMaster;

	ChannelGroup* _cgBGM;
	ChannelGroup* _cgSE;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	// ���� ����
	cSound* addSound(const char* soundName, const char * fileName, bool background, bool loop);
	cSound* find(string soundName);

	// ���� ����
	void stopAll(void);

	int& getMaxSoundCustom(void) { return _maxSoundCustom; }

	ChannelGroup* getBGM(void) { return _cgBGM; };
	ChannelGroup* getSE(void) { return _cgSE; };

public:
	soundManager() { _maxSoundCustom = -1; };
	~soundManager() {};
};

