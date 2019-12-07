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

	cout << "1. 攻撃" << endl;
	cout << "2. 戻る" << endl;
	cout << endl;
	cout << "3. メニューを選択してください。: ";	
	int iMenu = Input<int >();
	cout << endl;

	if (iMenu <= MENU_NONE || iMenu > MENU_BACK)
		return MENU_NONE;

	return iMenu;
}

//BATTLE_FLAG enumはCStage class内のenum
//CStage::をもう一度使う。
CStage::BATTLE_FLAG CStage::BattleAttack(CPlayer * pPlayer, CMonster * pMonster)
{
	//Playerの(装備の追加DMGをoverrideされた)DMGを求む。
	int iDamage = pPlayer->GetDamage() - pMonster ->GetAMR();
	iDamage = iDamage < 1 ? 1 : iDamage;

	cout << pPlayer->GetName() << "が" << pMonster->GetName()<< "に" << iDamage << "ダメージを与えました。"<< endl;

	if (pMonster->Damage(iDamage)) 
		return BF_MONSTER_DIE;

	//モンスターの方でPlayerを攻撃
	iDamage = pMonster->GetDamage() - pPlayer->GetAMR();
	iDamage = iDamage < 1 ? 1 : iDamage;
	cout << pMonster->GetName() << "が" << pPlayer->GetName() << "に" << iDamage << "ダメージを与えました。" << endl;

	if (pPlayer->Damage(iDamage))
		return BF_PLAYER_DIE;

	return BF_NONE;
}
