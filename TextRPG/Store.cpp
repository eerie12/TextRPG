#include "Store.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"



CStore::CStore()
{

}


CStore::~CStore()
{
	Safe_Delete_VecList(m_vecItem);
}

CItem * CStore::CreateItem(const char* pName, ITEM_TYPE eType, int iPrice, int iSell,const char* pDesc)
{
	CItem* pItem = NULL;

	switch (eType) 
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
		return NULL;

	}

	pItem->SetName(pName);
	pItem->SetItemInfo(eType,iPrice,iSell,pDesc);

	m_vecItem.push_back(pItem);

	return pItem;
}

void CStore::OutputItemList()
{
	for (size_t i = 0; i < m_vecItem.size(); i++) 
	{
		cout << i + 1 << ".";
		m_vecItem[i]->Render();
		cout << endl;

	}
}

void CStore::OutputTag(const char * pStoreName)
{
	cout << "====================" << pStoreName << "====================" << endl;
}

