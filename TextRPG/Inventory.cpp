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
		cout << "装備するItemを選択してください。" << endl;
		int iItem = Input<int>();

		if (iItem<1 || iItem > m_vecItem.size() + 1)
			continue;
		else if (iItem == m_vecItem.size() + 1)
			return;

		//iItemは1から選択される->1をマイナスしたら、該当するItemのIndexになる。
		CItem* pEquip = pPlayer->Equip(m_vecItem[iItem - 1]);
			
		//Itemを装備している場合
		if (pEquip) 
		{
			//選択したItemに交代
			m_vecItem[iItem - 1] = pEquip;
		}
		else 
		{
			//装備しているItemがない場合、該当するアイテム枠を消去
			//begin + Indexをして装備したItemのiteratorを呼ぶ。
			vector<CItem*>::iterator iter = m_vecItem.begin() + (iItem - 1);

			m_vecItem.erase(iter);

		}

		
	}	
}
