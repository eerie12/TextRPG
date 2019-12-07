#pragma once

#include "value.h"


class CObj;//�����ł͂Ȃ��Q�ƂȂ����錾�ł��\
class CObjectManager
{
private:
	//map��key,value�ō\��
	//��ڂ�template�̃^�C�v��key,��ڂ̃^�C�v����value�ɂȂ�->key�ŒT��,value�����ۂ̒l��save
	unordered_map <string, CObj*> m_mapObj;//monster,player->chara->obj�^�C�v�g�p�\



public:
	bool Init();
	CObj* CreateObject(const string& strKey, OBJECT_TYPE eType);
	CObj* FindObject(const string& strKey);
	CObj* CloneObject(const string& strKey);
	CObj* CloneObject(STAGE_TYPE eType);


	DECLARE_SINGLE(CObjectManager)

};

