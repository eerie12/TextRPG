#pragma once
#include "Item.h"
#include "FileStream.h"
class CItemWeapon :
	public CItem
{
protected:
	CItemWeapon();
	CItemWeapon(const CItemWeapon& item);
	virtual ~CItemWeapon();

private:
	friend class CStore;
	friend class CStoreWeapon;
	friend class CEditorItem;

private:
	int   m_iAttackMin;
	int   m_iAttackMax;
	float m_fCritical;

public:
	int GetAttackMin() const 
	{
		return m_iAttackMin;
	}
	int GetAttackMax() const 
	{
		return m_iAttackMax;
	}
	float GetCritical() const 
	{
		return m_fCritical;

	}

public:
	void SetWeaponInfo(int iMina, int iMaxm, float fCritical);



public:
	virtual bool Init();
	virtual void Render();
	virtual CItemWeapon* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

