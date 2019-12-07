#include "StageEasy.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"


CStageEasy::CStageEasy()
{
}


CStageEasy::~CStageEasy()
{
}

bool CStageEasy::Init()
{
	return true;
}

void CStageEasy::Run()
{
	//Player�𓾂�
	CPlayer* pPlayer = (CPlayer*)GET_SINGLE(CObjectManager)->FindObject("Player");

	//�����X�^�[���R�s�[
	CMonster* pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_EASY);

	while (true) 
	{
		system("cls");
		OutputStageName("Easy");

		pPlayer->Render();

		cout << endl;

		pMonster->Render();

		cout << endl;

		switch (OutputMenu()) 
		{
		case MENU_ATTACK:
			switch(BattleAttack(pPlayer,pMonster))
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

				//��������������Atrue��Ԋ�
				if(pPlayer->CheckLevelUp())
				{
					pPlayer->LevelUp();

					//���ۂ̔\�͒l�㏸
					pPlayer->AddLevelUpStatus(GET_SINGLE(CCore)->GetLevelUpInfo(pPlayer->GetJob()));

					cout << "LevelUp" << endl;
				}
				
				//�����X�^�[���������A�ĂуR�s�[����������B
				SAFE_DELETE(pMonster);
				pMonster = (CMonster*)GET_SINGLE(CObjectManager)->CloneObject(ST_EASY);
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
