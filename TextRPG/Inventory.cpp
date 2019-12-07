#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

DEFINITON_SINGLE(CInventory)


CInventory::CInventory() :
	m_iInvenMax(10)
{
}


CInventory::~CInventory()
{
	Safe_Delete_VecList(m_vecItem);
}

bool CInventory::Init()
{
	return true;
}

void CInventory::AddItem(CItem * pItem)
{
	if (m_iInvenMax == m_vecItem.size())
		return;

	m_vecItem.push_back(pItem);
}

void CInventory::Run()
{
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	while (true) 
	{

		system("cls");
		cout << "=============== Inventory ===============" << endl;
		pPlayer->Render();
		cout << endl;
		for (size_t i = 0; i < m_vecItem.size(); i++) 
		{
			cout << i + 1 << ".";
			m_vecItem[i]->Render();
			cout << endl;
		}
		cout << endl;
		cout << m_vecItem.size() + 1 << ". Back" << endl;
		cout << endl;
		cout << "��������Item��I�����Ă��������B" << endl;
		int iItem = Input<int>();

		if (iItem<1 || iItem > m_vecItem.size() + 1)
			continue;
		else if (iItem == m_vecItem.size() + 1)
			return;

		//iItem��1����I�������->1���}�C�i�X������A�Y������Item��Index�ɂȂ�B
		CItem* pEquip = pPlayer->Equip(m_vecItem[iItem - 1]);
			
		//Item�𑕔����Ă���ꍇ
		if (pEquip) 
		{
			//�I������Item�Ɍ��
			m_vecItem[iItem - 1] = pEquip;
		}
		else 
		{
			//�������Ă���Item���Ȃ��ꍇ�A�Y������A�C�e���g������
			//begin + Index�����đ�������Item��iterator���ĂԁB
			vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);

			m_vecItem.erase(iter);

		}

		
	}	
}
