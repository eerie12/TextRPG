/*
   TextRPG
   Text�𗘗p�����^�[������RPG�Q�[�����쐬���܂����B
   GameTool���[�h���g���A�����X�^�[�ƃA�C�e����ǉ����邱�Ƃ��\�ɂ��܂����B
   �����X�^�[��Stage�ɓo�^����Ă��郂���X�^�[�̐���0�̏ꍇ�A��{�ݒ�̃����X�^�[���o�^���܂��B
   Main�ɂȂ�Core,Stage,Player,Monster,Store,Inventory,Editor���쐬���܂����B
*/

#include "Core.h"
#include "EditorCore.h"

enum GAME_MODE 
{
	GAME_NONE,
	GAME_INGAME,
	GAME_EDIT,
	GAME_EXIT


};

int main() 
{
	srand((unsigned int)time(0));

	int iGameMode = 0;

	while (true) 
	{
		system("cls");
		cout << "1. GameMode" << endl;
		cout << "2. GameToolMode" << endl;
		cout << endl;
		cout << "3. EXIT" << endl;
		cout << endl;
		cout << "���j���[��I�����Ă��������B: ";
		iGameMode = Input<int>();

		if (iGameMode <= GAME_NONE || iGameMode > GAME_EXIT)
			continue;

		else if (iGameMode == GAME_EXIT)
			return 0;
		break;
	}

	switch (iGameMode) 
	{
	case GAME_INGAME:
		if (!GET_SINGLE(CCore)->Init())
		{
			DESTROY_SINGLE(CCore);
			return 0;
		}

		GET_SINGLE(CCore)->Run();

		DESTROY_SINGLE(CCore);
		break;
	case GAME_EDIT:
		if (!GET_SINGLE(CEditorCore)->Init())
		{
			DESTROY_SINGLE(CEditorCore);
			return 0;
		}

		GET_SINGLE(CEditorCore)->Run();

		DESTROY_SINGLE(CEditorCore);
		break;

	}



	return 0;


}