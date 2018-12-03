#include"DxLib.h"
#include"Enemy.h"
//#include"Player.h"
//#include"EnemyShot.h"
#include<Math.h>

/********************  変数宣言  ****************************/

P_Enemy enemy[50];

A_Enemy attack_enemy[48][NUMSHOT];

//debug用 
	/*現在のミリ秒を取得*/
double dNextTime = GetNowCount();
int x, add;
int NowTime;
int ChangeTime;

int e_count[48] = { 0 };
int move[14] = { 0,1,3,4,4,3,1 ,0,-1,-3,-4,-4,-3,-1 };
//ループ用
static int h,i, j, k;

//角度
int e_deg = 0;
//
int n = 0;

//敵の移動スピード
int speed = 1;

//Enemyの攻撃に移るまでのタイマー
double timer = 12000;

//行動カウント
int cntEnemy = 0;

//プレイヤーの位置情報格納用
int epx;
int epy;

int Enemy_Handle[40];

//初期位置(x座標)
static double first_x[50] = { 590,630,670,710					//3
									   , 550,590,630,670,710,750				//9
								  , 510, 550,590,630,670,710,750,790			//17
							  , 470, 510, 550,590,630,670,710,750,790,830		//27
							  , 470, 510, 550,590,630,670,710,750,790,830		//37
							  , 470, 510, 550,590,630,670,710,750,790,830		//47
							  , 470, 830 };

//初期位置(y座標)
static double first_y[50] = {               80, 80, 80, 80
									  ,110,110,110,110,110,110
								  ,140,140,140,140,140,140,140,140
							  ,170,170,170,170,170,170,170,170,170,170
							  ,200,200,200,200,200,200,200,200,200,200
							  ,230,230,230,230,230,230,230,230,230,230
							  ,80,80 };

static int priority_L[19] = {	//左側の敵攻撃優先度
	18,28,38,10,19,29,39,11,20,30,40,12,21,31,41,13,22,32,42
};

static int priority_R[19] = {	//右側の敵攻撃優先度
	27,37,47,17,26,36,46,16,25,35,45,15,24,34,44,14,23,33,43
};

