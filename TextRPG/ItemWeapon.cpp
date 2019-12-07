#include "ItemWeapon.h"



CItemWeapon::CItemWeapon()
{
}

CItemWeapon::CItemWeapon(const CItemWeapon & item) :
	CItem(item)
{
	m_iAttackMin = item.m_iAttackMin;
	m_iAttackMax = item.m_iAttackMax;
	m_fCritical = item.m_fCritical;
}


CItemWeapon::~CItemWeapon()
{
}







void CItemWeapon::SetWeaponInfo(int iMin, int iMax, float fCritical)
{
	m_iAttackMin = iMin;
	m_iAttackMax = iMax;
	m_fCritical = fCritical;
}

bool CItemWeapon::Init()
{
	return true;
}

void CItemWeapon::Render()
{
	cout << "–¼‘O : " << m_strName << "\tŽí—Þ : " << m_tInfo.strTypeName << endl;
	cout << "UŒ‚—Í : " << m_iAttackMin << " ~ " << m_iAttackMax << "\tCritical : " << m_fCritical <<endl;
	cout << "Price : " << m_tInfo.iPrice << "\tSell : " << m_tInfo.iSell << endl;
	cout << "à–¾ : " << m_tInfo.strDesc << endl;

}

CItemWeapon * CItemWeapon::Clone()
{
	return new CItemWeapon(*this);
}

void CItemWeapon::Save(CFileStream * pFile)
{
	CItem::Save(pFile);

	pFile->Write(&m_iAttackMin, 4);
	pFile->Write(&m_iAttackMax, 4);
	pFile->Write(&m_fCritical, 4);
}

void CItemWeapon::Load(CFileStream * pFile)
{
	CItem::Load(pFile);

	pFile->Read(&m_iAttackMin, 4);
	pFile->Read(&m_iAttackMax, 4);
	pFile->Read(&m_fCritical, 4);
}
