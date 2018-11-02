#pragma once
#include "questBase.h"

class questManager:public singletonBase<questManager>
{
private:
	typedef unordered_map<string, questBase*> mQuest;
	typedef unordered_map<string, questBase*>::iterator miQuest;
	
	typedef unordered_map<string, MoneyQuest*> mMoneyQuest;
	typedef unordered_map<string, MoneyQuest*>::iterator miMoneyQuest;

	typedef unordered_map<string, ItemQuest*> mItemQuest;
	typedef unordered_map<string, ItemQuest*>::iterator miItemQuest;
private:
	mQuest			_mQuest;					miQuest			_miQuest;
	mMoneyQuest		_mMoneyQuest;				miMoneyQuest	_miMoneyQuest;
	mItemQuest		_mItemQuest;				miItemQuest		_miItemQuest;



public:
	HRESULT init();
	void release();
	
	void setQuest();

	mQuest&				getmQuest()			{ return _mQuest; }
	mMoneyQuest&		getmMoneyQuest()	{ return _mMoneyQuest; }
	mItemQuest&			getmItemQuest()		{ return _mItemQuest; }
	
	questBase*			findQuest_base(string name);
	MoneyQuest*			findQuest_Money(string name);
	ItemQuest*			findQuest_Item(string name);

	questManager() {};
	~questManager() {};
};

