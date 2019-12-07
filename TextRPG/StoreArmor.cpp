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
	//�̔����X�g
	/*
	CItemArmor* pItem = (CItemArmor*)CreateItem("���[�U�[�A�[�}�[", ITEM_ARMOR, 1000, 500, "�Ղ��f�ނō��ꂽ�A�[�}�[");
	pItem->SetArmorInfo(5, 10);

	pItem = (CItemArmor*)CreateItem("�n�[�h���[�U�[�A�[�}�[", ITEM_ARMOR, 3000, 1500, "�S�ō��ꂽ�A�[�}�[");
	pItem->SetArmorInfo(10, 20);

	pItem = (CItemArmor*)CreateItem("�N���X�^���A�[�}�[", ITEM_ARMOR, 25000, 12500, "�N���X�^���ō��ꂽ�A�[�}�[");
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
