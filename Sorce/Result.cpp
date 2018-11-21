#include "DxLib.h"
#include "Result.h"
#include "StartMenu.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"

MenuElement_t ResultMenuElement[MENU_ELEMENT_MAX]{
{ 100 , 200 , "Next" },
{ 100 , 300 , "Title" },
{ 100 , 400 , "Exit" }
};

//ここで変数を宣言（C++を使わないのでグローバル変数）


static int SelectNum;


// Init 初期化
int Result_Init() {
	//ここで初期化をする
	//step_count = UI_StepCount();			UIができたらコメントをはずす
	SelectNum = 0;
	return 0;
}

int Result_Dpct() {
	//ここで計算
	//Dqctは毎フレーム呼ばれる
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// 現在の選択項目を一つ上にずらす
	}
	if (SelectNum == -1) {
		SelectNum = MENU_ELEMENT_MAX - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// 現在の選択項目を一つ下にずらす
	}
	for (int i = 0; i < MENU_ELEMENT_MAX; i++) {
		if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
			ResultMenuElement[i].x = 80; // 座標を80にする
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//座標が80になっている項目でスペースキーを押すと
														//その項目の中に入る
				int tmp;
				switch (i) {
				/*case 0:
					// 次のステージへ
					// 次のステージの敵の配列を入れる

					Scene_Mgr_ChangeScene(E_Scene_Game);




					tmp = MAP_GetHandleflag();
						//Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					else {
						MAP_SetHandleflag(tmp + 1);
						Scene_Mgr_ChangeScene(E_Scene_Game);
					}


					break;	*/
				case 1:
					Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					break;
				case 2:
					Scene_Mgr_End();
					DxLib_End(); // DXライブラリ終了処理
					exit(0);
					break;
				}
			}
		}
		else {                     // 今処理しているのが、選択番号以外なら
			ResultMenuElement[i].x = 100;// 座標を100にする
		}
	}

	return 0;
}

int Result_Draw() {
	//ここで描写
	//こっちも毎フレーム呼ばれますが計算とは別に書きます

	DrawFormatString(100, 100, GetColor(255, 255, 255), "りざると");

	for (int i = 0; i<MENU_ELEMENT_MAX; i++) { // メニュー項目を描画
		DrawFormatString(ResultMenuElement[i].x, ResultMenuElement[i].y, GetColor(255, 255, 255), ResultMenuElement[i].name);
	}

	return 0;
}

int Result_End() {
	//ここで終了処理
	return 0;
}