#include "Player.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"



CPlayer::CPlayer()
{
	m_eType = OT_PLAYER;
	//�|�C���^�[�ϐ��̔z���0�ɏ������B
	//EQUIP_END == 2 -> �|�C���^�[�ϐ�(�傫����8byte)��0�ɏ������B
	//�|�C���^�[�ϐ����NULL�|�C���^�[�ɏ������B
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

		//Critical�̊m��
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
	//��������Item��Type�ɂ���đ������镔�����Ⴄ
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
	//Item�𑕔����Ă���ꍇ�A�������Ă���Item��Ԋ҂���B
	if (m_pEquip[eq]) 
	{
		CItem* pEquip = m_pEquip[eq];
		m_pEquip[eq] = pItem;

		//�������Ă���Item��return�B
		return pEquip;

	}

	m_pEquip[eq] = pItem;

	return NULL;
}

bool CPlayer::Init()
{
	system("cls");
	cin.ignore(1024, '\n');
	cout << "���O����͂��Ă������� : " ;
	char strName[32] = {};
	cin.getline(strName, 31);

	SetName(strName);

	int iJob;

	while (true) 
	{
		system("cls");
		cout << "1.��m" << endl;
		cout << "2.�|��" << endl;
		cout << "3.���@�g��" << endl;
		cout << endl;
		cout << "�W���u��I��ł������� : ";
		iJob = Input<int>();
		
		if (iJob < JOB_WARRIOR || iJob >= JOB_END)
			continue;

		break;
	}

	m_eJob = (JOB)iJob;

	switch (m_eJob) 
	{
	case JOB_WARRIOR:
		m_strJobName = "��m";
		SetCharacterInfo(10, 15, 15, 20, 500, 100, 1, 0);
		break;
	case JOB_ARCHER:
		m_strJobName = "�|��";
		SetCharacterInfo(15, 20, 10, 15, 400, 200, 1, 0);
		break;
	case JOB_MAGICIAN:
		m_strJobName = "���@�g��";
		SetCharacterInfo(20, 25, 5, 10, 300, 300, 1, 0);
		break;
	}

	m_iGold = 10000;


	return true;
}

void CPlayer::Render()
{
	cout << "���O : " << m_strName << "\t�W���u : " << m_strJobName << endl;
	cout << "���x�� : " << m_tInfo.chaLevel << "\t�o���l : " << m_tInfo.chaExp << endl;
	cout << "�U���� : ";
	
	if (m_pEquip[EQUIP_WEAPON]) 
	{
		cout << m_tInfo.chaAttackMin << " + " << ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMin() << " ~ " <<
			    m_tInfo.chaAttackMax << " + " << ((CItemWeapon*)m_pEquip[EQUIP_WEAPON])->GetAttackMax();

	}
	else 
	{
		cout << m_tInfo.chaAttackMin << " ~ " << m_tInfo.chaAttackMax;
	}

	cout << "\t�h��� : ";

	if (m_pEquip[EQUIP_ARMOR]) 
	{
		cout << m_tInfo.chaArmorMin << " + " << ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMin() << " ~ " <<
			    m_tInfo.chaArmorMax << " + " << ((CItemArmor*)m_pEquip[EQUIP_ARMOR])->GetArmorMax() << endl;
	}
	else 
	{
		cout << m_tInfo.chaArmorMin << " ~ " << m_tInfo.chaArmorMax << endl;
	}
	
	cout << "�̗� : " << m_tInfo.chaHP << "/" << m_tInfo.chaHPMax << "\tMP : " <<
		m_tInfo.chaMP << "/" << m_tInfo.chaMPMax << endl;
	cout << "�莝���̋��z : " << m_iGold << " Gold" << endl;

	cout << "�������̕��� : ";
	if (m_pEquip[EQUIP_WEAPON])
		cout << m_pEquip[EQUIP_WEAPON]->GetName();
	else
		cout << "�Ȃ�";

	cout << "\t�������̖h�� : ";
	if (m_pEquip[EQUIP_ARMOR])
		cout << m_pEquip[EQUIP_ARMOR]->GetName() << endl;
	else
		cout << "�Ȃ�" << endl;
}

CPlayer * CPlayer::Clone()
{
	//this�͎��g�̃|�C���^�[ -> ���g�̃|�C���^�[���t�Q�Ƃ���ꍇ���g���I�u�W�F�N�g���̂ɂȂ�B
	//->���蓖�Ă�Player�I�u�W�F�N�g�Ɏ������g��n���A->���̎������g���R�s�[���鐶���҂��Ă�
	return new CPlayer(*this);
}


