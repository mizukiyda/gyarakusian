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

S_EShot ebullet[NUMSHOT];

MODE mode;

S_EnemyType E_State;

TYPE type;

SHOTPOINT S_Point;

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

//次のEnemy
int ne;


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
bool Enemy_Hit_Flg = false;

//Enemyで数えたスコア
int e_score;

static int Shot_Set = 0;

int timerEnemy = 0;
int cntAttack = 0;

int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;

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
		enemy[i].vct = 0;
		enemy[i].vct2 = 0;
		enemy[i].speed = 1;
		enemy[i].x = enemy[i].fx;
		enemy[i].y = enemy[i].fy;
		enemy[i].anime_cnt = 0;
		enemy[i].mode = NONE;
		enemy[i].Draw_Flg = Draw_ON;
		enemy[1].Draw_Flg = Draw_OFF;
		enemy[2].Draw_Flg = Draw_OFF;


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

	for (i = 0; i < NUMSHOT; i++) {

		ebullet[i].x = 10;
		ebullet[i].y = 750;
		ebullet[i].Draw_Flg = false;

	}

	for (i = 0; i < 4; i++) {
		if (enemy[i].Draw_Flg == Draw_ON) {
			cntYellow++;
		}
	}

	speed = 1;

	Enemy_Hit_Flg = false;

	SRand(GetDateTime(&Date));

	e_score = -60;

	return 0;
}

int Enemy_Move() {

	//プレイヤーの座標受け取り(真ん中)
	epx = Player_Pos_Init_x();
	epy = Player_Pos_Init_y();

	Enemy_control();

	//左右移動
	if ((enemy[49].x > 1080.0 || enemy[48].x < 200.0)) {
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
				Enemy_Attack_Move(&i);
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

		//EnemyShot_Mgr();

		cntYellow = 0;
		for (j = 0; j < 4; j++) {
			if (enemy[j].Draw_Flg == Draw_ON) {
				cntYellow++;
			}
		}
	}

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
	e_count[num_i] = 0;

	for (j = num_i + 4; j < num_i + 7; j++) {
		if (enemy[j].Draw_Flg == Draw_ON) {
			SetGax_Sound(4);
			enemy[j].mode = ATTACK;
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

	int Attack_Mode = GetRand(2) + 1;

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

int Enemy_Attack_Move(int *num) {

	if (EnemyCount > *num && enemy[*num].Draw_Flg == Draw_ON) {

		//下方向に向かって移動
		enemy[*num].y += 1;

		if (enemy[*num].y == 280) {
			EnemyShot();
		}

		if (enemy[*num].mode == ATTACK) {
			e_count[*num]++;
			if (e_count[*num] / 20 > 14) {
				e_count[*num] = 0;
			}

			enemy[*num].x += move[e_count[*num] / 20];
		}
		//画面外に行ったら、上に戻す
		if (enemy[*num].x < 0 || enemy[*num].x>1280) {
			enemy[*num].x = enemy[*num].fx;
			enemy[*num].y = -40;
			enemy[*num].mode = MOVE;
		}
		//画面下に行ったときの処理
		if (enemy[*num].y >= 750) {
			enemy[*num].y = -10;
			enemy[*num].x = enemy[*num].fx;
			enemy[*num].mode = MOVE;
		}
	}
	return 0;
}

int EnemyShot_Mgr() {

	if (enemy[i].y == SHOT_POINT_FIRST &&
		enemy[i].y == SHOT_POINT_SECOND &&
		enemy[i].y == SHOT_POINT_THIRD &&
		enemy[i].y == SHOT_POINT_FOURTH) {
		Shot_Set++;
	}

	for (int l = 0; l < NUMSHOT; l++) {
		if (ebullet[l].Draw_Flg == false && Shot_Set > 0) {
			ebullet[l].Draw_Flg = true;
			ebullet[l].x = enemy[i].x;
			ebullet[l].y = enemy[i].y;
			SetGax_Sound(4);							//enemyが発射の音
			Shot_Set--;
		}
		EnemyShot_Move();

		EnemyShot_Draw();

	}
	return 0;
}

int EnemyShot() {
	return 0;
}

int EnemyShot_Move() {

	Enemy_Hit_Flg = Player_Hit();

	for (j = 0; j < NUMSHOT; j++) {
		ebullet[j].y += 3;

		if (epx - 10 <= ebullet[j].x && epx + 20 >= ebullet[j].x && epy == ebullet[j].y) {
			Enemy_Hit_Flg = true;
			ebullet[j].Draw_Flg = false;
		}

	}

	for (int k = 0; k < EnemyCount; k++) {
		if (enemy[k].Draw_Flg == Draw_ON) {
			enemy[k].Draw_Flg = Player_HIT(k);
		}
		Enemy_Score(k);

	}
	if (Enemy_Hit_Flg == true) {
		Enemy_Hit_Flg = false;
		return true;
	}
	return false;
}

//プレーヤーの弾が当たったかとスコア
int Enemy_Score(int killed) {
	if (enemy[killed].Draw_Flg == Draw_OFF) {
		if (enemy[killed].mode == NONE) {
			switch (enemy[killed].Type) {
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
			switch (enemy[killed].Type) {
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
		enemy[killed].Draw_Flg = Breaken;
	}

	for (i = 0; i < EnemyCount; i++) {
		Enemy_State_Init(i);
	}

	return e_score;
}

//敵の弾の当たり判定
int Enemy_Hit() {

	/*Enemy_Hit_Flg = Player_Hit();
	for (i = 0; i < EnemyCount; i++) {
		for (j = 0; j < NUMSHOT; j++) {
			if (epx - 10 <= ebullet[i][j].x && epx + 20 >= ebullet[i][j].x && epy - 20  >= ebullet[i][j].y ){//+ 3 && epy  <= ebullet[i][j].y) {
				Enemy_Hit_Flg = true;
				ebullet[i][j].Draw_Flg = false;
			}
		}
	}*/
	return Enemy_Hit_Flg;
}

int Enemy_Draw() {

	for (i = 0; i < EnemyCount; i++) {

		switch (enemy[i].Draw_Flg) {
		case Draw_ON:

			DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime], true, 0, 0);

			break;
		case Draw_OFF:
			break;

		case Draw_Anime:
			enemy[i].anime_cnt++;
			switch (enemy[i].anime_cnt / 10) {
			case 0:
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[33], true, 0, 0);
				break;
			case 1:
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[34], true, 0, 0);
				break;
			case 2:
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[35], true, 0, 0);
				break;
			case 3:
			case 4:
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[32], true, 0, 0);
				break;
			case 5:
				enemy[i].Draw_Flg = Breaken;
				enemy[i].anime_cnt = 0;
				break;
			}
			break;
		case Breaken:
			break;
		}

	}

	return 0;
}

int EnemyShot_Draw() {

	for (j = 0; j < NUMSHOT; j++) {

		if (ebullet[j].Draw_Flg == true) {
			DrawRotaGraph(ebullet[j].x, ebullet[j].y, 2.5, 0, Enemy_Shot_Gyallaly[Enemy_None_Num], true, 0, 0);
		}
	}
	DrawFormatString(300, 20, GetColor(255, 255, 255), "%d", e_score);
	return 0;
}

int Enemy_Stage_clear() {

	//まだ撃破されてなかったら、returnで-1を返す。
	for (i = 4; i < EnemyCount; i++) {
		if (enemy[i].Draw_Flg == Draw_ON) {
			return -1;
		}
	}

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