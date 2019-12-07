#pragma once
#include "Character.h"
class CMonster :
	public CCharacter
{
private:
	CMonster();
	CMonster(const CMonster& monster);

public:
	~CMonster();

private:
	friend class CObjectManager;
	friend class CEditorMonster;

private:
	int        m_chaGoldMin;
	int        m_chaGoldMax;
	STAGE_TYPE m_eStageType;

public:
	void SetGold(int chaMin, int chaMax) 
	{
		m_chaGoldMin = chaMin;
		m_chaGoldMax = chaMax;
	}

	void SetStageType(STAGE_TYPE eType) 
	{
		m_eStageType = eType;
	}

public:
	//メンバー関数後ろのconst->この関数内でメンバー変数の値を変更不能にする。

	int GetDropGold() const 
	{
		return rand() % (m_chaGoldMax - m_chaGoldMin + 1) + m_chaGoldMax;

	}

	STAGE_TYPE GetStageType() const 
	{
		return m_eStageType;
	}


public:
	virtual bool Init();
	virtual void Render();
	virtual CMonster* Clone();
	virtual void Save(class CFileStream* pFile);
	virtual void Load(class CFileStream* pFile);
};

