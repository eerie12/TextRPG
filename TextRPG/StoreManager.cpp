#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"

DEFINITON_SINGLE(CStoreManager)

CStoreManager::CStoreManager()
{
}


CStoreManager::~CStoreManager()
{
	Safe_Delete_VecList(m_vecstore);
}

bool CStoreManager::Init()
{
	//WeaponStore¶¬
	CStore* pStore = CreateStore(STORE_WEAPON);

	//ArmorStore¶¬
	pStore =  CreateStore(STORE_ARMOR);

	return true;
}

void CStoreManager::Run()
{
	while (true) 
	{
		int iMenu = OutputMenu();

		if (iMenu == STORE_NONE)
			continue;
		else if (iMenu == STORE_BACK)
			break;

		m_vecstore[iMenu - 1]->Run();

	}
}

CStore * CStoreManager::CreateStore(STORE_TYPE eType)
{
	CStore* pStore = NULL;

	switch (eType) 
	{
	case STORE_WEAPON:
		pStore = new CStoreWeapon;
		break;
	case STORE_ARMOR:
		pStore = new CStoreArmor;
		break;

	}

	if (!pStore->Init()) 
	{
		SAFE_DELETE(pStore);
		return NULL;

	}

	m_vecstore.push_back(pStore);

	return pStore;
}

int CStoreManager::OutputMenu()
{
	system("cls");
	cout << "1.WeaponStore" << endl;
	cout << "2.ArmorStore" << endl;
	cout << endl;
	cout << "3.Back" << endl;
	cout << endl;
	cout << "Store‚ð‘I‚ñ‚Å‚­‚¾‚³‚¢B: ";
	int iStore = Input<int>();

	if (iStore <= STORE_NONE || iStore > STORE_BACK)
		return STORE_NONE;

	return iStore;
}
