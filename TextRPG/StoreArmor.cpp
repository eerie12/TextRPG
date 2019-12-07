#include "StoreArmor.h"
#include "ItemArmor.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "FileStream.h"



CStoreArmor::CStoreArmor()
{
}


CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
	//販売リスト
	/*
	CItemArmor* pItem = (CItemArmor*)CreateItem("レーザーアーマー", ITEM_ARMOR, 1000, 500, "易い素材で作られたアーマー");
	pItem->SetArmorInfo(5, 10);

	pItem = (CItemArmor*)CreateItem("ハードレーザーアーマー", ITEM_ARMOR, 3000, 1500, "鉄で作られたアーマー");
	pItem->SetArmorInfo(10, 20);

	pItem = (CItemArmor*)CreateItem("クリスタルアーマー", ITEM_ARMOR, 25000, 12500, "クリスタルで作られたアーマー");
	pItem->SetArmorInfo(30, 50);
	*/
	CFileStream file("StoreArmor.sar", "rb");

	if (file.GetOpen())
	{
		size_t iCount = 0;

		file.Read(&iCount, 4);

		for (size_t i = 0; i < iCount; i++)
		{
			CItemArmor* pItem = new CItemArmor;

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

void CStoreArmor::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true)
	{
		system("cls");
		OutputTag("ArmorStore");
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
