#include"Dxlib.h"
#include"Player.h"
#include"keyboard.h"
#include"EnemyShot.h"
#include"PlayerShot.h"

	//プレイヤー
	S_Player Player;

	//残機
	int remain = 3;

	//攻撃に関するもの
	bool PlayerShot_Flg = false;   //発射フラグ

	//画像に関するもの
	int None_Num = 0;      //画像のスタンバイ状態
	int Gyallaly[8];   //プレイヤーの画像の変数
	//bool Player_Image; //画像の順番

	int Player_Init() {

		//プレイヤーの位置
		Player.x = 300;
		Player.y = 600;

		//画像
		Gyallaly[8] = {0};
		LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);

		None_Num = 0;
		//Player_Image = 0;

		return 0;
	}

	int Player_Dpct() {
		//キー入力

		PlayerShot_Flg = PlayerShot_Dpct();

		//←
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 1;
		}

		//→
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 1;
		}

		if (PlayerShot_Flg == false) {
		//弾を撃つ
		    if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
			 PlayerShot_Flg = true;
		    }
		}

		if (Player.x <= 200) {
			Player.x = 200;
		}

		if (Player.x >= 1000) {
			Player.x = 1000;
		}

		if (Enemy_Hit() == true) {
			Player_Remain();
		}

		return PlayerShot_Flg;
	}

	int Player_Remain() {		//残機の処理


	return 0;
	}

	int Player_Draw() {
		
		DrawGraph(Player.x , Player.y , Gyallaly[None_Num], true);
		DrawFormatString(0, 300, GetColor(255, 255, 255), "x座標  %d\ny座標  %d", Player.x , Player.y );

		/*if (PlayerShot_Flg == true)
		{
			Player_Image = 1;
		}

		if (PlayerShot_Flg == false)
		{
			Player_Image = 0;
		}

		if (Enemy_Hit() == true) {
			Player_Image = count_x / 8 % 4;

			if (remain > 0) {
				remain = remain - 1;
			}
			else {
				Player_End();
			}
		}*/
		return 0;
	}

	int Player_Pos_Init_x() 
	{
		return Player.x;
	}

	int Player_Pos_Init_y() 
	{
		return Player.y;
	}

	int Player_End() 
	{
		return 0;
	}
