#include"DxLib.h"
#include"Enemy.h"
//#include"PlayerShot.h"
#include"Player.h"
#include<Math.h>

/********************  変数宣言  ****************************/

P_Enemy enemy[50];

A_Enemy attack_enemy[48][NUMSHOT];

S_EShot ebullet[EnemyCount][NUMSHOT];

//debug用 
//現在のミリ秒を取得
double dNextTime = GetNowCount();
int x, add;
int NowTime;
int ChangeTime;

int e_count[48] = { 0 };
int move[14] = { 0,1,3,4,4,3,1 ,0,-1,-3,-4,-4,-3,-1 };

//ループ用
static int h,i, j, k;

int copy_i = 0;

//角度
int e_deg = 0;
//
int n = 0;

int e_score=0;

//敵の移動スピード
int speed = 1;

//Enemyの攻撃に移るまでのタイマー
double timer = 12000;

//行動カウント
int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;

//プレイヤーの位置情報格納用
int epx;
int epy;

int pbullet_x;
int pbullet_y;

//画像格納変数
int Enemy_Handle[40];
int Enemy_Shot_Gyallaly[2];

int Enemy_None_Num;

bool Enemy_Hit_Flg;

//初期位置(x座標)
static double first_x[50] = {                 590,630,670,710					//3
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
	LoadDivBmpToGraph("Image/Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle, true, false);

	LoadDivBmpToGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 12, Enemy_Shot_Gyallaly,true,false);
	Enemy_None_Num = 1;


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
	}
	cntEnemy = 0;
	cntRed = 0;

	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {
			attack_enemy[i][j].timer = 300;
			attack_enemy[i][j].enemyshot = false;

			ebullet[i][j].x = 10;
			ebullet[i][j].y = 750;
			ebullet[i][j].Draw_Flg = false;
		}
	}

	for (i = 0; i < 4; i++) {
		if (enemy[i].Draw_Flg == true) {
			cntYellow++;
		}
	}
	Enemy_Hit_Flg = false;

	epx = 500;  //debug
	epy = 600;  //degug
	e_score = 0;

	return 0;
}

