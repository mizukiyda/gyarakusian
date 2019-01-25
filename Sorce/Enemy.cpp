#include"DxLib.h"
#include"Enemy.h"
#include"PlayerShot.h"
#include"Player.h"
#include<Math.h>
#include<time.h>
#include<stdlib.h>
#include"Sound.h"
#include "Scene_Mgr.h"

/********************  変数宣言  ****************************/

P_Enemy enemy[50];

E_POINT point[4];

SHOT_FLAG shot_flg[50];

POS enemy_shot[NUMSHOT];

Blow blow[REMITBLOW];

POS tmpBlow[REMITBLOW];

POS tmpEnemyShot[NUMSHOT];

VECTORE vct;

MODE mode;

S_EnemyType E_State;

TYPE type;

SHOTPOINT S_Point;

DATEDATA Date;

//ループ用
static int h, i, j;

//敵の変数

int copy_i = 0;

//角度
int e_deg = 0;
//
int n = 0;

//次のEnemy
int ne;


//Enemyの攻撃に移るまでのタイマー
double timer = 24000;

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
bool Enemy_Hit_Flg = false;

//Enemyで数えたスコア
int e_score;

int timerEnemy = 0;
int cntAttack = 0;

int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;

//爆発の数を加算する変数
int NumBlow = 0;
int cntBlow = 0;

//敵の弾の数を加算する変数
int numShot = 0;
int cntShot = 0;


int T_Count[EnemyCount] = { 0 };
int P_Count[EnemyCount] = { 0 };

//初期位置(x座標)
static double first_x[50] = { 590,630,670,710					//3
, 550,590,630,670,710,750				//9
, 510, 550,590,630,670,710,750,790			//17
, 470, 510, 550,590,630,670,710,750,790,830		//27
, 470, 510, 550,590,630,670,710,750,790,830		//37
, 470, 510, 550,590,630,670,710,750,790,830		//47
, 470, 830 };

//初期位置(y座標)
static double first_y[50] = { 80, 80, 80, 80
,110,110,110,110,110,110
,140,140,140,140,140,140,140,140
,170,170,170,170,170,170,170,170,170,170
,200,200,200,200,200,200,200,200,200,200
,230,230,230,230,230,230,230,230,230,230
,80,80 };


int Enemy_Init() {

	//画像読み込み
	LoadDivBmpToGraph("Image/Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle, true, false);

	LoadDivBmpToGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 12, Enemy_Shot_Gyallaly, true, false);
	Enemy_None_Num = 1;


	for (i = 0; i < 50; i++) {
		enemy[i].fx = first_x[i];
		enemy[i].fy = first_y[i];
		enemy[i].deg = 0;
		enemy[i].vct_x = 0;
		enemy[i].vct_y = 0;
		enemy[i].pt_x = 0;
		enemy[i].pt_y = 900;
		enemy[i].cp_x = 0;
		enemy[i].cp_y = 0;
		enemy[i].speed = 1;
		enemy[i].x = enemy[i].fx;
		enemy[i].y = enemy[i].fy;
		enemy[i].anime_cnt = 0;
		enemy[i].mode = NONE;
		enemy[i].A_Mode = NONE;
		enemy[i].Draw_Flg = Draw_ON;
		enemy[1].Draw_Flg = Breaken;
		enemy[2].Draw_Flg = Breaken;

		if (i < 4) {
			enemy[i].Type = YELLOW;
			enemy[i].anime = 0;
			enemy[i].nx = 90;
		}
		else if (i < 10) {
			enemy[i].Type = RED;
			enemy[i].anime = 8;
			enemy[i].nx = 120;
		}
		else if (i < 18) {
			enemy[i].Type = PURPLE;
			enemy[i].anime = 16;
			enemy[i].nx = 150;
		}
		else if (i < 28) {
			enemy[i].Type = BLUE;
			enemy[i].anime = 24;
			enemy[i].nx = 180;
		}
		else if (i < 38) {
			enemy[i].Type = BLUE;
			enemy[i].anime = 24;
			enemy[i].nx = 210;
		}
		else {
			enemy[i].Type = BLUE;
			enemy[i].anime = 24;
			enemy[i].nx = 240;
		}

		shot_flg[i].first_shot = false;
		shot_flg[i].second_shot = false;
		shot_flg[i].third_shot = false;
		shot_flg[i].fourth_shot = false;
	}
	timerEnemy = 0;
	cntRed = 0;

	for (i = 0; i < NUMSHOT; i++) {

		enemy_shot[i].x = 10;
		enemy_shot[i].y = 750;
		enemy_shot[i].onActive = false;

	}

	for (i = 0; i < 4; i++) {
		if (enemy[i].Draw_Flg == Draw_ON) {
			cntYellow++;
		}
	}

	for (i = 0; i < 4; i++) {

		switch (i) {
		case 0:
			point[i].basis_x = CENTER_X;
			point[i].basis_y = 0;
			point[i].vct = RIGHT;
			point[i].deg = 0;
			point[i].vct_x = 0;
			point[i].vct_y = 0;
			point[i].x = 0;
			point[i].y = 0;
			break;
		case 1:
			point[i].basis_x = CENTER_X;
			point[i].basis_y = CENTER_Y / 2;
			point[i].vct = LEFT;
			point[i].deg = 0;
			point[i].vct_x = 0;
			point[i].vct_y = 0;
			point[i].x = 0;
			point[i].y = 0;
			break;
		case 2:
			point[i].basis_x = CENTER_X;
			point[i].basis_y = CENTER_Y / 2;
			point[i].vct = RIGHT;
			point[i].deg = 0;
			point[i].vct_x = 0;
			point[i].vct_y = 0;
			point[i].x = 0;
			point[i].y = 0;
			break;
		case 3:
			point[i].basis_x = 500;
			point[i].basis_y = CENTER_Y;
			point[i].x = point[i].basis_x;
			point[i].y = point[i].basis_y;
			point[i].vct = RIGHT;
			point[i].remit_x = 10;
			break;
		}

	}

	speed = 1;

	Enemy_Hit_Flg = false;

	SRand(GetDateTime(&Date));

	e_score = 0;

	return 0;
}

