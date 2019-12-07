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
	//Player����
	CObj* pPlayer = CreateObject("Player", OT_PLAYER);

	//�����X�^�[���X�g��Read
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
		//�����X�^�[���ݒ肳��Ȃ������ꍇ�A��{�ݒ�̃����X�^�[��o�ꂳ����B
		if (iMonsterCount_Easy == 0) 
		{
			//CreateObject�֐�->�����X�^�[����->CObj*�^�C�v��return
			//�����X�^�[�̊�{�ϐ��̓����X�^�[�N���X��character�N���X�������Ă���
			//->�����X�^�[�N���X�Ɍ`��ϊ�->Save���@�\���g��
			CMonster* pMonster = (CMonster*)CreateObject("Goblin", OT_MONSTER);

			pMonster->SetName("�S�u����");
			pMonster->SetCharacterInfo(10, 20, 3, 5, 100, 10, 1, 1000);
			pMonster->SetStageType(ST_EASY);
			pMonster->SetGold(100, 200);
		}
		if (iMonsterCount_Normal == 0)
		{
			CMonster* pMonster = (CMonster*)CreateObject("Troll", OT_MONSTER);

			pMonster->SetName("�g���[��");
			pMonster->SetCharacterInfo(50, 90, 50, 60, 2000, 500, 5, 8000);
			pMonster->SetStageType(ST_NORMAL);
			pMonster->SetGold(500, 1000);
		}
		if (iMonsterCount_Hard == 0)
		{
			CMonster* pMonster = (CMonster*)CreateObject("Dragon", OT_MONSTER);

			pMonster->SetName("�h���S��");
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


	m_mapObj.insert(make_pair(strKey, pObj));//map�g�p�̎�insert(make_pair(key,value))->�v�b�V��==insert


	return pObj;
}

CObj * CObjectManager::FindObject(const string & strKey) 
{
	unordered_map<string, CObj*>::iterator iter = m_mapObj.find(strKey);

	if (iter == m_mapObj.end())
		return NULL;

	return iter->second;

}
//�I�u�W�F�N�g���R�s�[ -> ���� -> �Ԋ҂���֐�
CObj * CObjectManager::CloneObject(const string & strKey)
{
	//�R�s�[����I�u�W�F�N�g��T��
	CObj * pOrigin = FindObject(strKey);

	//pOrigin��Null�𔭌��ł��Ȃ������ꍇ
	if (!pOrigin)
		return NULL;

	//�����ł�����V�����I�u�W�F�N�g�����Ԋ�
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
	//�����X�^�[�̐� -> �����_���Ń����X�^�[�������Ă���B-> Clone��make
	int idx = rand() % vecMonster.size();
	return vecMonster[idx]->Clone();
}
