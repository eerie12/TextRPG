#include "StageManager.h"
#include "StageNormal.h"
#include "StageEasy.h"
#include "StageHard.h"


DEFINITON_SINGLE(CStageManager)


CStageManager::CStageManager()
{

}


CStageManager::~CStageManager()
{
	Safe_Delete_VecList(m_vecStage);
}

bool CStageManager::Init()
{
	if (!CreateStage(ST_EASY))
		return false;
	if (!CreateStage(ST_NORMAL))
		return false;
	if (!CreateStage(ST_HARD))
		return false;
	return true;
}

void CStageManager::Run()
{
	while (true) 
	{
		int iMenu = OutputMenu();

		if (iMenu == MENU_NONE)
			continue;
		else if (iMenu == MENU_BACK)
			return;

		m_vecStage[iMenu - 1]->Run();

		
	}
	
}

bool CStageManager::CreateStage(STAGE_TYPE eType)
{
	CStage* pStage = NULL;

	switch (eType) 
	{
	case ST_EASY:
		pStage = new CStageEasy;
		break;
	case ST_NORMAL:
		pStage = new CStageNormal;
		break;
	case ST_HARD:
		pStage = new CStageHard;
		break;

	}

	if (!pStage->Init()) 
	{
		SAFE_DELETE(pStage);
		return false;
	}

	m_vecStage.push_back(pStage);

	return true;
}

int CStageManager::OutputMenu()
{
	system("cls");
	cout << "1. Easy" << endl;
	cout << "2. Normal" << endl;
	cout << "3. Hard" << endl;
	cout << endl;
	cout << "4. Back" << endl;
	cout << endl;
	cout << "Stage‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢ : ";
	int iMenu = Input<int>();

	if (iMenu <= MENU_NONE || iMenu > MENU_BACK)
		return MENU_NONE;

	return iMenu;
}
