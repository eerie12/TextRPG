#include "Character.h"
#include "FileStream.h"



CCharacter::CCharacter()
{
}

//objのコピーコンストラクタ先に呼ぶ->objの値をコピー
//chracterの値をコピー
CCharacter::CCharacter(const CCharacter & character):
	CObj(character)
{
	m_tInfo = character.m_tInfo;
}


CCharacter::~CCharacter()
{
}

void CCharacter::SetCharacterInfo(int chaAtMin, int chaAtMax, int chaArMin,
	int chaArMax, int chaHP, int chaMP, int chaLevel, int chaexp)
{
	m_tInfo.chaAttackMin = chaAtMin;
	m_tInfo.chaAttackMax = chaAtMax;
	m_tInfo.chaArmorMin  = chaArMin;
	m_tInfo.chaArmorMax  = chaArMax;
	m_tInfo.chaHP        = chaHP;
	m_tInfo.chaHPMax     = chaHP;
	m_tInfo.chaMP        = chaMP;
	m_tInfo.chaMPMax     = chaMP;
	m_tInfo.chaLevel     = chaLevel;
	m_tInfo.chaExp       = chaexp;

}

bool CCharacter::Damage(int chaDamage)
{
	m_tInfo.chaHP -= chaDamage;

	
	return m_tInfo.chaHP <= 0;
}

bool CCharacter::AddExp(int chaExp)
{
	m_tInfo.chaExp += chaExp;

	//false returnの場合 レベルアップではない。
	return false;
}

bool CCharacter::CheckLevelUp()
{
	if (g_chaLvUpTable[m_tInfo.chaLevel - 1] <= m_tInfo.chaExp)
		return true;

	return false;
}

void CCharacter::DropExp()
{
	m_tInfo.chaExp *= (int)0.9f;
}

void CCharacter::FULLPOINT()
{
	m_tInfo.chaHP = m_tInfo.chaHPMax;
	m_tInfo.chaMP = m_tInfo.chaMPMax;

}

void CCharacter::LevelUp()
{
	m_tInfo.chaExp -= g_chaLvUpTable[m_tInfo.chaLevel - 1];
	++m_tInfo.chaLevel;
}

void CCharacter::AddLevelUpStatus(const LEVELUPINFO & tInfo)
{
	m_tInfo.chaAttackMin += tInfo.chaAttackMin;
	m_tInfo.chaAttackMax += tInfo.chaAttackMax;
	m_tInfo.chaArmorMin += tInfo.chaArmorMin;
	m_tInfo.chaArmorMax += tInfo.chaArmorMax;
	m_tInfo.chaHPMax += tInfo.chaHP;
	m_tInfo.chaHP = m_tInfo.chaHPMax;
	m_tInfo.chaMPMax += tInfo.chaMP;
	m_tInfo.chaMP = m_tInfo.chaMPMax;

}





bool CCharacter::Init()
{
	return true;
}

void CCharacter::Render()
{
}

void CCharacter::Save(CFileStream * pFile)
{
	//objのpFileを持ってくる。
	CObj::Save(pFile);

	pFile->Write(&m_tInfo, sizeof(m_tInfo));
}

void CCharacter::Load(CFileStream * pFile)
{
	//ObjのpFileを持ってくる。
	CObj::Load(pFile);

	pFile->Read(&m_tInfo, sizeof(m_tInfo));
}