int Enemy_Init() {

	//画像読み込み
	LoadDivBmpToGraph("Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle, true, false);

	for (i = 0; i < 50; i++) {
		enemy[i].fx = first_x[i];
		enemy[i].fy = first_y[i];
		enemy[i].deg = e_deg;
		enemy[i].x = enemy[i].fx;
		enemy[i].y = enemy[i].fy;
		enemy[i].Move_Flg = false;
		enemy[i].Attack_Move_Flg = false;
		enemy[i].Draw_Flg = true;
		enemy[1].Draw_Flg = false;
		enemy[2].Draw_Flg = false;

		if (i < 4) {
			enemy[i].Type = 0;
			enemy[i].anime = 0;
			enemy[i].nx = 90;
		}
		else if (i < 10) {
			enemy[i].Type = 1;
			enemy[i].anime = 8;
			enemy[i].nx = 120;
		}
		else if (i < 18) {
			enemy[i].Type = 2;
			enemy[i].anime = 16;
			enemy[i].nx = 150;
		}
		else if (i < 28) {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 180;
		}
		else if (i < 38) {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 210;
		}
		else {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 240;
		}
		for (j = 0; j < NUMSHOT; j++) {
			attack_enemy[i][j].timer = 300;
			attack_enemy[i][j].enemyshot = false;
		}
	}

	epx = 300;  //debug
	epy = 600;  //degug

	return 0;
}

int Enemy_Move() {

	//プレイヤーの座標受け取り
	//epx = Player_Pos_Init_x();
	//epy = Player_Pos_Init_y();

	//左右移動
	if ((enemy[49].x > 1080.0 || enemy[48].x < 200.0)) {
		speed *= -1;
	}

	for (i = 0; i < EnemyCount+2; i++) {

		//常に左右移動
		enemy[i].fx += speed;

		//ここで動く敵の順番を選択
		Enemy_Attack_Chose(&i);		

		if (enemy[i].Attack_Move_Flg == false) { //攻撃時じゃないとき左右移動
			enemy[i].x += speed;
		}

		if (enemy[i].Move_Flg == true) {	//攻撃時の移動

			Enemy_Attack_Move(&i);

		}

		if (enemy[i].Attack_Move_Flg == false && enemy[i].y == enemy[i].fy) {
			//一回転
			enemy[i].Move_Flg = false;
			enemy[i].deg += 15;
			if (enemy[i].deg >= 360) {
				enemy[i].deg = 0;
			}
		}
	}
	return 0;
}

/***************************************
  　　　　　敵の攻撃の動き
	   敵の動き出しの処理関数
****************************************/
int Enemy_Attack_Chose(int *num) {

	//敵のモーションタイマー
	timer--;
	if (timer <= 0) {//タイマーがゼロになったら、元に戻す
		timer = 6000;
		cntEnemy++;

		Enemy_Move_Flg(&i);
		
		if (epx > 320) { //プレイヤーが画面の右側にいた場合

			for (j = 0; j < 19; j++) {
				if (enemy[priority_R[j]].Attack_Move_Flg == false && enemy[priority_R[j]].Move_Flg == false && enemy[i].Draw_Flg == true) {	//見たところがfalseだったら
					enemy[priority_R[j]].Attack_Move_Flg = true;		//そこをtrueにして、ループを抜ける
					enemy[priority_R[j]].Move_Flg = true;
					break;
				}
			}
		}
		else {
			for (j = 0; j < 19; j++) {
				if (enemy[priority_L[j]].Attack_Move_Flg == false && enemy[priority_L[j]].Move_Flg == false && enemy[i].Draw_Flg == true) {	//一つOnにして抜ける
					enemy[priority_L[j]].Attack_Move_Flg = true;
					enemy[priority_L[j]].Move_Flg = true;
					break;
				}
			}
		}
	}

	return 0;
}

int Enemy_Attack_Move(int *num) {

	if (EnemyCount > *num) {

		
		//下方向に向かって移動
		enemy[*num].y += 1;	
		
		for (j = 0; j < NUMSHOT; j++) {
			//攻撃のタイマー
			attack_enemy[*num][j].timer--;
			if (attack_enemy[*num][j].timer <= 0) {

				//あとで動き出しのときに設定するように変える
				attack_enemy[*num][j].timer = 40;

				attack_enemy[*num][j].enemyshot = true;

				Enemy_Shot(enemy[*num].x, enemy[*num].y, *num);

			}
		}

		if (enemy[*num].Attack_Move_Flg == true) {
			e_count[*num]++;
			if (e_count[*num] / 20 > 14) {
				e_count[*num] = 0;
			}

			enemy[*num].x += move[e_count[*num] / 20];
		}
		//画面外に行ったら、ぶっ飛ばす
		if (enemy[*num].x < 0 || enemy[*num].x>1280) {
			enemy[*num].x = enemy[*num].fx;
			enemy[*num].y = -40;
			enemy[*num].Attack_Move_Flg = false;
		}
		//画面下に行ったときの処理
		if (enemy[*num].y >= 750) {
			enemy[*num].y = -10;
			enemy[*num].x = enemy[*num].fx;
			enemy[*num].Attack_Move_Flg = false;
		}
	}
	return 0;
}

/**********************************
		敵のショット関数
***********************************/
int Enemy_Shot(int x,int y,int num) {
	for (h = 0; h < EnemyCount; h++) {
		for (k = 0; k < NUMSHOT; k++) {

		}
	}
	return 0;
}

int Enemy_Move_Flg(int *num ) {

	if (enemy[*num].Type == 0 && enemy[*num].Attack_Move_Flg == true && enemy[*num].Move_Flg == true) {
		for (j = *num + 4; j < 10; j++) {
			if (enemy[j].Draw_Flg == true) {
				enemy[j].Attack_Move_Flg == true;
				enemy[j].Move_Flg == true;
				cntEnemy++;
			}
			if (cntEnemy >= 2) {
				cntEnemy = -5;
				break;
			}
		}
	}
	return 0;
}

int Enemy_Draw() {
	//DrawFormatString(0, 0, (255, 255, 255), "%.0d", cntEnemy);

	for (i = 0; i < 48; i++) {

		//DrawFormatString(enemy[i].fx, enemy[i].fy, (255,255,255), "%1.0d", enemy[i].Type);
		e_deg = enemy[i].deg;
		e_deg = 0;
		/*if (e_deg % 360 == 0 || e_deg == 0) {
			if (enemy[i].Type == 0)enemy[i].anime = 0;
			if (enemy[i].Type == 1)enemy[i].anime = 6;
			if (enemy[i].Type == 2)enemy[i].anime = 14;
			if (enemy[i].Type == 3)enemy[i].anime = 22;
		}
		if (e_deg % 360 == 15) {
			if (enemy[i].Type == 0)enemy[i].anime = 1;
			if (enemy[i].Type == 1)enemy[i].anime = 7;
			if (enemy[i].Type == 2)enemy[i].anime = 15;
			if (enemy[i].Type == 3)enemy[i].anime = 23;
		}
		if (e_deg % 360 == 30) {
			if (enemy[i].Type == 0)enemy[i].anime = 2;
			if (enemy[i].Type == 1)enemy[i].anime = 8;
			if (enemy[i].Type == 2)enemy[i].anime = 16;
			if (enemy[i].Type == 3)enemy[i].anime = 24;
		}
		if (e_deg % 360 == 45) {
			if (enemy[i].Type == 0)enemy[i].anime = 3;
			if (enemy[i].Type == 1)enemy[i].anime = 9;
			if (enemy[i].Type == 2)enemy[i].anime = 17;
			if (enemy[i].Type == 3)enemy[i].anime = 25;
		}if (e_deg % 360 == 60) {
			if (enemy[i].Type == 0)enemy[i].anime = 4;
			if (enemy[i].Type == 1)enemy[i].anime = 10;
			if (enemy[i].Type == 2)enemy[i].anime = 18;
			if (enemy[i].Type == 3)enemy[i].anime = 26;
		}if (e_deg % 360 == 75) {
			if (enemy[i].Type == 0)enemy[i].anime = 5;
			if (enemy[i].Type == 1)enemy[i].anime = 11;
			if (enemy[i].Type == 2)enemy[i].anime = 19;
			if (enemy[i].Type == 3)enemy[i].anime = 27;
		}
		if (e_deg % 360 == 90) {
			if (enemy[i].Type == 0)enemy[i].anime = 0;
			if (enemy[i].Type == 1)enemy[i].anime = 6;
			if (enemy[i].Type == 2)enemy[i].anime = 14;
			if (enemy[i].Type == 3)enemy[i].anime = 22;
		}
		if (e_deg % 360 == 105) {
			if (enemy[i].Type == 0)enemy[i].anime = 1;
			if (enemy[i].Type == 1)enemy[i].anime = 7;
			if (enemy[i].Type == 2)enemy[i].anime = 15;
			if (enemy[i].Type == 3)enemy[i].anime = 23;
		}
		if (e_deg % 360 == 120) {
			if (enemy[i].Type == 0)enemy[i].anime = 2;
			if (enemy[i].Type == 1)enemy[i].anime = 8;
			if (enemy[i].Type == 2)enemy[i].anime = 16;
			if (enemy[i].Type == 3)enemy[i].anime = 24;
		}
		if (e_deg % 360 == 135) {
			if (enemy[i].Type == 0)enemy[i].anime = 3;
			if (enemy[i].Type == 1)enemy[i].anime = 9;
			if (enemy[i].Type == 2)enemy[i].anime = 17;
			if (enemy[i].Type == 3)enemy[i].anime = 25;
		}if (e_deg % 360 == 150) {
			if (enemy[i].Type == 0)enemy[i].anime = 4;
			if (enemy[i].Type == 1)enemy[i].anime = 10;
			if (enemy[i].Type == 2)enemy[i].anime = 18;
			if (enemy[i].Type == 3)enemy[i].anime = 26;
		}if (e_deg % 360 == 165) {
			if (enemy[i].Type == 0)enemy[i].anime = 5;
			if (enemy[i].Type == 1)enemy[i].anime = 11;
			if (enemy[i].Type == 2)enemy[i].anime = 19;
			if (enemy[i].Type == 3)enemy[i].anime = 27;
		}if (e_deg % 360 == 180) {
			if (enemy[i].Type == 0)enemy[i].anime = 0;
			if (enemy[i].Type == 1)enemy[i].anime = 6;
			if (enemy[i].Type == 2)enemy[i].anime = 14;
			if (enemy[i].Type == 3)enemy[i].anime = 22;
		}
		if (e_deg % 360 == 195) {
			if (enemy[i].Type == 0)enemy[i].anime = 1;
			if (enemy[i].Type == 1)enemy[i].anime = 7;
			if (enemy[i].Type == 2)enemy[i].anime = 15;
			if (enemy[i].Type == 3)enemy[i].anime = 23;
		}
		if (e_deg % 360 == 210) {
			if (enemy[i].Type == 0)enemy[i].anime = 2;
			if (enemy[i].Type == 1)enemy[i].anime = 8;
			if (enemy[i].Type == 2)enemy[i].anime = 16;
			if (enemy[i].Type == 3)enemy[i].anime = 24;
		}
		if (e_deg % 360 == 225) {
			if (enemy[i].Type == 0)enemy[i].anime = 3;
			if (enemy[i].Type == 1)enemy[i].anime = 9;
			if (enemy[i].Type == 2)enemy[i].anime = 17;
			if (enemy[i].Type == 3)enemy[i].anime = 25;
		}if (e_deg % 360 == 240) {
			if (enemy[i].Type == 0)enemy[i].anime = 4;
			if (enemy[i].Type == 1)enemy[i].anime = 10;
			if (enemy[i].Type == 2)enemy[i].anime = 18;
			if (enemy[i].Type == 3)enemy[i].anime = 26;
		}if (e_deg % 360 == 255) {
			if (enemy[i].Type == 0)enemy[i].anime = 5;
			if (enemy[i].Type == 1)enemy[i].anime = 11;
			if (enemy[i].Type == 2)enemy[i].anime = 19;
			if (enemy[i].Type == 3)enemy[i].anime = 27;
		}if (e_deg % 360 == 270) {
			if (enemy[i].Type == 0)enemy[i].anime = 0;
			if (enemy[i].Type == 1)enemy[i].anime = 6;
			if (enemy[i].Type == 2)enemy[i].anime = 14;
			if (enemy[i].Type == 3)enemy[i].anime = 22;
		}
		if (e_deg % 360 == 285) {
			if (enemy[i].Type == 0)enemy[i].anime = 1;
			if (enemy[i].Type == 1)enemy[i].anime = 7;
			if (enemy[i].Type == 2)enemy[i].anime = 15;
			if (enemy[i].Type == 3)enemy[i].anime = 23;
		}
		if (e_deg % 360 == 300) {
			if (enemy[i].Type == 0)enemy[i].anime = 2;
			if (enemy[i].Type == 1)enemy[i].anime = 8;
			if (enemy[i].Type == 2)enemy[i].anime = 16;
			if (enemy[i].Type == 3)enemy[i].anime = 24;
		}
		if (e_deg % 360 == 315) {
			if (enemy[i].Type == 0)enemy[i].anime = 3;
			if (enemy[i].Type == 1)enemy[i].anime = 9;
			if (enemy[i].Type == 2)enemy[i].anime = 17;
			if (enemy[i].Type == 3)enemy[i].anime = 25;
		}if (e_deg % 360 == 330) {
			if (enemy[i].Type == 0)enemy[i].anime = 4;
			if (enemy[i].Type == 1)enemy[i].anime = 10;
			if (enemy[i].Type == 2)enemy[i].anime = 18;
			if (enemy[i].Type == 3)enemy[i].anime = 26;
		}if (e_deg % 360 == 345) {
			if (enemy[i].Type == 0)enemy[i].anime = 5;
			if (enemy[i].Type == 1)enemy[i].anime = 11;
			if (enemy[i].Type == 2)enemy[i].anime = 19;
			if (enemy[i].Type == 3)enemy[i].anime = 27;
		}
		*/
		if (enemy[i].Draw_Flg == true) {
			//if (e_deg >= 0 && e_deg < 90) {
			DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime], true, 0, 0);
			//}
			if (e_deg >= 90 && e_deg < 180) {
			}
		}
	}

	return 0;
}

int Enemy_Pos_Init_x() {
	return enemy[i].x;
}

int Enemy_Pos_Init_y() {
	return enemy[i].y;
}

int Enemy_End() {
	return 0;
}