int Enemy_Move() {

	//プレイヤーの座標受け取り(真ん中)
	epx = Player_Pos_Init_x();
	epy = Player_Pos_Init_y();

	Enemy_POINT();

	Enemy_control();

	//左右移動
	if ((enemy[49].x > 850.0 || enemy[48].x < 200.0)) {
		speed *= -1;
	}

	for (i = 0; i < EnemyCount + 2; i++) {

		//常に左右移動
		enemy[i].fx += speed;

		//ここで動く敵の順番を選択
		Enemy_Attack_Chose();
		if (enemy[i].Draw_Flg == Draw_ON) {
			switch (enemy[i].mode) {

			case NONE:
				enemy[i].x += speed;
				break;

			case ATTACK:
				if (enemy[i].A_Mode == NONE) {
					enemy[i].A_Mode = FIRST;
				}
				Enemy_Attack_Move(i);
				break;

			case MOVE:
				enemy[i].y += 1;
				enemy[i].x += speed;
				if (enemy[i].mode == MOVE && enemy[i].y == enemy[i].fy) {
					enemy[i].mode = NONE;
				}
				break;
			}
		}

		

		cntYellow = 0;
		for (j = 0; j < 4; j++) {
			if (enemy[j].Draw_Flg == Draw_ON) {
				cntYellow++;
			}
		}
	}
	Create_Blow();

	EnemyShot_Mgr();

	Enemy_Stage_clear();
	return 0;
}

//左右移動で、表示上の敵で切り返す処理 (たぶん完成)
int Enemy_control() {

	/*if (enemy[23].Draw_Flg == false && enemy[33].Draw_Flg == false && enemy[43].Draw_Flg == false && enemy[14].Draw_Flg == false && enemy[7].Draw_Flg == false) {
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
	}*/
	return 0;
}

