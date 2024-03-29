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

	cout << "名前 : " << m_strName;

	switch (m_eStageType) 
	{
	case ST_EASY:
		cout << "\t難易度 : Easy" << endl;
		break;
	case ST_NORMAL:
		cout << "\t難易度 : Normal" << endl;
		break;
	case ST_HARD:
		cout << "\t難易度 : Hard" << endl;
		break;
	}

	cout << "レベル : " << m_tInfo.chaLevel << "\t獲得経験値 : " << m_tInfo.chaExp << endl;
	cout << "攻撃力 : " << m_tInfo.chaAttackMin << " ~ " << m_tInfo.chaAttackMax <<
		"\t防御力 : " << m_tInfo.chaArmorMin << " ~ " << m_tInfo.chaArmorMax << endl;
	cout << "体力 : " << m_tInfo.chaHP << "/" << m_tInfo.chaHPMax << "\tMP" <<
		m_tInfo.chaMP << "/" << m_tInfo.chaMPMax << endl;
	cout << "獲得金額 : " << m_chaGoldMin << " ~ " << m_chaGoldMax <<" Gold" << endl/*<<endl*/;
}

CMonster * CMonster::Clone()
{
	return new CMonster(*this);
}

void CMonster::Save(CFileStream * pFile)
{
	//Obj->CharacterのpFileを持ってくる。
	CCharacter::Save(pFile);

	pFile->Write(&m_chaGoldMin, 4);
	pFile->Write(&m_chaGoldMax, 4);
	pFile->Write(&m_eStageType, 4);
}

void CMonster::Load(CFileStream * pFile)
{
	//Obj->CharacterのpFileを持ってくる。
	CCharacter::Load(pFile);

	pFile->Read(&m_chaGoldMin, 4);
	pFile->Read(&m_chaGoldMax, 4);
	pFile->Read(&m_eStageType, 4);
}