int Enemy_Move() {

	//プレイヤーの座標受け取り(真ん中)
	epx = Player_Pos_Init_x() + 19;
	epy = Player_Pos_Init_y() + 18;
	//pbullet_x = PlayerShot_Pos_Init_x() + 19;
	//pbullet_y = PlayerShot_Pos_Init_y() + 18;

	Enemy_control();
	//左右移動
	if ((enemy[49].x > 1080.0 || enemy[48].x < 200.0)) {
		speed *= -1;
	}

	for (i = 0; i < EnemyCount+2; i++) {

		//常に左右移動
		enemy[i].fx += speed;

		//ここで動く敵の順番を選択
		Enemy_Attack_Chose();		

		if (enemy[i].Attack_Move_Flg == false) { //攻撃時じゃないとき左右移動
			enemy[i].x += speed;
		}
	    //攻撃時の移動
		if (enemy[i].Move_Flg == true) {

			//Enemy_deg(&i);

			Enemy_Attack_Move(&i);

		}

		if (enemy[i].y <= 280) {

			Enemy_Shot_Set(&i);

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

//左右移動で、表示上の敵で切り返す処理
int Enemy_control() {

	if (enemy[23].Draw_Flg == false && enemy[33].Draw_Flg == false && enemy[43].Draw_Flg == false) {
		enemy[48].x = enemy[32].fx;
	}
	if (enemy[22].Draw_Flg == false && enemy[32].Draw_Flg == false && enemy[42].Draw_Flg == false) {
		enemy[48].x = enemy[31].fx;
	}
	if (enemy[21].Draw_Flg == false && enemy[31].Draw_Flg == false && enemy[41].Draw_Flg == false) {
		enemy[48].x = enemy[30].fx;
	}
	if (enemy[20].Draw_Flg == false && enemy[30].Draw_Flg == false && enemy[40].Draw_Flg == false) {
		enemy[48].x = enemy[29].fx;
	}
	if (enemy[19].Draw_Flg == false && enemy[29].Draw_Flg == false && enemy[39].Draw_Flg == false) {
		enemy[48].x = enemy[28].fx;
	}
	if (enemy[18].Draw_Flg == false && enemy[28].Draw_Flg == false && enemy[38].Draw_Flg == false) {
		enemy[48].x = enemy[27].fx;
	}


	if (enemy[22].Draw_Flg == false && enemy[32].Draw_Flg == false && enemy[42].Draw_Flg == false) {
		enemy[49].x = enemy[21].fx;
	}
	if (enemy[23].Draw_Flg == false && enemy[33].Draw_Flg == false && enemy[43].Draw_Flg == false) {
		enemy[49].x = enemy[22].fx;
	}
	if (enemy[24].Draw_Flg == false && enemy[34].Draw_Flg == false && enemy[44].Draw_Flg == false) {
		enemy[49].x = enemy[23].fx;
	}
	if (enemy[25].Draw_Flg == false && enemy[35].Draw_Flg == false && enemy[45].Draw_Flg == false) {
		enemy[49].x = enemy[24].fx;
	}
	if (enemy[26].Draw_Flg == false && enemy[36].Draw_Flg == false && enemy[46].Draw_Flg == false) {
		enemy[49].x = enemy[25].fx;
	}
	if (enemy[27].Draw_Flg == false && enemy[37].Draw_Flg == false && enemy[47].Draw_Flg == false) {
		enemy[49].x = enemy[26].fx;
	}
	return 0;
}

//黄色の敵が動く時の処理
int Enemy_Move_Flg(int num_i) {

	enemy[num_i].Attack_Move_Flg = true;
	enemy[num_i].Move_Flg = true;
	e_count[num_i] = 0;

	for (j = num_i + 4; j < 10; j++) {
		if (enemy[j].Draw_Flg == true) {
			enemy[j].Attack_Move_Flg = true;
			enemy[j].Move_Flg = true;
			e_count[j] = 0;
			cntRed++;
		}
		if (cntRed >= 2) {
			cntRed = 0;
			break;
		}
	}
	return 0;
}

/***************************************
  　　　　　敵の攻撃の動き
	   敵の動き出しの処理関数
****************************************/
int Enemy_Attack_Chose() {

	//敵のモーションタイマー
	timer--;
	if (timer <= 0) {//タイマーがゼロになったら、元に戻す
		timer = 8000;
		cntEnemy++;

		if (cntEnemy >= 5) {
			cntEnemy = -5;
			switch (cntYellow) {
			case 2:
				if (epx < enemy[32].fx - 20 || enemy[3].Draw_Flg == false) {
					n = 0;
				}
				else {
					n = 3;
				}
				break;
			case 3:
				if (epx < enemy[32].fx - 20) {
					if (enemy[0].Draw_Flg == false) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == false) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == false && enemy[3].Draw_Flg == false) {
						n = 1;
					}
				}
				else {
					if (enemy[3].Draw_Flg == false) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == false) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == false && enemy[0].Draw_Flg == false) {
						n = 1;
					}
				}
				break;
			case 4:
				if (epx < enemy[32].fx - 20) {
					if (enemy[0].Draw_Flg == false) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == false) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == false && enemy[3].Draw_Flg == false && enemy[2].Draw_Flg == false) {
						n = 1;
					}
					if (enemy[0].Draw_Flg == false && enemy[3].Draw_Flg == false && enemy[1].Draw_Flg == false) {
						n = 2;
					}
				}
				else {
					if (enemy[3].Draw_Flg == false) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == false) {
						n = 3;
					}
					if (enemy[0].Draw_Flg == false && enemy[3].Draw_Flg == false && enemy[1].Draw_Flg == false) {
						n = 2;
					}
					if (enemy[0].Draw_Flg == false && enemy[3].Draw_Flg == false && enemy[2].Draw_Flg == false) {
						n = 1;
					}
				}
				break;
			}
			Enemy_Move_Flg(n);
		}
		else if (epx > enemy[32].fx - 20) { //プレイヤーが画面の右側にいた場合
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

	if (EnemyCount > *num && enemy[*num].Draw_Flg == true) {
		
		//下方向に向かって移動
		enemy[*num].y += 1;	
		
		for (j = 0; j < NUMSHOT; j++) {
			//攻撃のタイマー
			attack_enemy[*num][j].timer--;
			if (attack_enemy[*num][j].timer <= 0) {

				//あとで動き出しのときに設定するように変える
				attack_enemy[*num][j].timer = 40000;

				attack_enemy[*num][j].enemyshot = true;

				Enemy_Shot(enemy[*num].x, enemy[*num].y, *num);

			}
		}

		if (enemy[*num].Attack_Move_Flg == true) {
			e_count[*num]++;
			if (e_count[*num] / 20 > 14) {
				e_count[*num] = 0;
			}

			//enemy[*num].x += (enemy[*num].deg* sin(enemy[*num].x));
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
			if (attack_enemy[h][k].enemyshot == true) {
				ebullet[h][k].x = x + 4;
				ebullet[h][k].y = y + 4;
				ebullet[h][k].Draw_Flg = true;
				attack_enemy[h][k].enemyshot = false;
			}
		}
	}
	return 0;
}