//黄色の敵が動く時の処理 (たぶん完成)
int Enemy_Move_Flg(int num_i) {

	enemy[num_i].mode = ATTACK;

	for (j = num_i + 4; j < num_i + 7; j++) {
		if (enemy[j].Draw_Flg == Draw_ON) {
			SetGax_Sound(4);
			enemy[j].mode = ATTACK;
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

	int Attack_Mode = GetRand(2) + 1;

	//敵のモーションタイマー
	timer--;
	cntAttack++;
	if (cntAttack >= 120) {
		cntAttack = 0;
	}

	if (timer <= 0) {//タイマーがゼロになったら、元に戻す
		timer = 10000;// t_a[cntAttack % 12];
		timerEnemy++;

		if (timerEnemy >= 5) {
			timerEnemy = -5;

			//黄色の敵の選択
			switch (cntYellow) {
			case 1:
				if (epx < enemy[32].fx - 20 || enemy[0].Draw_Flg == Draw_OFF) {
					n = 3;
				}
				else {
					n = 0;
				}
			case 2:
				if (epx < enemy[32].fx - 20 || enemy[3].Draw_Flg == Draw_OFF) {
					n = 0;
				}
				else {
					n = 3;
				}
				break;
			case 3:
				if (epx < enemy[32].fx - 20) {
					if (enemy[0].Draw_Flg == Draw_OFF) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == Draw_OFF) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == Draw_OFF && enemy[3].Draw_Flg == Draw_OFF) {
						n = 1;
					}
				}
				else {
					if (enemy[3].Draw_Flg == Draw_OFF) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == Draw_OFF) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == Draw_OFF && enemy[0].Draw_Flg == Draw_OFF) {
						n = 1;
					}
				}
				break;
			case 4:
				if (epx < enemy[32].fx - 20) {
					if (enemy[0].Draw_Flg == Draw_OFF) {
						n = 3;
					}
					if (enemy[3].Draw_Flg == Draw_OFF) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == Draw_OFF && enemy[3].Draw_Flg == Draw_OFF && enemy[2].Draw_Flg == Draw_OFF) {
						n = 1;
					}
					if (enemy[0].Draw_Flg == Draw_OFF && enemy[3].Draw_Flg == Draw_OFF && enemy[1].Draw_Flg == Draw_OFF) {
						n = 2;
					}
				}
				else {
					if (enemy[3].Draw_Flg == Draw_OFF) {
						n = 0;
					}
					if (enemy[0].Draw_Flg == Draw_OFF) {
						n = 3;
					}
					if (enemy[0].Draw_Flg == Draw_OFF && enemy[3].Draw_Flg == Draw_OFF && enemy[1].Draw_Flg == Draw_OFF) {
						n = 2;
					}
					if (enemy[0].Draw_Flg == Draw_OFF && enemy[3].Draw_Flg == Draw_OFF && enemy[2].Draw_Flg == Draw_OFF) {
						n = 1;
					}
				}
				break;
			}
			Enemy_Move_Flg(n);
		}
		else { //プレイヤーが敵の右側にいた場合

			cntEnemy = 0;

			//二体目を動かし、return　でぬける。
			if (ne >= 49 && ne < 0) {
				enemy[ne].mode = ATTACK;
				ne = 49;
				timer = (GetRand(8) * 1000) + 4000;
				
				return 0;
			}

			switch (Attack_Mode) {
			case MODE_DOWN:
				//もしONにしたのが、黄色だったら
				if (enemy[ne].Type == 0) {
					while (1) {
						ne = GetRand(1) + 1;
						if (ne == 1) {
							for (j = 4; j < 27; j++) {
								if (j < 10 && cntYellow == 0 && enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
									ne = j + 7;
									timer = 3000;
									break;
								}
								else if (j < 18 && enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
									ne = j + 9;
									timer = 3000;
									break;
								}
								else {
									if (enemy[j].mode == NONE) {
										enemy[j].mode = ATTACK;
									}
									else if (enemy[j + 10].mode == NONE) {
										enemy[j + 10].mode = ATTACK;
										ne = j + 10;
									}
									else {
										if (enemy[j + 20].mode == NONE) {
											enemy[j + 20].mode = ATTACK;
											ne = 49;
											timer = (GetRand(8) * 1000) + 4000;
											break;
										}
									}
									ne = j + 10;
									timer = 3000;
									break;
								}
							}
						}
						else {
							for (j = 9; j >= 4; j--) {
								if (cntYellow == 0 && enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
									ne = j + 7;
									timer = 3000;
									return 0;
								}
							}
							for (j = 17; j >= 10; j++) {
								if (enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
									ne = j + 9;
									timer = 3000;
									return 0;
								}
							}
							for (j = 27; j >= 18; j--) {
								if (enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
								}
								else if (enemy[j + 10].mode == NONE) {
									enemy[j + 10].mode = ATTACK;
									ne = j + 10;
								}
								else {
									if (enemy[j + 20].mode == NONE) {
										enemy[j + 20].mode = ATTACK;
										ne = 49;
										timer = (GetRand(8) * 1000) + 4000;
										break;
									}
								}
								ne = j + 10;
								timer = 3000;
								return 0;
							}
						}
					}
				}
				else {
					if (epx > (enemy[48].x + enemy[49].x + 20) / 2) {
						for (j = 4; j < 27; j++) {
							if (j < 10 && cntYellow == 0 && enemy[j].mode == NONE) {
								enemy[j].mode = ATTACK;
								ne = j + 7;
								timer = 3000;
								break;
							}
							else if (j < 18 && enemy[j].mode == NONE) {
								enemy[j].mode = ATTACK;
								ne = j + 9;
								timer = 3000;
								break;
							}
							else {
								if (enemy[j].mode == NONE) {
									enemy[j].mode = ATTACK;
								}
								else if (enemy[j + 10].mode == NONE) {
									enemy[j + 10].mode = ATTACK;
									ne = j + 10;
								}
								else {
									if (enemy[j + 20].mode == NONE) {
										enemy[j + 20].mode = ATTACK;
										ne = 49;
										timer = (GetRand(8) * 1000) + 4000;
										break;
									}
								}
								ne = j + 10;
								timer = 3000;
								break;
							}
						}
					}
					else {
						for (j = 9; j >= 4; j--) {
							if (cntYellow == 0 && enemy[j].mode == NONE) {
								enemy[j].mode = ATTACK;
								ne = j + 7;
								timer = 3000;
								return 0;
							}
						}
						for (j = 17; j >= 10; j++) {
							if (enemy[j].mode == NONE) {
								enemy[j].mode = ATTACK;
								ne = j + 9;
								timer = 3000;
								return 0;
							}
						}
						for (j = 27; j >= 18; j--) {
							if (enemy[j].mode == NONE) {
								enemy[j].mode = ATTACK;
							}
							else if (enemy[j + 10].mode == NONE) {
								enemy[j + 10].mode = ATTACK;
								ne = j + 10;
							}
							else {
								if (enemy[j + 20].mode == NONE) {
									enemy[j + 20].mode = ATTACK;
									ne = 49;
									timer = (GetRand(8) * 1000) + 4000;
									break;
								}
							}
							ne = j + 10;
							timer = 3000;
							return 0;
						}
					}
				}
				break;
			case MODE_NEXT:
				if (epx > (enemy[48].x + enemy[49].x + 20) / 2) {

				}
				else {

				}
				break;
			}
		}
	}

	return 0;
}

