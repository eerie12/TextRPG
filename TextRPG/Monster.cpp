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

	cout << "���O : " << m_strName;

	switch (m_eStageType) 
	{
	case ST_EASY:
		cout << "\t��Փx : Easy" << endl;
		break;
	case ST_NORMAL:
		cout << "\t��Փx : Normal" << endl;
		break;
	case ST_HARD:
		cout << "\t��Փx : Hard" << endl;
		break;
	}

	cout << "���x�� : " << m_tInfo.chaLevel << "\t�l���o���l : " << m_tInfo.chaExp << endl;
	cout << "�U���� : " << m_tInfo.chaAttackMin << " ~ " << m_tInfo.chaAttackMax <<
		"\t�h��� : " << m_tInfo.chaArmorMin << " ~ " << m_tInfo.chaArmorMax << endl;
	cout << "�̗� : " << m_tInfo.chaHP << "/" << m_tInfo.chaHPMax << "\tMP" <<
		m_tInfo.chaMP << "/" << m_tInfo.chaMPMax << endl;
	cout << "�l�����z : " << m_chaGoldMin << " ~ " << m_chaGoldMax <<" Gold" << endl/*<<endl*/;
}

CMonster * CMonster::Clone()
{
	return new CMonster(*this);
}

void CMonster::Save(CFileStream * pFile)
{
	//Obj->Character��pFile�������Ă���B
	CCharacter::Save(pFile);

	pFile->Write(&m_chaGoldMin, 4);
	pFile->Write(&m_chaGoldMax, 4);
	pFile->Write(&m_eStageType, 4);
}

void CMonster::Load(CFileStream * pFile)
{
	//Obj->Character��pFile�������Ă���B
	CCharacter::Load(pFile);

	pFile->Read(&m_chaGoldMin, 4);
	pFile->Read(&m_chaGoldMax, 4);
	pFile->Read(&m_eStageType, 4);
}
