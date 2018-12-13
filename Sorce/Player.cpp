#include"Dxlib.h"
#include"Player.h"
#include"keyboard.h"
#include"Enemy.h"
#include"PlayerShot.h"
#include"Sound.h"

//プレイヤー
S_Player Player;

//残機
int remain = 3;

//bool Draw_Flg = true;

//攻撃に関するもの
bool PlayerShot_Flg = 0;   //発射フラグ

//画像に関するもの
//int None_Num = 0;				//画像のスタンバイ状態
int Gyallaly[8];				//プレイヤーの画像の変数
int i;							//画像表示用
float j;
int Player_Image[35] = { 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7 }; //画像の順番(アニメーション)
int Player_Cnt;					//画像表示用カウント
int OnActive = true;			//Playerが生きている状態

int Player_Init() {

	//プレイヤーの位置
	Player.x = 300;
	Player.y = 600;

	//画像
	Gyallaly[8] = { 0 };
	LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);
	i = 0;
	Player_Cnt = 0;
	//Player_Image[10] = {4,5,6,7};
	//None_Num = 0;

	return 0;
}

int Player_Dpct() {
	//キー入力

	PlayerShot_Flg = PlayerShot_Dpct();

	if (OnActive == true) {											//生きていなければ動けない
		//←
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 3;
		}

		//→
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 3;
		}
	}

	if (OnActive == true){											//playerが生きていなければ撃てない
		if (PlayerShot_Flg == 0) {
			i = 0;
			//弾を撃つ
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
				//PlayerShot_Flg = 1;
				SetPlayer_Shot_Flg(1);
				SetGax_Sound(8);									//発射音を鳴らす
				i = 1;
			}
		}
    }

	if (Player.x <= 200) {
		Player.x = 200;
	}

	if (Player.x >= 1000) {
		Player.x = 1000;
	}
	if (OnActive == true) {
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {			//エンターキーを押したら爆発をする
			//Player_Remain();
			OnActive = false;								//playerが死んだとき
			SetGax_Sound(7);								//爆発音
		}
	}

	return PlayerShot_Flg;
}

int Player_Remain() {		//残機の処理

	if (Enemy_Hit() == true) {

		//Draw_Flg = false;
		if (remain > 0) {
			remain = remain - 1;
		}
		else {
			Player_End();
		}
	}

	return 0;//Player_Draw;
}

int Player_Draw() {

	if (OnActive == true) {													//生きている時だけ表示

		DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true); //画像の拡大表示

	}

	if (OnActive == false) {												//破壊された時のアニメーション

		Player_Cnt++;

		switch (Player_Image[Player_Cnt]) {
		case 4:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[4], true);
			break;

		case 5:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[5], true);
			break;

		case 6:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[6], true);
			break;

		case 7:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[7], true);
			break;

		case 8:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[2], true);
			break;

		case 9:
			//Draw_Flg = true;
			//Player.x = 300;
			//Player_Cnt = 0;
			break;

		}
		if (Player_Cnt > 200) {		//もしカウントが200を
			Player.x = 600;			//プレイヤーの復活場所をx座標の300にする。
			Player_Cnt = 0;			//カウントを0にする
			OnActive = true;		//playerが復活した時
		}
	}
	return PlayerShot_Flg;
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
	//remain = 0;
	return 0;
}