int EnemyShot_Move() {

	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {

			if (ebullet[i][j].y <= 750 && ebullet[i][j].y >= 280) {
				ebullet[i][j].y += 5;
			}

		}
	}

	Enemy_Hit();

	return 0;
}

//プレーヤーの弾が当たったかとスコア
int Player_Hit() {
	if (pbullet_x + 1 == enemy[i].x + 5 && pbullet_x == enemy[i].x + 16 && pbullet_y == enemy[i].y + 5 && pbullet_y == enemy[i].y + 16) {
		if (enemy[i].Attack_Move_Flg == false && enemy[i].Move_Flg == false) {
			switch (enemy[i].Type) {
			case 0:
				e_score += 30;
				break;
			case 1:
				e_score += 40;
				break;
			case 2:
				e_score += 50;
				break;
			case 3:
				e_score += 60;
				break;
			}
		}
		else {
			switch (enemy[i].Type) {
			case 0:
				e_score += 60;
				break;
			case 1:
				e_score += 80;
				break;
			case 2:
				e_score += 100;
				break;
			case 3:
				e_score += 200;
				break;
			}
		}
		enemy[i].Draw_Flg = false;
	}
	return e_score;
}

//敵の弾の当たり判定
int Enemy_Hit() {

	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {

			if (epx - 7 >= ebullet[i][j].x && epx + 7 <= ebullet[i][j].x && epy - 8 >= ebullet[i][j].y + 3 && epy +9 <= ebullet[i][j].y) {
				Enemy_Hit_Flg = true;
			}

		}
	}
	return Enemy_Hit_Flg;
}

//プレーヤーと敵の角度
int Enemy_deg(int *num) {

	enemy[*num].deg = atan2(epy - enemy[*num].y, epx - enemy[*num].x);

	if (enemy[*num].deg < 0) {
		enemy[*num].deg = enemy[*num].deg + 2 * PI;
	}

	enemy[*num].deg = (enemy[*num].deg * 360 / (2 * PI));
	return 0;
}

int Enemy_Draw() {

	
	//DrawFormatString(10, 20, GetColor(255, 255, 255), "%lf", enemy[37].deg);
	//DrawBox(epx - 10, epy - 15, epx + 10, epy + 15, GetColor(255, 255, 255), false);
	for (i = 0; i < EnemyCount; i++) {

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

int EnemyShot_Draw() {

	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {
			if (ebullet[i][j].Draw_Flg == true && ebullet[i][j].y > 260) {
				DrawRotaGraph(ebullet[i][j].x , ebullet[i][j].y , 2.5, 0, Enemy_Shot_Gyallaly[Enemy_None_Num], true, 0, 0);
			}
		}
	}
	return 0;
}

//敵の球を打つタイマーのセット関数
int Enemy_Shot_Set(int *i) {

	if (*i != 48 && *i != 49) {

		for (j = 0; j < NUMSHOT; j++) {
			switch (j) {
			case 0:
				attack_enemy[*i][j].timer = 0;
				break;
			case 1:
				attack_enemy[*i][j].timer = 50;
				break;
			case 2:
				if (enemy[*i].Type != 3) {
					attack_enemy[*i][j].timer = 100;
				}
				else {
					attack_enemy[*i][j].timer = 10000;
				}
				break;
			case 3:
				if (enemy[*i].Type != 3 && enemy[*i].Type != 2) {
					attack_enemy[*i][j].timer = 150;
				}
				else {
					attack_enemy[*i][j].timer = 10000;
				}
				break;
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