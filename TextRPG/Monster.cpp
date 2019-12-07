#include "Monster.h"
#include "FileStream.h"



CMonster::CMonster()
{
	m_eType = OT_MONSTER;
}

CMonster::CMonster(const CMonster & monster) :
	CCharacter(monster)
{
	m_chaGoldMin = monster.m_chaGoldMin;
	m_chaGoldMax = monster.m_chaGoldMax;
	m_eStageType = monster.m_eStageType;
}


CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	return true;
}

void CMonster::Render()
{

	cout << "–¼‘O : " << m_strName;

	switch (m_eStageType) 
	{
	case ST_EASY:
		cout << "\t“ïˆÕ“x : Easy" << endl;
		break;
	case ST_NORMAL:
		cout << "\t“ïˆÕ“x : Normal" << endl;
		break;
	case ST_HARD:
		cout << "\t“ïˆÕ“x : Hard" << endl;
		break;
	}

	cout << "ƒŒƒxƒ‹ : " << m_tInfo.chaLevel << "\tŠl“¾ŒoŒ±’l : " << m_tInfo.chaExp << endl;
	cout << "UŒ‚—Í : " << m_tInfo.chaAttackMin << " ~ " << m_tInfo.chaAttackMax <<
		"\t–hŒä—Í : " << m_tInfo.chaArmorMin << " ~ " << m_tInfo.chaArmorMax << endl;
	cout << "‘Ì—Í : " << m_tInfo.chaHP << "/" << m_tInfo.chaHPMax << "\tMP" <<
		m_tInfo.chaMP << "/" << m_tInfo.chaMPMax << endl;
	cout << "Šl“¾‹àŠz : " << m_chaGoldMin << " ~ " << m_chaGoldMax <<" Gold" << endl/*<<endl*/;
}

CMonster * CMonster::Clone()
{
	return new CMonster(*this);
}

void CMonster::Save(CFileStream * pFile)
{
	//Obj->Character‚ÌpFile‚ðŽ‚Á‚Ä‚­‚éB
	CCharacter::Save(pFile);

	pFile->Write(&m_chaGoldMin, 4);
	pFile->Write(&m_chaGoldMax, 4);
	pFile->Write(&m_eStageType, 4);
}

void CMonster::Load(CFileStream * pFile)
{
	//Obj->Character‚ÌpFile‚ðŽ‚Á‚Ä‚­‚éB
	CCharacter::Load(pFile);

	pFile->Read(&m_chaGoldMin, 4);
	pFile->Read(&m_chaGoldMax, 4);
	pFile->Read(&m_eStageType, 4);
}
