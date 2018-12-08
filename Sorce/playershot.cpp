#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int atari = 0;
int Player_Shot_Flg = 0;		//プレイヤーが球を打つ時のフラグ
int Player_Shotcnt_y;		//弾を動かす
int ex, ey;
int Px, Py;
int score = 0;
S_PShot pbullet;
int Player_Hit_Flg;	//プレイヤーの弾がplayerに当たった時のFlg
int Player_Shot_Gyallaly[2];		// 画像格納変数
int Player_None_Num;			// 画像のスタンバイ状態(静止状態)

								/****初期化****/

int Playershot_Init() {

	Player_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Player_Shot_Gyallaly); // 画像をロード
	Player_None_Num = 0;        //スタンバイ状態の向いてる方向を正面へするための画像番号1
	ex = Enemy_Pos_Init_x();
	ey = Enemy_Pos_Init_y();
	return 0;
}

/****計算****/
int PlayerShot_Dpct() {

	if (Player_Shot_Flg == 1) {
		pbullet.x = Player_Pos_Init_x();
		pbullet.y = Player_Pos_Init_y();
		Player_Shot_Flg = 2;
		//pbullet.y -= 5;
	}
	//フラグが2になったら弾を上に撃つ
	if (Player_Shot_Flg == 2) {
		pbullet.y -= 5;
		//弾の座標が0まで行ったらふらぐを0にして消す

	}
	if (pbullet.y <= 0) {
		Player_Shot_Flg = 0;
	}

	if (300 <= pbullet.x && pbullet.x <= 400 &&
		pbullet.y >= 300 && pbullet.y <= 400) {
		Player_Hit();
		Player_Score();
		Player_Shot_Flg = false;


	}
	return Player_Shot_Flg;
}

int Player_HIT() {
	//弾が当たったらEnemy渡す
	Player_Hit_Flg = true;
	if (Player_Hit_Flg == true) {
		atari = 1;
	}

	return Player_Hit_Flg;
}

int Player_Score() {
	//Enemy_Type 
	/*if (Enemy_Type = 3) {  //もし	黄色なら
	score += 10;
	}
	else if(Enemy_Type = 2){  //もし紫なら
	score += 30;
	}
	else if(Enemy_Type = 1) {  //もし赤なら
	score += 60;
	}
	else if (Enemy_Type = 0) {
	score += 100;
	}*/
	return score;
}

int Playershot_Draw() {

	if (atari == 1) {


		DrawFormatString(300, 400, GetColor(255, 255, 255), "当たり");
		if (Player_Shot_Flg == true) {
			atari = 0;
		}
	}

	if (Player_Shot_Flg != 0) {
		//画像の拡大表示
		DrawRotaGraph(pbullet.x + 3, pbullet.y - 25, 4.0, 0.0, Player_Shot_Gyallaly[Player_None_Num], true);
	}
	DrawBox(300, 300, 400, 400, GetColor(255, 255, 255), false);
	DrawFormatString(0, 400, GetColor(255, 255, 255), "pbullet.x座標  %d\npbullet.y座標  %d", pbullet.x, pbullet.y);

	return 0;
}


void SetPlayer_Shot_Flg(int flag) {
	Player_Shot_Flg = flag;
}

/**********************************　終了(一回)　******************************************/
int PlayerShot_End()
{
	//No Script
	return 0;
}
