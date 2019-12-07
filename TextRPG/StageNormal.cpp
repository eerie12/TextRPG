#include "StageNormal.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"



CStageNormal::CStageNormal()
{
}


CStageNormal::~CStageNormal()
{
}

bool CStageNormal::Init()
{
	return true;
}

void CStageNormal::Run()
{
	//Playerを得る
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	//モンスターをコピー
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_NORMAL);

	while (true)
	{
		system("cls");
		OutputStageName("Normal");

		pPlayer->Render();

		cout << endl;

		pMonster->Render();

		cout << endl;

		switch (OutputMenu())
		{
		case MENU_ATTACK:
			switch (BattleAttack(pPlayer, pMonster))
			{
			case BF_PLAYER_DIE:
				pPlayer->DropExp();
				pPlayer->DropGold();
				pPlayer->FULLPOINT();
				break;
			case BF_MONSTER_DIE:
				cout << pPlayer->GetName() << "が" << pMonster->GetCharacterInfo().chaExp << "経験値を獲得しました。" << endl;
				int iDropGold;
				iDropGold = pMonster->GetDropGold();
				cout << pPlayer->GetName() << "が" << iDropGold << "Goldを獲得しました。" << endl;


				//条件が満たされたらtrueを返還->レベルアップ
				pPlayer->AddExp(pMonster->GetCharacterInfo().chaExp);
				pPlayer->AddGold(iDropGold);

				if (pPlayer->CheckLevelUp())
				{
					pPlayer->LevelUp();

					//実際の能力値上昇
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "LevelUp" << endl;
				}


				//モンスターを消去し、再びコピーし生成する。
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_NORMAL);
				break;

			}
			break;
		case MENU_BACK:
			//作ったモンスターをもう使用しないため消去
			SAFE_DELETE(pMonster);
			return;
		}

		system("pause");

	}


}
