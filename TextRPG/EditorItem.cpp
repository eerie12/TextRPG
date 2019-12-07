#include "EditorItem.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "FileStream.h"

DEFINITON_SINGLE(CEditorItem)

enum EDIT_ITEM_MENU
{
	EIM_NONE,
	EIM_INSERT,
	EIM_DELETE,
	EIM_OUTPUT,
	EIM_SAVE,
	EIM_LOAD,
	EIM_BACK

};

CEditorItem::CEditorItem()
{
}


CEditorItem::~CEditorItem()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);
}

bool CEditorItem::Init()
{
	return true;
}

void CEditorItem::Run()
{
	while (true)
	{
		switch (OutputMenu())
		{
		case EIM_INSERT:
			Insert();
			break;
		case EIM_DELETE:
			Delete();
			break;
		case EIM_OUTPUT:
			OutputStoreList();
			break;
		case EIM_SAVE:
			Save();
			break;
		case EIM_LOAD:
			Load();
			break;
		case EIM_BACK:
			return;

		}
	}
}

int CEditorItem::OutputMenu()
{
	system("cls");
	cout << "1. Item追加" << endl;
	cout << "2. Item削除" << endl;
	cout << "3. Itemリスト" << endl;
	cout << "4. SAVE" << endl;
	cout << "5. LOAD" << endl;
	cout << endl;
	cout << "6. BACK" << endl;
	cout << endl;
	cout << "メニューを選択してください。: ";
	int iMenu = Input<int>();

	if (iMenu <= EIM_NONE || iMenu > EIM_BACK)
		return EIM_NONE;

	return iMenu;

}

void CEditorItem::Insert()
{
	CItem* pItem = NULL;

	system("cls");
	cout << "=============== Item追加 ===============" << endl;
	int iItemType = -1;
	while (iItemType <= 0 || iItemType > ITEM_MAX) 
	{
		cout << "1. 武器" << endl;
		cout << "2. 防具" << endl;
		cout << endl;
		cout << "Itemの種類を選択してください。 : ";
		iItemType = Input<int>();
	}

	
	switch (iItemType - 1) 
	{
	case ITEM_WEAPON:
		pItem = new CItemWeapon;
		break;
	case ITEM_ARMOR:
		pItem = new CItemArmor;
		break;

	}

	if (!pItem->Init())
	{
		SAFE_DELETE(pItem);
		return;

	}

	cin.ignore(1024, '\n');
	cout << "名前 : ";
	char strName[256] = {};
	cin.getline(strName, 255);

	pItem -> SetName(strName);

	int iPrice,  iSell;
	cout << "Price : ";
	cin >> iPrice;

	cout << "Sell : ";
	cin >> iSell;

	switch (iItemType - 1) 
	{
	case ITEM_WEAPON: 
	{
		int iAttMin, iAttMax;
		cout << "最小攻撃力 : ";
		iAttMin = Input<int>();

		cout << "最大攻撃力 : ";
		iAttMax = Input<int>();

		int fCritical;
		cout << "Criticalの確率 : ";
		fCritical = Input<float>();

		((CItemWeapon*)pItem)->SetWeaponInfo(iAttMin, iAttMax, fCritical);
	}
	break;
	case ITEM_ARMOR:
	{
		int iDefMin, iDefMax;
		cout << "最小防御力 : ";
		iDefMin = Input<int>();

		cout << "最大防御力 : ";
		iDefMax = Input<int>();

		((CItemArmor*)pItem)->SetArmorInfo(iDefMin, iDefMax);
	}
	break;
	}

	char strDesc[256] = {};

	cin.ignore(1024, '\n');
	cout << "Itemの説明 : ";
	cin.getline(strDesc, 265);

	pItem->SetItemInfo((ITEM_TYPE)(iItemType - 1), iPrice, iSell, strDesc);

	switch (iItemType - 1) 
	{
	case ITEM_WEAPON:
		m_vecWeapon.push_back(pItem);
		break;
	case ITEM_ARMOR:
		m_vecArmor.push_back(pItem);
		break;
	}
}

void CEditorItem::OutputStoreList()
{
	system("cls");
	cout << "===============武器ショップ===============" << endl;
	for (size_t i = 0; i < m_vecWeapon.size(); i++) 
	{
		cout << i + 1 << ". ";
		m_vecWeapon[i]->Render();
		cout << endl;
	}

	cout << "===============防具ショップ===============" << endl;
	for (size_t i = 0; i < m_vecArmor.size(); i++)
	{
		cout << i + 1 << ". ";
		m_vecArmor[i]->Render();
		cout << endl;
	}
	system("pause");
}

void CEditorItem::Save()
{
	CFileStream file("StoreWeapon.swp", "wb");

	if (file.GetOpen())
	{
		//武器数をSave。
		size_t iCount = m_vecWeapon.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			m_vecWeapon[i]->Save(&file);
		}
		file.Close();
	}

	//防具ショップSave

	if (file.Open("StoreArmor.sar","wb"))
	{
		//防具の数をSave。
		size_t iCount = m_vecArmor.size();

		file.Write(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			m_vecArmor[i]->Save(&file);
		}
		file.Close();
	}

	cout << "ショップリストSave完了" << endl;
	system("pause");
}



void CEditorItem::Load()
{
	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);

	CFileStream file("StoreWeapon.swp", "rb");

	if (file.GetOpen())
	{
		//武器数をLoad。
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			CItemWeapon* pItem = new CItemWeapon;

			if (!pItem->Init()) 
			{
				SAFE_DELETE(pItem);
				return;
			}

			pItem->Load(&file);

			m_vecWeapon.push_back(pItem);

		}
		file.Close();
	}

	//防具ショップLoad

	if (file.Open("StoreArmor.sar", "rb"))
	{
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			CItemArmor* pItem = new CItemArmor;

			if (!pItem->Init())
			{
				SAFE_DELETE(pItem);
				return;
			}

			pItem->Load(&file);

			m_vecArmor.push_back(pItem);

		}
		file.Close();
	}

	cout << "ショップリストSave完了" << endl;
	system("pause");
}

void CEditorItem::Delete()
{

	system("cls");
	cout << "=============== FileDelete(現在のItemーの一覧をDELETE) ===============" << endl;

	Safe_Delete_VecList(m_vecWeapon);
	Safe_Delete_VecList(m_vecArmor);


	cout << "Delete Complete" << endl;
	system("pause");

}
