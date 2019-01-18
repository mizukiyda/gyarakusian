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
int remain = 3;

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

int Player_Init() {
	remain = Result_Reborn();

	//プレイヤーの初期位置
	Player.x = 300;
	Player.y = 600;

	//画像
	Gyallaly[8] = { 0 };
	LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);				//画像の読み込み
	i = 0;
	Player_Cnt = 0;

	BackGround = LoadGraph("Image/BackGround.png");

	return 0;
}

int Player_Dpct() {
	//キー入力

	PlayerShot_Flg = PlayerShot_Dpct();														//Shotからフラグを受け取る

	if (OnActive == true) {																	//生きていなければ動けない
																							//←
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 2;
		}

		//→
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 2;
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

	if (Player.x <= 300) {											//Playerのxの動きを200で止める
		Player.x = 300;
	}

	if (Player.x >= 900) {											//Playerのxの動きを1000で止める
		Player.x = 900;
	}

	EnemyHit_Flg = EnemyShot_Move();									//enemyからの当たり判定を入れるもの
	if (EnemyHit_Flg == true) {
		Player_Remain();	//Remainへ飛ぶ
		OnActive = false;										//playerが死んだとき
		SetGax_Sound(7);										//爆発音
		Player_Hit();
		HitFlg = true;
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

	DrawExtendGraph(0, 5, 1280, 700, BackGround, true);

	if (OnActive == true) {														//生きている時だけ表示

		DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true);			//画像の拡大表示

	}
	DrawFormatString(0, 100, GetColor(255, 255, 255), "remain:%d", remain);
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
			Player.x = 600;			//プレイヤーの復活場所をx座標の300にする。
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
	//remain = 0;
	return 0;
}
