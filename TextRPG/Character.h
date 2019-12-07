#pragma once
#include "Obj.h"
class CCharacter :
	public CObj
{
protected:
	CCharacter();
	CCharacter(const CCharacter& character);
	virtual ~CCharacter() = 0;

protected:
	CHARACTERINFO m_tInfo;

public:
	CHARACTERINFO GetCharacterInfo() const 
	{
		return m_tInfo;
	}

	void SetCharacterInfo(int iAtMin, int iAtMax, int iArMin, int iArMax,
		int iHP, int iMP, int iLevel, int iExp);

	virtual int GetDamage() 
	{
		//MaxDMG - MinDMG + 1 -> MaxDMG - MinDMG
		//-> +MinDMG == MaxDMG - MinDMG +MinDMG
		//== MinDMG ~ MaxDMG
		return rand() % (m_tInfo.chaAttackMax - m_tInfo.chaAttackMin + 1) + m_tInfo.chaAttackMin;
	}

	virtual int GetAMR()
	{
		return rand() % (m_tInfo.chaArmorMax - m_tInfo.chaArmorMin + 1) + m_tInfo.chaArmorMin;

	}

	bool Damage(int iDamage);
	bool AddExp(int iExp);
	bool CheckLevelUp();
	void DropExp();
	void FULLPOINT();
	void LevelUp();
	void AddLevelUpStatus(const LEVELUPINFO& tInfo);

public:
	virtual bool Init();
	virtual void Render();
	virtual CCharacter* Clone() = 0;
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

