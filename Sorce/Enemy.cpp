#include"DxLib.h"
#include"Enemy.h"
#include"PlayerShot.h"
#include"Player.h"
#include<Math.h>
#include<time.h>
#include<stdlib.h>
#include"Sound.h"

/********************  変数宣言  ****************************/

P_Enemy enemy[50];

A_Enemy attack_enemy[48][NUMSHOT];

S_EShot ebullet[EnemyCount][NUMSHOT];

DATEDATA Date;

//ループ用
static int h, i, j, k;

//敵の変数

  //敵の移動用
int e_count[48] = { 0 };
int move[14] = { 0,1,3,4,4,3,1 ,0,-1,-3,-4,-4,-3,-1 };
//int t_a[12] = { 4000,4000,4000,6000,6000,6000,8000,8000,8000,12000,12000,20000 };

int copy_i = 0;

//角度
int e_deg = 0;
//
int n = 0;


//Enemyの攻撃に移るまでのタイマー
double timer = 12000;

//行動カウント

  //敵の移動スピード
int speed;

//プレイヤーの位置情報格納用
int epx;
int epy;

//プレイヤーの弾
int pbullet_x;
int pbullet_y;


//画像格納変数
int Enemy_Handle[40];
int Enemy_Shot_Gyallaly[2];

int Enemy_None_Num;

//Enemyが当てられたフラグ
bool Enemy_Hit_Flg;

//Enemyで数えたスコア
int e_score;

int timerEnemy = 0;
int cntAttack = 0;

int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;

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


int Enemy_Init() {

	//画像読み込み
	LoadDivBmpToGraph("Image/Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle, true, false);

	LoadDivBmpToGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 12, Enemy_Shot_Gyallaly,true,false);
	Enemy_None_Num = 1;


	for (i = 0; i < 50; i++) {
		enemy[i].fx = first_x[i];
		enemy[i].fy = first_y[i];
		enemy[i].deg = 0;
		enemy[i].vct = 0;
		enemy[i].vct2 = 0;
		enemy[i].speed = 1;
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
	timerEnemy = 0;
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

	speed = 1;

	Enemy_Hit_Flg = false;

	SRand(GetDateTime(&Date));

	epx = 500;  //debug
	epy = 600;  //degug
	e_score = 0;

	return 0;
}

int Enemy_Move() {

	//プレイヤーの座標受け取り(真ん中)
	epx = Player_Pos_Init_x() + 19;
	epy = Player_Pos_Init_y() + 18;
	pbullet_x = PlayerShot_Pos_Init_x();// +19;
	pbullet_y = PlayerShot_Pos_Init_y();// +18;
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
			//enemy[i].deg += 15;
			if (enemy[i].deg >= 360) {
				enemy[i].deg = 0;
			}

			enemy[i].Move_Flg = false;
		}

		cntYellow = 0;
		for (j = 0; j < 4; j++) {
			if (enemy[j].Draw_Flg == true) {
				cntYellow++;
			}
		}

	}

	Enemy_Stage_clear();
	return 0;
}

