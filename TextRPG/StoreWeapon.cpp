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
	//�̔����X�g
	/*
	CItemWeapon* pItem = (CItemWeapon*)CreateItem("�ؓ�", ITEM_WEAPON, 1000, 500, "�؂ō��ꂽ�ؓ�");
	pItem->SetWeaponInfo(5, 10, 10.f);

	pItem = (CItemWeapon*)CreateItem("�S�̌�", ITEM_WEAPON, 3000, 1500, "�S�ō��ꂽ���͂Ȍ�");
	pItem->SetWeaponInfo(20, 30, 20.f);

	pItem = (CItemWeapon*)CreateItem("�呾��", ITEM_WEAPON, 25000, 12500, "�s���呾���A���̎a���̈З͓͂S�̌�������B");
	pItem->SetWeaponInfo(70, 100, 35.f);
	*/
	CFileStream file("StoreWeapon.swp", "rb");

	if (file.GetOpen())
	{
		//���퐔��Save�B
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
		cout << "�莝���̋��z : " << pPlayer->GetGold() << "Gold" << endl;
		cout << endl;
		cout << "�w�����镐���I��ł��������B: ";
		int iInput = Input<int>();

		if (iInput <1 || iInput > m_vecItem.size() + 1)
			continue;
		else if (iInput == m_vecItem.size() + 1)
			return;

		//Item�𔃂� Inventory��Max�ȏꍇ�s�\
		if (GET_SINGLE(CInventory)->Full()) 
		{
			cout << "Inventory�ɋ󂫂�����܂���B" << endl;
			continue;

		}

		// Gold������Ȃ����`�F�b�N
		else if (pPlayer->GetGold() < m_vecItem[iInput - 1]->GetItemInfo().iPrice)
		{
			cout << "Gold������܂���B" << endl;
			continue;
		}

		CItem* pItem = m_vecItem[iInput - 1]->Clone();

		GET_SINGLE(CInventory)->AddItem(pItem);

		pPlayer->AddGold(-pItem->GetItemInfo().iPrice);
	}
}
