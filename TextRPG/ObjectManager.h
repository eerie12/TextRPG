#pragma once

#include "value.h"


class CObj;//生成ではなく参照なら先方宣言でも可能
class CObjectManager
{
private:
	//mapはkey,valueで構成
	//一つ目のtemplateのタイプがkey,二つ目のタイプががvalueになる->keyで探索,valueが実際の値をsave
	unordered_map <string, CObj*> m_mapObj;//monster,player->chara->objタイプ使用可能



public:
	bool Init();
	CObj* CreateObject(const string& strKey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strKey);
	CObj* CloneObject(const string& strKey);
	CObj* CloneObject(STAGE_TYPE eType);


	DECLARE_SINGLE(CObjectManager)

};

