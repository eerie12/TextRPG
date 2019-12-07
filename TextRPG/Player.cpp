#include "Player.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"



CPlayer::CPlayer()
{
	m_eType = OT_PLAYER;
	//ポインター変数の配列を0に初期化。
	//EQUIP_END == 2 -> ポインター変数(大きさが8byte)を0に初期化。
	//ポインター変数二つをNULLポインターに初期化。
	memset(m_pEquip, 0, sizeof(CItem*) * EQUIP_END);
}

CPlayer::CPlayer(const CPlayer & player) :
	CCharacter(player)
{
	m_eJob = player.m_eJob;
	m_strJobName = player.m_strJobName;
	m_iGold = player.m_iGold;
	memset(m_pEquip, 0, sizeof(CItem*) * EQUIP_END);
}


CPlayer::~CPlayer()
{
	for (int i = 0; i < EQUIP_END; i++) 
	{
		SAFE_DELETE(m_pEquip[i]);
	}
}



void CPlayer::AddGold(int iGold)
{
	m_iGold += iGold;
}

void CPlayer::DropGold()
{
	m_iGold *= (int)0.9f;
}

int CPlayer::GetDamage()
{
	int iMin = m_tInfo.chaAttackMin;
	int iMax = m_tInfo.chaAttackMax;

	if (m_pEquip[EQUIP_WEAPON])
	{
		iMin += ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMin();
		iMax += ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMax();

		//Criticalの確率
		if (rand() % 9901 / 100.f <= ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetCritical())
		{
			cout << "Critical!" << endl;
			iMin *= 2;
			iMax *= 2;

		}
	}
	
	//MaxDMG - MinDMG + 1 -> MaxDMG - MinDMG
	//-> +MinDMG == MaxDMG - MinDMG +MinDMG
	//== MinDMG ~ MaxDMG
	return rand() % (iMax - iMin + 1) + iMin;
}

int CPlayer::GetAMR()
{
	int iMin = m_tInfo.chaArmorMin;
	int iMax = m_tInfo.chaArmorMax;
	if (m_pEquip[EQUIP_ARMOR])
	{
		iMin = ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMin();
		iMax = ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMax();

	}

	return rand() % (iMax - iMin + 1) + iMin;
}

class CItem* CPlayer::Equip(CItem * pItem)
{
	//装備するItemのTypeによって装備する部分が違う
	EQUIP eq;

	switch (pItem->GetItemInfo().eType) 
	{
	case ITEM_WEAPON:
		eq = EQUIP_WEAPON;
		break;
	case ITEM_ARMOR:
		eq = EQUIP_ARMOR;
		break;

	}
	//Itemを装備している場合、装備していたItemを返還する。
	if (m_pEquip[eq]) 
	{
		CItem* pEquip = m_pEquip[eq];
		m_pEquip[eq] = pItem;

		//装備していたItemをreturn。
		return pEquip;

	}

	m_pEquip[eq] = pItem;

	return NULL;
}

bool CPlayer::Init()
{
	system("cls");
	cin.ignore(1024, '\n');
	cout << "名前を入力してください : " ;
	char strName[32] = {};
	cin.getline(strName, 31);

	SetName(strName);

	int iJob;

	while (true) 
	{
		system("cls");
		cout << "1.戦士" << endl;
		cout << "2.弓兵" << endl;
		cout << "3.魔法使い" << endl;
		cout << endl;
		cout << "ジョブを選んでください : ";
		iJob = Input<int>();
		
		if (iJob < JOB_WARRIOR || iJob >= JOB_END)
			continue;

		break;
	}

	m_eJob = (JOB)iJob;

	switch (m_eJob) 
	{
	case JOB_WARRIOR:
		m_strJobName = "戦士";
		SetCharacterInfo(10, 15, 15, 20, 500, 100, 1, 0);
		break;
	case JOB_ARCHER:
		m_strJobName = "弓兵";
		SetCharacterInfo(15, 20, 10, 15, 400, 200, 1, 0);
		break;
	case JOB_MAGICIAN:
		m_strJobName = "魔法使い";
		SetCharacterInfo(20, 25, 5, 10, 300, 300, 1, 0);
		break;
	}

	m_iGold = 10000;


	return true;
}

void CPlayer::Render()
{
	cout << "名前 : " << m_strName << "\tジョブ : " << m_strJobName << endl;
	cout << "レベル : " << m_tInfo.chaLevel << "\t経験値 : " << m_tInfo.chaExp << endl;
	cout << "攻撃力 : ";
	
	if (m_pEquip[EQUIP_WEAPON]) 
	{
		cout << m_tInfo.chaAttackMin << " + " << ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMin() << " ~ " <<
			    m_tInfo.chaAttackMax << " + " << ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMax();

	}
	else 
	{
		cout << m_tInfo.chaAttackMin << " ~ " << m_tInfo.chaAttackMax;
	}

	cout << "\t防御力 : ";

	if (m_pEquip[EQUIP_ARMOR]) 
	{
		cout << m_tInfo.chaArmorMin << " + " << ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMin() << " ~ " <<
			    m_tInfo.chaArmorMax << " + " << ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMax() << endl;
	}
	else 
	{
		cout << m_tInfo.chaArmorMin << " ~ " << m_tInfo.chaArmorMax << endl;
	}
	
	cout << "体力 : " << m_tInfo.chaHP << "/" << m_tInfo.chaHPMax << "\tMP : " <<
		m_tInfo.chaMP << "/" << m_tInfo.chaMPMax << endl;
	cout << "手持ちの金額 : " << m_iGold << " Gold" << endl;

	cout << "装備中の武器 : ";
	if (m_pEquip[EQUIP_WEAPON])
		cout << m_pEquip[EQUIP_WEAPON]->GetName();
	else
		cout << "なし";

	cout << "\t装備中の防具 : ";
	if (m_pEquip[EQUIP_ARMOR])
		cout << m_pEquip[EQUIP_ARMOR]->GetName() << endl;
	else
		cout << "なし" << endl;
}

CPlayer * CPlayer::Clone()
{
	//thisは自身のポインター -> 自身のポインターを逆参照する場合自身がオブジェクト自体になる。
	//->割り当てるPlayerオブジェクトに自分自身を渡し、->その自分自身をコピーする生成者を呼ぶ
	return new CPlayer(*this);
}


