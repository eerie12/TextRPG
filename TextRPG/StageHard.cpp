#include "StageHard.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"


CStageHard::CStageHard()
{
}


CStageHard::~CStageHard()
{
}

bool CStageHard::Init()
{
	return true;
}

void CStageHard::Run()
{
	//Player�𓾂�
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	//�����X�^�[���R�s�[
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_HARD);

	while (true)
	{
		system("cls");
		OutputStageName("Hard");

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
				cout << pPlayer->GetName() << "��" << pMonster->GetCharacterInfo().chaExp << "�o���l���l�����܂����B" << endl;
				int iDropGold;
				iDropGold = pMonster->GetDropGold();
				cout << pPlayer->GetName() << "��" << iDropGold << "Gold���l�����܂����B" << endl;


				//�������������ꂽ��true��Ԋ�->���x���A�b�v
				pPlayer->AddExp(pMonster->GetCharacterInfo().chaExp);
				pPlayer->AddGold(iDropGold);

				if (pPlayer->CheckLevelUp())
				{
					pPlayer->LevelUp();

					//���ۂ̔\�͒l�㏸
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "LevelUp" << endl;
				}


				//�����X�^�[���������A�ĂуR�s�[����������B
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_HARD);
				break;

			}
			break;
		case MENU_BACK:
			//����������X�^�[�������g�p���Ȃ����ߏ���
			SAFE_DELETE(pMonster);
			return;
		}

		system("pause");

	}


}