//左右移動で、表示上の敵で切り返す処理 (たぶん完成)
int Enemy_control() {

	if (enemy[23].Draw_Flg == false && enemy[33].Draw_Flg == false && enemy[43].Draw_Flg == false && enemy[14].Draw_Flg == false && enemy[7].Draw_Flg == false) {
		enemy[48].x = enemy[32].fx;
	}
	if (enemy[22].Draw_Flg == false && enemy[32].Draw_Flg == false && enemy[42].Draw_Flg == false && enemy[13].Draw_Flg == false && enemy[6].Draw_Flg == false) {
		enemy[48].x = enemy[31].fx;
	}
	if (enemy[21].Draw_Flg == false && enemy[31].Draw_Flg == false && enemy[41].Draw_Flg == false && enemy[12].Draw_Flg == false && enemy[5].Draw_Flg == false) {
		enemy[48].x = enemy[30].fx;
	}
	if (enemy[20].Draw_Flg == false && enemy[30].Draw_Flg == false && enemy[40].Draw_Flg == false && enemy[11].Draw_Flg == false && enemy[4].Draw_Flg == false) {
		enemy[48].x = enemy[29].fx;
	}
	if (enemy[19].Draw_Flg == false && enemy[29].Draw_Flg == false && enemy[39].Draw_Flg == false && enemy[10].Draw_Flg == false) {
		enemy[48].x = enemy[28].fx;
	}
	if (enemy[18].Draw_Flg == false && enemy[28].Draw_Flg == false && enemy[38].Draw_Flg == false) {
		enemy[48].x = enemy[27].fx;
	}


	if (enemy[22].Draw_Flg == false && enemy[32].Draw_Flg == false && enemy[42].Draw_Flg == false && enemy[13].Draw_Flg == false && enemy[6].Draw_Flg == false) {
		enemy[49].x = enemy[21].fx;
	}
	if (enemy[23].Draw_Flg == false && enemy[33].Draw_Flg == false && enemy[43].Draw_Flg == false && enemy[14].Draw_Flg == false && enemy[7].Draw_Flg == false) {
		enemy[49].x = enemy[22].fx;
	}
	if (enemy[24].Draw_Flg == false && enemy[34].Draw_Flg == false && enemy[44].Draw_Flg == false && enemy[15].Draw_Flg == false && enemy[8].Draw_Flg == false) {
		enemy[49].x = enemy[23].fx;
	}
	if (enemy[25].Draw_Flg == false && enemy[35].Draw_Flg == false && enemy[45].Draw_Flg == false && enemy[16].Draw_Flg == false && enemy[9].Draw_Flg == false) {
		enemy[49].x = enemy[24].fx;
	}
	if (enemy[26].Draw_Flg == false && enemy[36].Draw_Flg == false && enemy[46].Draw_Flg == false && enemy[17].Draw_Flg == false) {
		enemy[49].x = enemy[25].fx;
	}
	if (enemy[27].Draw_Flg == false && enemy[37].Draw_Flg == false && enemy[47].Draw_Flg == false) {
		enemy[49].x = enemy[26].fx;
	}
	return 0;
}

