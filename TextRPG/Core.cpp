#include "Core.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"
#include "Inventory.h"

DEFINITON_SINGLE(CCore)

enum MAIN_MENU 
{
	MM_NONE,
	MM_STAGE,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT,

};

CCore::CCore()
{
}


CCore::~CCore()
{
	
	DESTROY_SINGLE(CObjectManager);
	DESTROY_SINGLE(CStageManager);
	DESTROY_SINGLE(CStoreManager);
	DESTROY_SINGLE(CInventory);
}

LEVELUPINFO CCore::GetLevelUpInfo(JOB eJob)
{
	return m_tLevelUpInfo[eJob -1];
}

bool CCore::Init()
{
	//LeveUp�ɕK�v�Ƃ����\�͒l�㏸��struct
	SetLevelUPInfo();

	//ObjectManager������
	if (!GET_SINGLE(CObjectManager)->Init()) 	
		return false;

	//Stage��������
	if (!GET_SINGLE(CStageManager)->Init())
		return false;

	//Store��������
	if (!GET_SINGLE(CStoreManager)->Init())
		return false;

	//Inventory������
	if (!GET_SINGLE(CInventory)->Init())
		return false;

	return true;

}

void CCore::Run()
{
	while (true) 
	{
		switch (OutputMenu()) 
		{
		case MM_STAGE:
			GET_SINGLE(CStageManager)->Run();
			break;
		case MM_STORE:
			GET_SINGLE(CStoreManager)->Run();
			break;
		case MM_INVENTORY:
			GET_SINGLE(CInventory)->Run();
			break;
		case MM_EXIT:
			return;


		}

	}
}

int CCore::OutputMenu()
{
	system("cls");
	cout << "1.�}�b�v" << endl;
	cout << "2.SHOP" << endl;
	cout << "3.Inventory" << endl;
	cout << endl;
	cout << "4.�I��" << endl;
	cout << endl;
	cout << "���j���[��I�����Ă������� : ";
	int iMenu = Input<int>();//int�Ƃ��ď���
	cout << endl;

	if (iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}

void CCore::SetLevelUPInfo()
{
	//�\�͒l�㏸�̐��l���
	m_tLevelUpInfo[JOB_WARRIOR - 1] = CreateLevelUpInfo(10,15,15,20,100,10);
	m_tLevelUpInfo[JOB_ARCHER - 1] = CreateLevelUpInfo(15,20,10,15,80,30);
	m_tLevelUpInfo[JOB_MAGICIAN - 1] = CreateLevelUpInfo(20,25,5,10,50,50);

}

LEVELUPINFO CCore::CreateLevelUpInfo(int chaAttackMin, int chaAttackMax, int chaArmorMin, int chaArmorMax, int ChaHP, int ChaMP)
{
	LEVELUPINFO tInfo = {};

	//�\�͒l�㏸�̐��l����Input
	tInfo.chaAttackMin = chaArmorMin;
	tInfo.chaAttackMax = chaArmorMax;
	tInfo.chaArmorMin = chaArmorMin;
	tInfo.chaArmorMax = chaArmorMax;
	tInfo.chaHP = ChaHP;
	tInfo.chaMP = ChaMP;

	return tInfo;
}
