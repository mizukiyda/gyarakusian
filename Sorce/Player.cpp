#include "Dxlib.h"
#include "Player.h"
#include "keyboard.h"
#include "Enemy.h"
#include "PlayerShot.h"
#include "Sound.h"
#include "Scene_Mgr.h"
#include"Result.h"

//プレイヤー
S_Player Player;

//残機
int remain = 500;

//bool Draw_Flg = true;
int HitFlg = false;

//攻撃に関するもの
bool PlayerShot_Flg = 0;				//発射フラグ

bool Remain_Flg = false;				//UIにRemain処理を送るフラグ

//攻撃を受けたフラグ
bool EnemyHit_Flg = false;

//画像に関するもの
//int None_Num = 0;						//画像のスタンバイ状態
int Gyallaly[8];						//プレイヤーの画像の変数
int i;									//画像表示用の変数
float j;
int Player_Image[35] = { 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7 }; //画像の順番(アニメーション)
int Player_Cnt;							//画像表示用カウント
int OnActive = true;					//Playerが生きている状態
int BackGround;
int BackGround2;
int starcnt = 0;						//スクロールCnt
int y = 5;
int gy = 750;
int scl_speed = 1;

int Player_Init() {
	remain = Result_Reborn();

	//プレイヤーの初期位置
	Player.x = 350;
	Player.y = 600;

	//画像
	Gyallaly[8] = { 0 };
	LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);				//画像の読み込み
	i = 0;
	Player_Cnt = 0;

	BackGround = LoadGraph("Image/BackGround.png");
	BackGround2 = LoadGraph("Image/BackGround2.png");

	return 0;
}

int Player_Dpct() {

	y += scl_speed;
	gy += scl_speed;

	starcnt = (starcnt + 1) % 120;

	PlayerShot_Flg = PlayerShot_Dpct();														//Shotからフラグを受け取る
	//キー入力
	if (OnActive == true) {																	//生きていなければ動けない
																							//←
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 3;
		}

		//→
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 3;
		}
	}

	if (OnActive == true) {											//playerが生きていなければ撃てない
		if (PlayerShot_Flg == 0) {
			i = 0;													//弾を所持しているplayerの画像
																	//弾を撃つ
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
				SetPlayer_Shot_Flg(1);								//ポインタで返す
				SetGax_Sound(8);									//発射音を鳴らす
				i = 1;												//弾を所持していないplayerの画像
			}
		}
	}

	if (Player.x <= 150) {											//Playerのxの動きを200で止める
		Player.x = 150;
	}

	if (Player.x >= 500) {											//Playerのxの動きを1000で止める
		Player.x = 500;
	}
	EnemyHit_Flg = Enemy_Hit();									//enemyからの当たり判定を入れるもの
	if (OnActive == true) {
		if (EnemyHit_Flg == true) {
			HitFlg = true;
			OnActive = false;
			SetGax_Sound(7);									//playerが死んだとき
			Player_Remain();									//Remainへ飛ぶ
																//爆発音
			Player_Hit();
		}
	}

	return PlayerShot_Flg;
}

int Player_Remain() {		//残機の処理
	if (HitFlg == true) {
		remain--;
		HitFlg = false;
	}

	if (remain < 1) {
		Scene_Mgr_ChangeScene(E_Scene_Result);
	}
	return remain;
}

int Player_Hit() {

	EnemyHit_Flg = false;

	return EnemyHit_Flg;
}

int Player_Draw() {
	
	if (starcnt < 60) {
		DrawExtendGraph(5, y, 1280, gy, BackGround, true);
	}
	else {
		DrawExtendGraph(-10, y, 1280, gy, BackGround, true);
	}

	if (y == 700) {
		y = 5;
		gy = 750;
	}

	if (starcnt < 60) {
		DrawExtendGraph(5, y-700, 1280, gy-750, BackGround2, true);
	}
	else {
		DrawExtendGraph(-10, y-700, 1280, gy-750, BackGround2, true);
	}

	if (y == 700) {
		y = 5;
		gy = 750;
	}

	if (OnActive == true) {														//生きている時だけ表示

		DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true);			//画像の拡大表示

	}
	if (OnActive == false) {													//破壊された時のアニメーション

		Player_Cnt++;

		//↓爆発のアニメーション
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

		}
		if (Player_Cnt > 400) {		//もしカウントが200を
			Player.x = 350;			//プレイヤーの復活場所をx座標の300にする。
			Player_Cnt = 0;			//カウントを0にする
			OnActive = true;		//playerが復活した時
		}
	}
	return PlayerShot_Flg;
}

int Player_Pos_Init_x()				//Playerのｘ座標
{
	return Player.x;
}

int Player_Pos_Init_y()				//Playerのy座標
{
	return Player.y;
}

int Player_End()
{
	return 0;
}