//黄色の敵が動く時の処理 (たぶん完成)
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
	cntAttack++;
	if (cntAttack >= 120) {
		cntAttack = 0;
	}

	if (timer <= 0) {//タイマーがゼロになったら、元に戻す
		timer = 8000;// t_a[cntAttack % 12];
		timerEnemy++;

		if (timerEnemy >= 5) {
			timerEnemy = -5;

			//黄色の敵の選択
			switch (cntYellow) {
			case 1:
				if (epx < enemy[32].fx - 20 || enemy[0].Draw_Flg == false) {
					n = 3;
				}
				else {
					n = 0;
				}
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
		else if (epx > (enemy[48].x + enemy[49].x + 20) / 2) { //プレイヤーが敵の右側にいた場合

			cntEnemy = 0;

			for (j = 18; j < 27; j++) {
				if (GetRand(2) == 0) {
					if (j == 18 || j == 27) {
						for (h = 0; h < 3; h++) {
							if (enemy[j + h * 10].Move_Flg == false && enemy[j + h * 10].Draw_Flg == true) {
								enemy[j + h * 10].Attack_Move_Flg = true;
								enemy[j + h * 10].Move_Flg = true;
								cntEnemy++;
								if (cntEnemy >= 2) {
									goto CHOSE;
								}
							}
						}
					}
					else if(j == 19&& j == 17){
						for (h = 0; h < 5; h++) {
							if (cntYellow == 0 && h == 0) {
								if (enemy[j - 16].Move_Flg == false && enemy[j - 16].Draw_Flg == true) {
									enemy[j - 16].Attack_Move_Flg = true;
									enemy[j - 16].Move_Flg = true;
									cntEnemy++;
								}
							}
							if (h == 1) {
								if (enemy[j - 9].Move_Flg == false && enemy[j - 9].Draw_Flg == true) {
									enemy[j - 9].Attack_Move_Flg = true;
									enemy[j - 9].Move_Flg = true;
									cntEnemy++;
								}
							}
							else {
								if (enemy[j + (h - 1) * 10].Move_Flg == false && enemy[j + (h - 1) * 10].Draw_Flg == true) {
									enemy[j + (h - 1) * 10].Attack_Move_Flg = true;
									enemy[j + (h - 1) * 10].Move_Flg = true;
									cntEnemy++;
									if (cntEnemy >= 2) {
										goto CHOSE;
									}
								}
							}
						}
					}
					else {
						for (h = 0; h < 4; h++) {
							if (h == 0) {
								if (enemy[j - 9].Move_Flg == false && enemy[j - 9].Draw_Flg == true) {
									enemy[j - 9].Attack_Move_Flg = true;
									enemy[j - 9].Move_Flg = true;
									cntEnemy++;
								}
							}
							else {
								if (enemy[j + (h - 1) * 10].Move_Flg == false && enemy[j + (h - 1) * 10].Draw_Flg == true) {
									enemy[j + (h - 1) * 10].Attack_Move_Flg = true;
									enemy[j + (h - 1) * 10].Move_Flg = true;
									cntEnemy++;
									if (cntEnemy >= 2) {
										goto CHOSE;
									}
								}
							}
						}
					}
				}
				else {
					if (j == 18) {
						if (enemy[j].Move_Flg == false && enemy[j].Draw_Flg == true) {
							enemy[j].Attack_Move_Flg = true;
							enemy[j].Move_Flg = true;
							enemy[j - 10].Attack_Move_Flg = true;
							enemy[j - 10].Move_Flg = true;
							cntEnemy++;
						}
					}
				}


			}
		}
		else {

		}
	CHOSE:;
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
				//SetGax_Sound(4);				//enemyの発射音（ここではなかった）
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
	//j = Player_HIT(k);
	//Player_Hit(j);
	for (int k = 0; k < EnemyCount; k++) {
		enemy[k].Draw_Flg = Player_HIT(k);
		//if (enemy[k].Draw_Flg == false) {
		Enemy_State_Init(k);
			//SetGax_Sound(5);							//enemyがやられた時の音(ここではなかった)
		//}
	}
	return 0;
}

//プレーヤーの弾が当たったかとスコア
int Player_Hit() {
	//if (pbullet_x + 1 == enemy[i].x + 5 && pbullet_x == enemy[i].x + 16 && pbullet_y == enemy[i].y + 5 && pbullet_y == enemy[i].y + 16) {
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

		//enemy[Player_HIT(num)].Draw_Flg = false;
		for (i = 0;i < EnemyCount;i++) {
			Enemy_State_Init(i);

		}
	//}
	return e_score;
}

//敵の弾の当たり判定
int Enemy_Hit() {

	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {

			if (epx - 7 >= ebullet[i][j].x && epx + 7 <= ebullet[i][j].x && epy - 8 >= ebullet[i][j].y + 3 && epy +9 <= ebullet[i][j].y&& enemy[i].Draw_Flg == true) {
				Enemy_Hit_Flg = true;
			}

		}
	}
	return Enemy_Hit_Flg;
}

//プレーヤーと敵の角度
/*int Enemy_deg(int *num) {

	enemy[*num].deg = atan2(epy - enemy[*num].y, epx - enemy[*num].x);

	if (enemy[*num].deg < 0) {
		enemy[*num].deg = enemy[*num].deg + 2 * PI;
	}

	enemy[*num].deg = (enemy[*num].deg * 360 / (2 * PI));
	return 0;
}*/

//プレーヤーと敵の角度
int Enemy_deg(int *num) {

	enemy[37].deg = atan2(epy - enemy[37].y, epx - enemy[37].x);

	if (enemy[37].deg < 0) {
		enemy[37].deg = enemy[37].deg + 2 * PI;
	}

	enemy[37].deg = (enemy[37].deg * 360 / (2 * PI));
	return 0;
}

int Enemy_Draw() {
	

	//DrawBox(epx-7, epy-8, epx + 7, epy + 9, GetColor(255, 255, 255), false);
	//DrawBox(pbullet_x, pbullet_y, pbullet_x +1, pbullet_y + 3, GetColor(255, 255, 255), false);
	
	for (i = 0; i < EnemyCount; i++) {
		//DrawFormatString(10, 150,  GetColor(255, 255, 255), "%d", Player_HIT(47));
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
			//DrawBox(enemy[i].x - 7, enemy[i].y - 8, enemy[i].x + 7, enemy[i].y + 9, GetColor(255, 255, 255), false);

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

int Enemy_Stage_clear() {

	//まだ撃破されてなかったら、returnで-1を返す。
	for (i = 4; i < EnemyCount; i++) {
		if (enemy[i].Draw_Flg == true) {
			return -1;
		}
	}

	//黄色以外が全部撃破されてたら…
	cntYellow = 0;
	for (i = 0; i < 4; i++) {
		if (enemy[i].Draw_Flg == true) {
			cntYellow++;
		}
	}

	//黄色が2体以上残ってる状態でクリアしたら、二体分引き継ぐ
	if (cntYellow >= 2)cntYellow = 2;

	return cntYellow;
}

int Enemy_Pos_Init_x(int num) {
	
	return enemy[num].x;
}

int Enemy_Pos_Init_y(int num) {
	return enemy[num].y;
}

int Enemy_State_Init(int num) {
	return enemy[num].Draw_Flg;
}

int Enemy_End() {
	return 0;
}