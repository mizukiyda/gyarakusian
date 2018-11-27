#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int atari = 0;
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
		//フラグが2になったら弾を上に撃つ
		if (Player_Shot_Flg == 2) {
			pbullet.y -= 5;
			//弾の座標が0まで行ったらふらぐを0にして消す
			
		}
		if (pbullet.y <= 0) {
			Player_Shot_Flg = 0;
		}

		if (300 <= pbullet.x && pbullet.x <= 400 && 
			pbullet.y >=300 && pbullet.y <= 400) {
			Player_Hit();
			Player_Score();
			Player_Shot_Flg = false;
			

		}

	

	return Player_Shot_Flg;
}

int Player_Hit() {
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

int Playershot_Draw(){

	if (atari == 1) {


		DrawFormatString(300, 400, GetColor(255, 255, 255), "当たり");
		if (Player_Shot_Flg == true) {
			atari = 0;
	}
	}
	
	if (Player_Shot_Flg != 0) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);

		DrawCircle(pbullet.x, pbullet.y, 5, GetColor(255, 255, 255), 10, 10);
	}
	DrawBox(300, 300, 400, 400, GetColor(255,255,255), false);
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
