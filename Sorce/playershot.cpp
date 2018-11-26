#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int Player_Shot_Flg = 0;		//プレイヤーが球を打つ時のフラグ
int Player_Shotcnt_y;		//弾を動かす
int Handle;				// データハンドル格納用変数
int ex, ey;
int Px, Py;
int score = 0;
S_PShot pbullet;
int Player_Hit_Flg;	//プレイヤーの弾がplayerに当たった時のFlg

/****初期化****/

int Playershot_Init(){

	Handle = LoadGraph("Image/Galaxian_OBJ_bullet.png"); // 画像をロード
	ex = Enemy_Pos_Init_x();
	ey = Enemy_Pos_Init_y();
	return 0;
}

/****計算****/
int PlayerShot_Dpct(){

		if (Player_Shot_Flg == 1) {
			pbullet.x = Player_Pos_Init_x();
			pbullet.y = Player_Pos_Init_y();
			Player_Shot_Flg = 2;
			//pbullet.y -= 5;
		}

		if (Player_Shot_Flg == 2) {
			pbullet.y -= 5;
			if (pbullet.y <= 0) {
				Player_Shot_Flg = 0;
			}
		}

	/*
	pbullet.x = Player_Pos_Init_x();
	pbullet.y = Player_Pos_Init_y();

	Player_Shot_Flg = Player_Dpct();

	if (Player_Shot_Flg == true) {
 		
	    pbullet.y -= 100;

		if (pbullet.x == ex && pbullet.y == ey) {
			Player_Hit();
			Player_Score();
			Player_Shot_Flg = false;
		}

		if (pbullet.y <= 0) {
			Player_Shot_Flg = false;
		}
	}
	return Player_Shot_Flg;
	*/
	return Player_Shot_Flg;
}

int Player_Hit() {
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
	if (Player_Shot_Flg != 0) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);

		DrawCircle(pbullet.x, pbullet.y, 5, GetColor(255, 255, 255), 10, 10);
	}

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