int Enemy_Attack_Move(int num) {

	if (EnemyCount > num && enemy[num].Draw_Flg == Draw_ON) {

		switch (enemy[num].A_Mode) {
		case NONE:
			break;
		case FIRST:
			SetGax_Sound(4);
			if (enemy[num].x >= CENTER_X) {
				enemy[num].pt_x = enemy[num].x + 45;
				enemy[num].pt_y = enemy[num].y - 45;
				enemy[num].A_Mode = R_ROLL;
			}
			if (enemy[num].x < CENTER_X) {
				enemy[num].pt_x = enemy[num].x - 45;
				enemy[num].pt_y = enemy[num].y - 45;
				enemy[num].A_Mode = L_ROLL;
			}
			enemy[num].deg = atan2(enemy[num].y - 60, 0);

			break;
		case R_ROLL:
			T_Count[num] += 1;
			enemy[num].deg += 0.03;

			enemy[num].vct_x = 40 * cos(enemy[num].deg);
			enemy[num].vct_y = 40 * sin(enemy[num].deg);

			enemy[num].x = enemy[num].pt_x + enemy[num].vct_x;
			enemy[num].y = enemy[num].pt_y + enemy[num].vct_y;
			break;
		case L_ROLL:
			T_Count[num] += 1;
			enemy[num].deg -= 0.03;

			enemy[num].vct_x = 40 * cos(enemy[num].deg);
			enemy[num].vct_y = 40 * sin(enemy[num].deg);

			enemy[num].x = enemy[num].pt_x + enemy[num].vct_x;
			enemy[num].y = enemy[num].pt_y + enemy[num].vct_y;
			break;
		case R_CURVE:
			enemy[num].deg += 0.0001;

			enemy[num].vct_x = (enemy[num].cp_x - enemy[num].pt_x + 60) * cos(enemy[num].deg);
			enemy[num].vct_y = (enemy[num].pt_y - enemy[num].cp_y) * sin(enemy[num].deg);

			enemy[num].x = enemy[num].pt_x + enemy[num].vct_x;
			enemy[num].y = (enemy[num].cp_y + 50) + enemy[num].vct_y;

			break;
		case L_CURVE:
			enemy[num].deg -= 0.0001;

			enemy[num].vct_x = (enemy[num].pt_x - enemy[num].cp_x - 60) * cos(enemy[num].deg);
			enemy[num].vct_y = (enemy[num].pt_y - enemy[num].cp_y) * sin(enemy[num].deg);

			enemy[num].x = enemy[num].pt_x + enemy[num].vct_x;
			enemy[num].y = (enemy[num].cp_y + 50) + enemy[num].vct_y;

			break;
		case TRACK:
			enemy[num].deg = atan2((enemy[num].pt_y) - enemy[num].y, enemy[num].pt_x - enemy[num].x);

			enemy[num].vct_x = 2 * cos(enemy[num].deg);
			enemy[num].vct_y = 2 * sin(enemy[num].deg);

			enemy[num].x += enemy[num].vct_x;// / 10;
			enemy[num].y += enemy[num].vct_y;// / 10;
			break;
		case CHANGE:

			if (P_Count[num] != 0) {
				enemy[num].pt_x = point[3].x;
				enemy[num].pt_y = point[3].y;

				enemy[num].cp_x = enemy[num].x;
				enemy[num].cp_y = enemy[num].y;

				/*if ( enemy[num].x >enemy[num].pt_x) {
				enemy[num].A_Mode = R_CURVE;
				}
				else {
				enemy[num].A_Mode = L_CURVE;
				}*/
				if (num == 0 || num == 3) {
					enemy[num].pt_y -= 30;
				}
				if (num == 4 || num == 7) {
					enemy[num].pt_x -= 40;
				}if (num == 6 || num == 9) {
					enemy[num].pt_x += 40;
				}
				enemy[num].A_Mode = TRACK;
				break;
			}

			enemy[num].pt_x = point[P_Count[num]].x;

			if (enemy[num].pt_x > epx + 380) {
				P_Count[num] = 1;
			}
			else if (enemy[num].pt_x > epx - 380) {
				P_Count[num] = 2;
			}
			else {
				P_Count[num] = 3;
			}

			enemy[num].pt_x = point[P_Count[num]].x;
			enemy[num].pt_y = point[P_Count[num]].y;

			if (num == 0 || num == 3) {
				enemy[num].pt_y -= 30;
			}
			if (num == 4 || num == 7) {
				enemy[num].pt_x -= 40;
			}if (num == 6 || num == 9) {
				enemy[num].pt_x += 40;
			}
			enemy[num].A_Mode = TRACK;
			break;
		}

		//円の周りを回す場合
		//一定範囲内なら
		if (pow(16 + 60, 2) >= pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			if (enemy[num].A_Mode != L_ROLL && enemy[num].x >= CENTER_X) {
				if (enemy[num].A_Mode != R_ROLL) {

					//enemy[num].deg = atan2(enemy[num].y - 60, 0);

				}
				enemy[num].A_Mode = R_ROLL;
			}
			if (enemy[num].A_Mode != R_ROLL && enemy[num].x < CENTER_X) {
				if (enemy[num].A_Mode != L_ROLL) {

					//enemy[num].deg = atan2(enemy[num].y - 60, 0);

				}
				enemy[num].A_Mode = L_ROLL;
			}
		}

		//円からの脱出(CHANGEに変える)
		if (enemy[num].A_Mode == L_ROLL &&
			enemy[num].pt_y < enemy[num].y  &&
			enemy[num].pt_x > enemy[num].x &&
			T_Count[num] > 10) {
			T_Count[num] = 0;
			enemy[num].A_Mode = CHANGE;
		}
		else if (enemy[num].A_Mode == R_ROLL &&
			enemy[num].pt_y < enemy[num].y &&
			enemy[num].pt_x < enemy[num].x &&
			T_Count[num] > 10) {
			T_Count[num] = 0;
			enemy[num].A_Mode = CHANGE;
		}

		//一定範囲にいたら、中心点が移動する。
		//pow(enemyの半径 + 目標点の半径, 2)
		if (pow(16 + 120, 2) >= pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2) &&
			pow(16 + 60, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			enemy[num].A_Mode = CHANGE;
		}

		//一定範囲外なら、中心点に向かって移動する。
		if (pow(16 + 120, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2) && enemy[num].pt_x <0) {
			enemy[num].A_Mode = TRACK;
		}

		//画面外に行ったら、目標点更新
		if (enemy[num].x < 150) {
			enemy[num].A_Mode = CHANGE;
			P_Count[num] = 3;
			enemy[num].x += 2;
		}
		if ( enemy[num].x>900) {
			enemy[num].A_Mode = CHANGE;
			P_Count[num] = 3;
			enemy[num].x -= 2;
		}
		//画面下に行ったときの処理
		if (enemy[num].y > 780) {
			enemy[num].y = -10;
			enemy[num].x = enemy[num].fx;
			enemy[num].mode = MOVE;
			enemy[num].A_Mode = NONE;
			P_Count[num] = 0;
			enemy[num].pt_y = 0;
			enemy[num].pt_x = 0;
			SetGax_Sound(10);
		}
	}
	return 0;
}

