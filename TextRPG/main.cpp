/*
   TextRPG
   Textを利用したターン制のRPGゲームを作成しました。
   GameToolモードを使い、モンスターとアイテムを追加することが可能にしました。
   モンスターはStageに登録されているモンスターの数が0の場合、基本設定のモンスターが登録します。
   MainになるCore,Stage,Player,Monster,Store,Inventory,Editorを作成しました。
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
		cout << "メニューを選択してください。: ";
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