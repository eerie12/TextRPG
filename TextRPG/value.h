#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <time.h>
using namespace std;

//使用者定義ヘッダー(ユーザーヘッダー)
#include "defines.h"
#include "Flags.h"


template<typename T>
T Input() 
{
	T data;
	cin >> data;

	if (cin.fail()) 
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return 0;

	}
	return data;
}

template <typename T>
void Safe_Delete_VecList(T& p) 
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++) 
	{
		SAFE_DELETE(*iter);
	}

	p.clear();
}

template <typename T>
void Safe_Delete_Map(T& p)
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for (iter = p.begin(); iter != iterEnd; iter++)
	{
		//mapにはkey(first)とvalue(second)で接近
		SAFE_DELETE(iter->second);
	}

	p.clear();
}

//Character Info
typedef struct _tagCharacterInfo
{
	int chaAttackMin;
	int chaAttackMax;
	int chaArmorMin;
	int chaArmorMax;
	int chaHP;
	int chaHPMax;
	int chaMP;
	int chaMPMax;
	int chaLevel;
	int chaExp;

}CHARACTERINFO, *PCHARACTERINFO;

//level up Info
typedef struct _tagLevelUpInfo 
{
	int chaAttackMin;
	int chaAttackMax;
	int chaArmorMin;
	int chaArmorMax;
	int chaHP;
	int chaMP;

}LEVELUPINFO, *PLEVELUPINFO;

#define MAX_LV 10

static int g_chaLvUpTable[MAX_LV] = { 4000,10000,20000,30000,50000,70000,90000,130000,170000,250000 };

//Item Info
typedef struct _tagItemInfo 
{
	ITEM_TYPE eType;
	string    strTypeName;
	int       iPrice;
	int       iSell;
	string    strDesc;

}ITEMINFO, *PITEMINFO;
