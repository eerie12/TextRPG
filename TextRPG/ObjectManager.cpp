#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITON_SINGLE(CObjectManager)


CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	//Player生成
	CObj* pPlayer = CreateObject("Player", OT_PLAYER);

	//モンスターリストをRead
	CFileStream file("MonsterList.mtl", "rb");



	if (file.GetOpen()) 
	{

		int iMonsterCount = 0;
		
		int iMonsterCount_Easy = 0;
		int iMonsterCount_Normal = 0;
		int iMonsterCount_Hard = 0;
		
		
		file.Read(&iMonsterCount, 4);

		for (int i = 0; i < iMonsterCount; i++) 
		{
			CMonster* pMonster = new CMonster;

			pMonster->Load(&file);

			m_mapObj.insert(make_pair(pMonster->GetName(), pMonster));

			
			if (pMonster->GetStageType() == ST_EASY) 
			{
				++iMonsterCount_Easy;
			}
			else if (pMonster->GetStageType() == ST_NORMAL)
			{
				++iMonsterCount_Normal;
			}
			else if (pMonster->GetStageType() == ST_HARD)
			{
				++iMonsterCount_Hard;
			}
			

		}
		//モンスターが設定されなかった場合、基本設定のモンスターを登場させる。
		if (iMonsterCount_Easy == 0) 
		{
			//CreateObject関数->モンスター生成->CObj*タイプをreturn
			//モンスターの基本変数はモンスタークラスやcharacterクラスが持っている
			//->モンスタークラスに形を変換->Saveし機能を使う
			CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);

			pMonster->SetName("ゴブリン");
			pMonster->SetCharacterInfo(10, 20, 3, 5, 100, 10, 1, 1000);
			pMonster->SetStageType(ST_EASY);
			pMonster->SetGold(100, 200);
		}
		if (iMonsterCount_Normal == 0)
		{
			CMonster* pMonster = (CMonster*)CreateObject("Troll", OT_MONSTER);

			pMonster->SetName("トロール");
			pMonster->SetCharacterInfo(50, 90, 50, 60, 2000, 500, 5, 8000);
			pMonster->SetStageType(ST_NORMAL);
			pMonster->SetGold(500, 1000);
		}
		if (iMonsterCount_Hard == 0)
		{
			CMonster* pMonster = (CMonster*)CreateObject("Dragon", OT_MONSTER);

			pMonster->SetName("ドラゴン");
			pMonster->SetCharacterInfo(150, 250, 150, 250, 10000, 10000, 10, 25000);
			pMonster->SetStageType(ST_HARD);
			pMonster->SetGold(30000, 50000);
		}
		
	}
	return true;
}

CObj * CObjectManager::CreateObject(const string& strKey, OBJECT_TYPE eType)
{
	CObj* pObj = NULL;

	switch (eType) 
	{
	case OT_PLAYER:
		pObj = new CPlayer; 
		break;

	case OT_MONSTER:
		pObj = new CMonster;
		break;

	}

	if (!pObj -> Init())
	{
		SAFE_DELETE(pObj);
		return NULL;

	}


	m_mapObj.insert(make_pair(strKey, pObj));//map使用の時insert(make_pair(key,value))->プッシュ==insert


	return pObj;
}

CObj * CObjectManager::FindObject(const string & strKey) 
{
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strKey);

	if (iter == m_mapObj.end())
		return NULL;

	return iter->second;

}
//オブジェクトをコピー -> 生成 -> 返還する関数
CObj * CObjectManager::CloneObject(const string & strKey)
{
	//コピーするオブジェクトを探索
	CObj * pOrigin = FindObject(strKey);

	//pOriginがNullを発見できなかった場合
	if (!pOrigin)
		return NULL;

	//発見できたら新しいオブジェクトを作り返還
	return pOrigin->Clone();

	return nullptr;
}

CObj * CObjectManager::CloneObject(STAGE_TYPE eType)
{
	vector<CMonster*> vecMonster;

	unordered_map<string, CObj*>:: iterator iter;

	for (iter = m_mapObj.begin(); iter != m_mapObj.end(); iter++) 
	{
		if (iter->second->GetObjectType() == OT_MONSTER)
		{
			CMonster* pMonster = (CMonster*)iter->second;

			if (pMonster->GetStageType() == eType)
				vecMonster.push_back(pMonster);
		}
	}
	if (vecMonster.empty())
		return NULL;
	//モンスターの数 -> ランダムでモンスターを持ってくる。-> Cloneをmake
	int idx = rand() % vecMonster.size();
	return vecMonster[idx]->Clone();
}
