#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int a;
int atari = 0;
int Player_Shot_Flg = 0;		//プレイヤーが球を打つ時のフラグ
int Player_Shotcnt_y;		//弾を動かす
int ex[EnemyCount];
int ey[EnemyCount];
bool e_draw[EnemyCount];
int Px, Py;
int score = 0;
S_PShot pbullet;
bool Player_Hit_Flg[EnemyCount] = { false };	//プレイヤーの弾がenemyに当たった時のFlg
int Player_Shot_Gyallaly[2];		// 画像格納変数
int Player_None_Num;			// 画像のスタンバイ状態(静止状態)

								/****初期化****/

int Playershot_Init() {

	Player_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Player_Shot_Gyallaly); // 画像をロード
	Player_None_Num = 0;        //スタンバイ状態の向いてる方向を正面へするための画像番号1
	return 0;
}

/****計算****/
int PlayerShot_Dpct() {
	for (a = 0;a < EnemyCount;a++) {
		ex[a] = Enemy_Pos_Init_x(a);
		ey[a] = Enemy_Pos_Init_y(a);
		e_draw[a] = Enemy_State_Init(a);
	}
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
	for (a = 0;a < EnemyCount;a++) {
		if (ex[a] - 25 <= pbullet.x - 10 && pbullet.x + 10 <= ex[a] + 25 &&
			pbullet.y == ey[a] + 25 && e_draw[a] == true) {
			Player_Shot_Flg = false;
			Player_HIT(a);
		}
	}

	return Player_Shot_Flg;
}

int Player_HIT(int num) {

	Player_Hit_Flg[num] = true;

	return Player_Hit_Flg[num];
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

	return 0;
}


void SetPlayer_Shot_Flg(int flag) {
	Player_Shot_Flg = flag;
}

int PlayerShot_Pos_Init_x() {

	return pbullet.x;
}

int PlayerShot_Pos_Init_y() {

	return pbullet.y;
}

/**********************************　終了(一回)　******************************************/
int PlayerShot_End()
{
	//No Script
	return 0;
}