int Enemy_POINT() {

	for (int j = 0; j < 4; j++) {

		if (j != 3) {

			if (point[j].y <= point[j].basis_y + 150) {
				if (point[j].x > point[j].basis_x) {
					point[j].vct = LEFT;
				}
				else if (point[j].x < point[j].basis_x) {
					point[j].vct = RIGHT;
				}
			}
		}
		switch (j) {
		case 0:
			if (point[j].vct == LEFT) {
				//回転のスピード
				point[j].deg += 0.01;
			}
			if (point[j].vct == RIGHT) {
				point[j].deg -= 0.01;
			}
			break;
		case 1:
			if (point[j].x <= point[j].basis_x + 250) {
				point[j].vct = RIGHT;
			}
			if (point[j].y >= point[3].basis_y) {//CENTER_Y * 2 + 150) {
				point[j].vct = RIGHT;
			}
			break;
		case 2:
			if (point[j].x >= point[j].basis_x - 250) {
				point[j].vct = LEFT;
			}
			if (point[j].y >= point[3].basis_y) {//CENTER_Y * 2 + 150) {
				point[j].vct = LEFT;
			}
			break;
		case 3:
			point[j].basis_x = epx;
			point[j].basis_y = epy;
			if (point[j].x > point[j].basis_x + point[j].remit_x ||
				point[j].x < point[j].basis_x - point[j].remit_x) {
				point[j].vct *= -1;
			}
			if (point[j].vct == RIGHT) {
				point[j].x += 1;
			}
			if (point[j].vct == LEFT) {
				point[j].x -= 1;
			}
			point[j].y = point[j].basis_y + 300;
			break;
		}

		switch (j) {
		case 0:
			point[j].vct_x = CENTER_X * cos(point[j].deg);
			point[j].vct_y = (CENTER_Y * 2) * sin(point[j].deg);
			break;
		case 1:
		case 2:
			if (point[j].vct == LEFT) {
				//回転のスピード
				point[j].deg += 0.001;

			}
			if (point[j].vct == RIGHT) {
				point[j].deg -= 0.001;
			}

			//円の半径　×　sin or cos
			point[j].vct_x = CENTER_X * cos(point[j].deg);
			point[j].vct_y = 1000 * sin(point[j].deg);
			break;
		}
		if (j != 3) {
			point[j].x = point[j].basis_x + point[j].vct_x;
			point[j].y = point[j].basis_y + point[j].vct_y;
		}

	}
	return 0;
}

