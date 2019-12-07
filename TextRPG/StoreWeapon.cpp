#include "StoreWeapon.h"
#include "ItemWeapon.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "FileStream.h"


CStoreWeapon::CStoreWeapon()
{
}


CStoreWeapon::~CStoreWeapon()
{
}

bool CStoreWeapon::Init()
{
	//販売リスト
	/*
	CItemWeapon* pItem = (CItemWeapon*)CreateItem("木刀", ITEM_WEAPON, 1000, 500, "木で作られた木刀");
	pItem->SetWeaponInfo(5, 10, 10.f);

	pItem = (CItemWeapon*)CreateItem("鉄の剣", ITEM_WEAPON, 3000, 1500, "鉄で作られた強力な剣");
	pItem->SetWeaponInfo(20, 30, 20.f);

	pItem = (CItemWeapon*)CreateItem("大太刀", ITEM_WEAPON, 25000, 12500, "鋭い大太刀、その斬撃の威力は鉄の剣を上回る。");
	pItem->SetWeaponInfo(70, 100, 35.f);
	*/
	CFileStream file("StoreWeapon.swp", "rb");

	if (file.GetOpen())
	{
		//武器数をSave。
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			CItemWeapon* pItem = new CItemWeapon;

			if (!pItem->Init())
			{
				SAFE_DELETE(pItem);
				return false;
			}

			pItem->Load(&file);

			m_vecItem.push_back(pItem);

		}
		file.Close();
	}

	return true;
}

void CStoreWeapon::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true) 
	{
		system("cls");
		OutputTag("WeaponStore");
		OutputItemList();
		cout << m_vecItem.size() + 1 << ". Back" << endl;
		cout << endl;
		cout << "手持ちの金額 : " << pPlayer->GetGold() << "Gold" << endl;
		cout << endl;
		cout << "購入する武器を選んでください。: ";
		int iInput = Input<int>();

		if (iInput <1 || iInput > m_vecItem.size() + 1)
			continue;
		else if (iInput == m_vecItem.size() + 1)
			return;

		//Itemを買う InventoryがMaxな場合不可能
		if (GET_SINGLE(CInventory)->Full()) 
		{
			cout << "Inventoryに空きがありません。" << endl;
			continue;

		}

		// Goldが足りないかチェック
		else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice)
		{
			cout << "Goldが足りません。" << endl;
			continue;
		}

		CItem* pItem = m_vecItem[iInput - 1]->Clone();

		GET_SINGLE(CInventory)->AddItem(pItem);

		pPlayer->AddGold(-pItem->GetItemInfo().iPrice);
	}
}
