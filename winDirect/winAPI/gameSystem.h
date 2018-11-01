#pragma once
#include "singletonBase.h"

class fieldBase;
class playerableBase;

struct tagVolume
{
	float master;
	float BGM;
	float SE;
	float skill;

	tagVolume() :
		master(1.0f),
		BGM(1.0f),
		SE(1.0f),
		skill(1.0f)
	{};
};

struct tagGameOption
{
	tagVolume volume;

};

struct tagShortcut
{
	string name;
	int mapindex;
	int putIndex;

	function<void(void)> active;

	tagShortcut() : putIndex(-1) {};
};

class gameSystem : public singletonBase<gameSystem>
{
private : 
	tagGameOption	_infoOption;
	fieldBase*		_curField;
	playerableBase*	_player;

	map<string, tagShortcut*>	_mShortcutTotal;
	vector<tagShortcut*>		_vShortcutSetting;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public :	// * option * //
	tagGameOption& getInfoOption(void) { return _infoOption; };

	// ----- volume ----- //
	float getVolumeMaster(void)	{ return _infoOption.volume.master; };
	float getVolumeBGM(void)	{ return _infoOption.volume.BGM		* getVolumeMaster(); };
	float getVolumeSE(void)		{ return _infoOption.volume.SE		* getVolumeMaster(); };
	float getVolumeSkill(void)	{ return _infoOption.volume.skill	* getVolumeMaster(); };

public :	// * field * //
	fieldBase *& getField(void) { return _curField; };

public :	// * player * //
	playerableBase *& getPlayer(void) { return _player; };

public :	// * shortcut * //
	void addShortcut(string name, int index, function<void(void)>* active);
	void putShortcut(string name, int virtualKey);
	void useShortcut(int virtualKey) { _vShortcutSetting[virtualKey]->active(); };

private :
	tagShortcut* findShortcut(string name);


public:
	gameSystem() {};
	~gameSystem() {};
};

