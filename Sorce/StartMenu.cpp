#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include"Sound.h"

Image_t Image;
int star;

int StartMenu_Init() {

	Image.Start = LoadGraph("Image/PUSH SPACE BUTTON.png");				//画像の習得	
	Image.CREDIT = LoadGraph("Image/CREDIT.png");
	Image.HIGH_SCORE = LoadGraph("Image/HIGH SCORE.png");
	Image.ONE_UP = LoadGraph("Image/1UP.png");
	star = LoadGraph("Image/BackGround.png");

	return 0;
}

int StartMenu_Dpct() {
	//Dqctは毎フレーム呼ばれる

	if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
		Scene_Mgr_ChangeScene(E_Scene_StartMenu2);							//スペースキーを押したら次のシーンへ
		//SetGax_Sound(1);
	}
	return 0;
}

int StartMenu_Draw() {
	//ここで描写

	DrawRotaGraph(600, 370, 3.5, 0, star, TRUE);							//背景を一番最初に呼ぶことで一番後ろに表示される

	DrawGraph(200, 500, Image.Start, TRUE);
	DrawGraph(50, 650, Image.CREDIT, TRUE);
	DrawGraph(350, 0, Image.HIGH_SCORE, TRUE);
	DrawGraph(250, 0, Image.ONE_UP, TRUE);

	return 0;
}

int StartMenu_End() {
	//NoScript
	return 0;
}