int Enemy_M() {
	/*for (int j = 0; j < EnemyCount; j++) {


	enemy[i].deg = atan2(enemy[i].pt_y - enemy[i].y, enemy[i].pt_x - enemy[i].x);

	int len = (enemy[i].pt_x - enemy[i].x)*(enemy[i].pt_x - enemy[i].x) + (enemy[i].pt_y - enemy[i].y)*(enemy[i].pt_y - enemy[i].y);

	if (len <= ((10 + 30) * (10 + 30))) {

	enemy[i].pt_x = enemy[i].x + epx / 2;

	enemy[i].pt_y -= 100;
	}
	}*/
	return 0;
}

int EnemyShot_Mgr() {

	for (int l = 0; l < EnemyCount; l++) {
		if (enemy[l].Draw_Flg == Draw_ON) {
			if (enemy[l].y >= SHOT_POINT_FIRST - N &&
				enemy[l].y <= SHOT_POINT_FIRST + N && shot_flg[l].first_shot == false) {
				shot_flg[l].first_shot = true;
			}
			if (enemy[l].y >= SHOT_POINT_SECOND - N &&
				enemy[l].y <= SHOT_POINT_SECOND + N && shot_flg[l].second_shot == false) {
				shot_flg[l].second_shot = true;
			}
			if (enemy[l].y >= SHOT_POINT_THIRD - N &&
				enemy[l].y <= SHOT_POINT_THIRD + N && shot_flg[l].third_shot == false) {
				shot_flg[l].third_shot = true;
			}
			if (enemy[l].y >= SHOT_POINT_FOURTH - N &&
				enemy[l].y <= SHOT_POINT_FOURTH + N && shot_flg[l].fourth_shot == false) {
				shot_flg[l].fourth_shot = true;
			}
			if (shot_flg[l].first_shot == true ||
				shot_flg[l].second_shot == true ||
				shot_flg[l].third_shot == true ||
				shot_flg[l].fourth_shot == true) {
				cntShot++;
				if (cntShot > NUMSHOT)cntShot = 0;

				PUSH_SHOT(cntShot, enemy[l].x, enemy[l].y);
				if (shot_flg[l].first_shot == true)shot_flg[l].first_shot = NONE;
				if (shot_flg[l].second_shot == true)shot_flg[l].second_shot = NONE;
				if (shot_flg[l].third_shot == true)shot_flg[l].third_shot = NONE;
				if (shot_flg[l].fourth_shot == true)shot_flg[l].fourth_shot = NONE;
			}

			if (enemy[l].y >= 720) {
				shot_flg[l].first_shot = false;
				shot_flg[l].second_shot = false;
				shot_flg[l].third_shot = false;
				shot_flg[l].fourth_shot = false;
			}
		}
	}

	numShot = 0;

	for (int l = 0; l < NUMSHOT; l++) {
		if (tmpEnemyShot[l].onActive == true) {
			numShot++;
		}
	}

	//再生数が0なら,returnで脱出
	if (numShot <= 0) {
		return 0;
	}

	//配列内のものを前詰めに並び替える。
	for (int l = 0; l < NUMSHOT; l++) {
		for (int n = l; n < NUMSHOT; n++) {
			if (tmpEnemyShot[l].onActive == true && enemy_shot[n].onActive == false) {
				enemy_shot[n].onActive = tmpEnemyShot[l].onActive;
				tmpEnemyShot[l].onActive = false;

				enemy_shot[n].x = tmpEnemyShot[l].x;

				enemy_shot[n].y = tmpEnemyShot[l].y;
			}
		}
	}


	EnemyShot_Move();

	EnemyShot_Draw();

	return 0;
}

