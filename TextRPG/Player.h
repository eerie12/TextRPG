#pragma once
#include "Character.h"
class CPlayer :
	public CCharacter
{
private:


	enum EQUIP
	{
		EQUIP_WEAPON,
		EQUIP_ARMOR,
		EQUIP_END,
	};

private:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

private:
	friend class CObjectManager;

private:
	JOB    m_eJob;
	string m_strJobName;
	int    m_iGold;
	//��������Ă���Item�̏Z���������Ă���B
	class CItem* m_pEquip[EQUIP_END];

public:
	void AddGold(int iGold);
	void DropGold();

public:
	JOB GetJob() const 
	{
		return m_eJob;
	}

	int GetGold() const 
	{
		return m_iGold;

	}

	class CItem* GetEquip(EQUIP eq) const 
	{
		return m_pEquip[eq];

	}
	//Character�����overriding
	virtual int GetDamage();

	virtual int GetAMR();

public:
	class CItem* Equip(class CItem* pItem);


public:
	virtual bool Init();
	virtual void Render();
	virtual CPlayer* Clone();
};

