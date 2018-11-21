#include "DxLib.h"
//#include "Init_Mgr.h"
//#include "Dpct_Mgr.h"
//#include "Drow_Mgr.h"
//#include "End_Mgr.h"
#include "keyboard.h"
#include "Scene_Mgr.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("ギャラクシアン");
	SetWindowSize(1280, 720);
	SetGraphMode(1280,720,32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	//初期化管理関数の呼び出し
	Scene_Mgr_Init();
	//Init_Mgr();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		//ここに処理を追加
		Keyboard_Update();

		Scene_Mgr_Dpct();
		//Dpct_Mgr();		//計算処理
		Scene_Mgr_Draw();
		//Drow_Mgr();		//描写処理





	}
	Scene_Mgr_End();
	//End_Mgr();			//終了処理

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}