int EnemyShot_Move() {

	for (j = 0; j < NUMSHOT; j++) {
		enemy_shot[j].y += 5;

		if (enemy_shot[j].y >= 820) {
			enemy_shot[j].onActive = false;
		}
	}

	for (int k = 0; k < EnemyCount; k++) {
	
		if (enemy[k].Draw_Flg == Draw_ON) {
			enemy[k].Draw_Flg = Player_HIT(k);
		}
		if (enemy[k].Draw_Flg == Draw_OFF) {
			cntBlow++;
			if (cntBlow > REMITBLOW)cntBlow = 0;
			PUSH_BLOW(cntBlow, enemy[k].x, enemy[k].y);
		}
		Enemy_Score(k);
	}

	return 0;
}


//プレーヤーの弾が当たったかとスコア
int Enemy_Score(int killed) {
	if (enemy[killed].Draw_Flg == Draw_OFF) {
		if (enemy[killed].mode == NONE) {
			switch (enemy[killed].Type) {
			case 0:
				e_score += 60;
				SetGax_Sound(6);
				break;
			case 1:
				e_score += 50;
				break;
			case 2:
				e_score += 40;
				break;
			case 3:
				e_score += 30;
				break;
			}
		}
		else {
			switch (enemy[killed].Type) {
			case 0:
				e_score += 60;
				SetGax_Sound(6);
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
		enemy[killed].Draw_Flg = Breaken;
	}

	for (i = 0; i < EnemyCount; i++) {
		Enemy_State_Init(i);
	}

	return e_score;
}

//敵の弾の当たり判定
int Enemy_Hit() {

	for (j = 0; j < NUMSHOT; j++) {

		if (epx - 9 <= enemy_shot[j].x && epx + 18 >= enemy_shot[j].x - 4 &&
			epy - 17 <= enemy_shot[j].y - 5 && epy + 15 >= enemy_shot[j].y + 3 &&
			enemy_shot[j].onActive == true && Enemy_Hit_Flg == false) {
			Enemy_Hit_Flg = true;
			enemy_shot[j].onActive = false;
		}
	}
	for (j = 0; j < EnemyCount; j++) {
		if (enemy[j].mode != ATTACK) {
			continue;
		}
		if (epx - 9 <= enemy[j].x + 20 && epx + 18 >= enemy[j].x - 10 &&
			epy - 17 <= enemy[j].y + 20 && epy + 15 >= enemy[j].y - 10 &&
			enemy[j].Draw_Flg == Draw_ON && Enemy_Hit_Flg == false) {
			Enemy_Hit_Flg = true;
			enemy[j].Draw_Flg = Draw_Anime;

			cntBlow++;
			if (cntBlow > REMITBLOW)cntBlow = 0;
			PUSH_BLOW(cntBlow, enemy[j].x, enemy[j].y);
		}
	}

	if (Enemy_Hit_Flg == true) {
		Enemy_Hit_Flg = false;
		return true;
	}
	return false;

}

/**********************************
関数名：Create_Blow
内容 ：Enemy破壊時に座標を取得し、
　　　 並び替える。
	引数 ：なし
	返却値：なし
	***********************************/
int Create_Blow() {

	NumBlow = 0;

	//爆発の再生数を数える
	for (int l = 0; l < REMITBLOW; l++) {
		if (tmpBlow[l].onActive == true) {
			NumBlow++;
		}
	}

	//再生数が0なら,returnで脱出
	if (NumBlow <= 0) {
		return 0;
	}

	//配列内のものを前詰めに並び替える。
	for (int l = 0; l < REMITBLOW; l++) {
		for (int n = l; n < REMITBLOW; n++) {
			if (tmpBlow[l].onActive == true && blow[n].onActive == false) {
				blow[n].onActive = tmpBlow[l].onActive;
				tmpBlow[l].onActive = false;

				blow[n].x = tmpBlow[l].x;

				blow[n].y = tmpBlow[l].y;
			}
		}
	}

	return 0;
}

int Enemy_Draw() {

	for (i = 0; i < EnemyCount; i++) {

		switch (enemy[i].Draw_Flg) {
		case Draw_ON:

			DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime], true, 0, 0);

			//DrawBox(enemy[i].x - 10, enemy[i].y - 10, enemy[i].x + 20, enemy[i].y + 20, GetColor(255, 0, 0), false);

			break;
		case Draw_OFF:
			break;

		case Draw_Anime:
			break;
		case Breaken:
			break;
		}

	}

	return 0;
}

