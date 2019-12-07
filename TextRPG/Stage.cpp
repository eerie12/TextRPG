#include "Stage.h"
#include "Player.h"
#include "Monster.h"



CStage::CStage()
{
}


CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

void CStage::Run()
{
}

void CStage::OutputStageName(const char * pName)
{
	cout << "=====================" << pName << "=====================" << endl;
}

int CStage::OutputMenu()
{

	cout << "1. �U��" << endl;
	cout << "2. �߂�" << endl;
	cout << endl;
	cout << "3. ���j���[��I�����Ă��������B: ";	
	int iMenu = Input<int >();
	cout << endl;

	if (iMenu <= MENU_NONE || iMenu > MENU_BACK)
		return MENU_NONE;

	return iMenu;
}

//BATTLE_FLAG enum��CStage class����enum
//CStage::��������x�g���B
CStage::BATTLE_FLAG CStage::BattleAttack(CPlayer * pPlayer, CMonster * pMonster)
{
	//Player��(�����̒ǉ�DMG��override���ꂽ)DMG�����ށB
	int iDamage = pPlayer->GetDamage() - pMonster ->GetAMR();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pPlayer->GetName() << "��" << pMonster->GetName()<< "��" << iDamage << "�_���[�W��^���܂����B"<< endl;

	if (pMonster->Damage(iDamage)) 
		return BF_MONSTER_DIE;

	//�����X�^�[�̕���Player���U��
	iDamage = pMonster->GetDamage() - pPlayer->GetAMR();
	iDamage = iDamage < 1 ? 1 : iDamage;
	cout << pMonster->GetName() << "��" << pPlayer->GetName() << "��" << iDamage << "�_���[�W��^���܂����B" << endl;

	if (pPlayer->Damage(iDamage))
		return BF_PLAYER_DIE;

	return BF_NONE;
}
