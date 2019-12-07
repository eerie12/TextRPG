#include "EditorMonster.h"
#include "Monster.h"
#include "FileStream.h"

DEFINITON_SINGLE(CEditorMonster)

enum EDIT_MONSTER_MENU
{
	EMM_NONE,
	EMM_INSERT,
	EMM_DELETE,
	EMM_OUTPUT,
	EMM_SAVE,
	EMM_LOAD,
	EMM_BACK

};


CEditorMonster::CEditorMonster()
{
}


CEditorMonster::~CEditorMonster()
{
	Safe_Delete_VecList(m_vecMonster);
}

bool CEditorMonster::Init()
{
	return true;
}

void CEditorMonster::Run()
{
	while (true) 
	{
		switch (OutputMenu()) 
		{
		case EMM_INSERT:
			Insert();
			break;
		case EMM_DELETE:
			Delete();
			break;
		case EMM_OUTPUT:
			OutputMonsterList();
			break;
		case EMM_SAVE:
			Save();
			break;
		case EMM_LOAD:
			Load();
			break;
		case EMM_BACK:
			return;

		}
	}
}

int CEditorMonster::OutputMenu()
{
	system("cls");
	cout << "1. モンスター追加" << endl;
	cout << "2. モンスター削除" << endl;
	cout << "3. モンスターリスト" << endl;
	cout << "4. SAVE" << endl;
	cout << "5. LOAD" << endl;
	cout << endl;
	cout << "6. BACK" << endl;
	cout << endl;
	cout << "メニューを選択してください。: ";
	int iMenu = Input<int>();

	if (iMenu <= EMM_NONE || iMenu > EMM_BACK)
		return EMM_NONE;

	return iMenu;
}

void CEditorMonster::Insert()
{
	CMonster* pMonster = new CMonster;

	if (!pMonster->Init()) 
	{
		SAFE_DELETE(pMonster);
		return;

	}

	system("cls");
	cout << "=============== モンスター追加 ===============" << endl;
	cout << "名前 : ";
	char strName[256] = {};
	cin >> strName;

	pMonster->SetName(strName);

	int chaAttMin, chaAttMax, chaArmorMin, chaArmorMax, chaHP, chaMP, chaLevel, chaExp;
	cout << "最小攻撃力 : ";
	cin >> chaAttMin;

	cout << "最大攻撃力 : ";
	cin >> chaAttMax;

	cout << "最小防御力 : ";
	cin >> chaArmorMin;

	cout << "最大防御力 : ";
	cin >> chaArmorMax;

	cout << "HP : ";
	cin >> chaHP;

	cout << "MP : ";
	cin >> chaMP;

	cout << "LEVEL : ";
	cin >> chaLevel;

	cout << "獲得経験値 : ";
	cin >> chaExp;
	
	pMonster->SetCharacterInfo(chaAttMin, chaAttMax, chaArmorMin, chaArmorMax, chaHP, chaMP, chaLevel, chaExp);


	int chaGoldMin, chaGoldMax;
	cout << "(最小)Gold :";
	cin >> chaGoldMin;
	cout << "(最大)Gold :";
	cin >> chaGoldMax;

	pMonster->SetGold(chaGoldMin, chaArmorMax);

	//難易度を選択する。
	int iStage = ST_NONE;

	while (iStage <= ST_NONE || iStage > ST_BACK) 
	{
		cout << "1. Easy" << endl;
		cout << "2. Noraml" << endl;
		cout << "3. Hard" << endl;
		cout << endl;
		cout << "難易度を選択してください。: ";
		iStage = Input<int>();
	}
	
	pMonster->SetStageType((STAGE_TYPE)iStage);

	m_vecMonster.push_back(pMonster);
}

void CEditorMonster::OutputMonsterList()
{
	system("cls");

	cout << "=============== 入力したモンスターの一覧 ===============" << endl;

	
	for (size_t i = 0; i < m_vecMonster.size(); i++) 
	{
		cout << i + 1<< ". ";
		m_vecMonster[i]->Render();
		cout << endl;
	}

	system("pause");
}

void CEditorMonster::Save()
{
	system("cls");
	cout << "=============== FileSave(現在のモンスターの一覧をSAVE) ===============" << endl;

	CFileStream file("MonsterList.mtl", "wb");

	//モンスターの数をSave
	size_t iMonsterCount = m_vecMonster.size();

	file.Write(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++) 
	{
		m_vecMonster[i]->Save(&file);
	}

	cout << "Save Complete" << endl;
	system("pause");
}

void CEditorMonster::Load()
{
	system("cls");
	cout << "=============== FileLoad(全体のモンスターの一覧をLOAD) ===============" << endl;

	CFileStream file("MonsterList.mtl", "rb");

	Safe_Delete_VecList(m_vecMonster);

	//モンスターの数を読んでくる。
	size_t iMonsterCount = 0;

	file.Read(&iMonsterCount, 4);

	for (size_t i = 0; i < iMonsterCount; i++)
	{
		CMonster* pMonster = new CMonster;

		if (!pMonster->Init()) 
		{
			SAFE_DELETE(pMonster);
			return;
		}

		pMonster->Load(&file);

		m_vecMonster.push_back(pMonster);
	}

	cout << "Read Complete" << endl;
	system("pause");
}



void CEditorMonster::Delete()
{
	
	system("cls");
	cout << "=============== FileDelete(現在のモンスターの一覧をDELETE) ===============" << endl;

	Safe_Delete_VecList(m_vecMonster);


	cout << "Delete Complete" << endl;
	system("pause");
	
}