int EnemyShot_Draw() {

	for (j = 0; j < NUMSHOT; j++) {

		if (enemy_shot[j].onActive == true) {
			DrawRotaGraph(enemy_shot[j].x, enemy_shot[j].y, 2.5, 0, Enemy_Shot_Gyallaly[Enemy_None_Num], true, 0, 0);
		}
	}
	for (i = 0; i < REMITBLOW; i++) {
		//再生

		if (blow[i].onActive == true) {
			blow[i].Blow_Cnt++;

			switch (blow[i].Blow_Cnt / 5) {
			case 0:
				DrawRotaGraph(blow[i].x, blow[i].y, 2.5, 0, Enemy_Handle[33], true, 0, 0);
				break;
			case 1:
				DrawRotaGraph(blow[i].x, blow[i].y, 2.5, 0, Enemy_Handle[34], true, 0, 0);
				break;
			case 2:
				DrawRotaGraph(blow[i].x, blow[i].y, 2.5, 0, Enemy_Handle[35], true, 0, 0);
				break;
			case 3:
				DrawRotaGraph(blow[i].x, blow[i].y, 2.5, 0, Enemy_Handle[32], true, 0, 0);
				break;
			case 5:
				DrawRotaGraph(blow[i].x, blow[i].y, 2.5, 0, Enemy_Handle[36], true, 0, 0);
				break;
			case 4:
				blow[i].onActive = false;
				blow[i].x = 10;
				blow[i].y = 40;
				break;
			}
		}
	}
	DrawFormatString(375, 40, GetColor(255, 0, 0), "%d", e_score);
	return 0;
}

int Enemy_Stage_clear() {

	//まだ撃破されてなかったら、returnで-1を返す。
	for (i = 0; i < EnemyCount; i++) {
		if (enemy[i].Draw_Flg == Draw_ON) {
			return -1;
		}
	}
	Scene_Mgr_ChangeScene(E_Scene_Result);

	//黄色以外が全部撃破されてたら…
	cntYellow = 0;
	for (i = 0; i < 4; i++) {
		if (enemy[i].Draw_Flg == Draw_ON) {
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