#include"dxlib.h"
#include"Playershot.h" 
#include"Enemy.h"
#include"Player.h"

int Player_Shot_Flg = false;		//プレイヤーが球を打つ時のフラグ
int Player_Shotcnt_y;		//弾を動かす
int Handle;				// データハンドル格納用変数
int ex, ey;
int Px, Py;
int score = 0;
S_PShot pbullet;
int Player_Hit_Flg;	//プレイヤーの弾がplayerに当たった時のFlg

/****初期化****/

int Playershot_Init()
{
	Handle = LoadGraph("Image/Galaxian_OBJ_bullet.png"); // 画像をロード
	ex = Enemy_Pos_Init_x();
	ey = Enemy_Pos_Init_y();
	return 0;
}

/****計算****/
int Playershot_Dpct()
{

	Px = Player_Pos_Init_x();
	Py = Player_Pos_Init_y();

	pbullet.x = Px;
	pbullet.y = Py;

	Player_Shot_Flg = Player_Dpct();

	if (Player_Shot_Flg == true) {
		player_Shot();
	}
	return 0;
}

int player_Shot() {

	Player_Shot_Flg = false;

	pbullet.y -= 10;

	if (pbullet.x == ex && pbullet.y == ey) {
		player_Hit();
		Player_Score();
		Player_Shot_Flg = false;
	}

	if (pbullet.y <= 0) {
		Player_Shot_Flg = false;
	}
	return Player_Shot_Flg;
}

int player_Hit() {
	//弾が当たったらEnemy渡す
	Player_Hit_Flg = true;

	return Player_Hit_Flg;
}

int Player_Score() {
	/*if () {  //もし緑なら
		score += 10;
	}
	else if(){  //もし紫なら
		score += 30;
	}
	else if() {  //もし赤なら
		score += 60;
	}
	else if () {
		score += 100;
	}*/
	return score;
}

int Playershot_Draw(){
	if (Player_Shot_Flg == true) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);
	}

	DrawFormatString(0, 400, GetColor(255, 255, 255), "pbullet.x座標  %d\npbullet.y座標  %d", pbullet.x, pbullet.y);

	return 0;
}
	/**********************************　終了(一回)　******************************************/
	int PlayerShot_End()
	{
		//No Script
		return 0;
	}
