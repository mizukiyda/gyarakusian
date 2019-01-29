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

P_Enemy enemy[EnemyCount + 2];

E_POINT point[4];

E_POINT enemy_satellite[EnemyCount + 2];

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
static int i, j;

//Enemy_Move_Flgに渡す。どの黄色は動いたか渡す
int n = 0;

//次のEnemy
int ne;
//右から縦
int Chose_1[EnemyCount - 2] = { 27,37,47,17,26,36,46,9,16,25,35,45,8,15,24,34,44,7,14,23,33,43,6,12,22,32,42,5,12,21,31,41,4,11,20,30,40,10,19,29,39,18,28,38 };
//左から縦
int Chose_2[EnemyCount - 2] = { 18,28,38,10,19,29,39,4,11,20,30,40,5,12,21,31,41,6,13,22,32,42,7,14,23,33,43,8,15,24,34,44,9,16,25,35,45,17,26,36,46,27,37,47 };
//右から横
int Chose_3[EnemyCount - 2] = { 27,17,9,37,26,16,8,47,36,25,15,7,46,35,24,14,6,45,34,23,13,5,44,33,22,12,4,43,32,21,11,42,31,20,10,41,30,19,40,29,18,39,28,38 };
//左から横
int Chose_4[EnemyCount - 2] = { 18,10,4,28,19,11,5,38,29,20,12,6,39,30,21,13,7,40,31,22,14,8,41,32,23,15,9,42,33,24,16,43,34,25,17,44,35,26,45,36,27,46,37,47 };

//Enemyの攻撃に移るまでのタイマー
int timer = 24000;

//敵の移動スピード
int speed;

//プレイヤーの位置情報格納用
int epx;
int epy;

//画像格納変数
int Enemy_Handle[40];
int Enemy_Shot_Gyallaly[2];

int Enemy_None_Num;

//Enemyが当てられたフラグ
bool Enemy_Hit_Flg = false;

//Enemyで数えたスコア
int e_score;

int cntAttack = 0;

int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;
int cntPourple = 0;
int cntBlue = 0;

//爆発の数を加算する変数
int NumBlow = 0;
int cntBlow = 0;

//敵の弾の数を加算する変数
int numShot = 0;
int cntShot = 0;


int T_Count[EnemyCount] = { 0 };
int P_Count[EnemyCount] = { 0 };

//初期位置(x座標)
static double first_x[50] = { 150,190,230,270					//3
, 110,150,190,230,270,310				//9
, 70, 110,150,190,230,270,310,350			//17
, 30, 70, 110,150,190,230,270,310,350,390		//27
, 30, 70, 110,150,190,230,270,310,350,390		//37
, 30, 70, 110,150,190,230,270,310,350,390		//47
, 30,                                 390 };

//初期位置(y座標)
static double first_y[50] = { 80, 80, 80, 80
,110,110,110,110,110,110
,140,140,140,140,140,140,140,140
,170,170,170,170,170,170,170,170,170,170
,200,200,200,200,200,200,200,200,200,200
,230,230,230,230,230,230,230,230,230,230
,80,80 };

/***************************************
関数名:Enemy_Init
引数 :なし
戻り値:なし
機能 :初期化関数
***************************************/
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
		enemy[i].anime2 = 0;
		enemy[i].anime_cnt = 0;
		enemy[i].mode = NONE;
		enemy[i].A_Mode = NONE;
		enemy[i].onActive = Draw_ON;
		enemy[1].onActive = Breaken;
		enemy[2].onActive = Breaken;

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
	cntRed = 0;

	for (i = 0; i < NUMSHOT; i++) {

		enemy_shot[i].x = 10;
		enemy_shot[i].y = 310;
		enemy_shot[i].onActive = false;

	}

	for (i = 0; i < 4; i++) {
		if (enemy[i].onActive == Draw_ON) {
			cntYellow++;
		}
	}

	for (i = 0; i < 4; i++) {

		switch (i) {
		case 0:
			point[i].basis_x = CENTER_X - 10;
			point[i].basis_y = 0;
			point[i].vct = RIGHT;
			point[i].deg = 0;
			point[i].vct_x = 0;
			point[i].vct_y = 0;
			point[i].x = 0;
			point[i].y = 0;
			break;
		case 1:
			point[i].basis_x = CENTER_X - 10;
			point[i].basis_y = CENTER_Y / 2;
			point[i].vct = LEFT;
			point[i].deg = 0;
			point[i].vct_x = 0;
			point[i].vct_y = 0;
			point[i].x = 0;
			point[i].y = 0;
			break;
		case 2:
			point[i].basis_x = CENTER_X - 10;
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
			point[i].remit_x = 100;
			break;
		}

	}

	speed = 1;

	Enemy_Hit_Flg = false;

	SRand(GetDateTime(&Date));

	e_score = 0;

	return 0;
}

/***************************************
関数名:Enemy_Move
引数 :なし
戻り値:なし
機能 :Enemyの動きを操作する。
　　　各関数はここで呼びだす。
   ***************************************/
int Enemy_Move() {

	//プレイヤーの座標受け取り(真ん中)
	epx = Player_Pos_Init_x();
	epy = Player_Pos_Init_y();

	Enemy_POINT();

	Enemy_Control();

	Cnt_Yellow();
	Cnt_Red();
	Cnt_Pourple();
	Cnt_Blue();

	//左右移動
	if ((enemy[49].x > 680.0 || enemy[48].x < 10.0)) {
		speed *= -1;
	}

	for (i = 0; i < EnemyCount + 2; i++) {

		//常に左右移動
		enemy[i].fx += speed;

		//ここで動く敵の順番を選択
		timer--;
		if (timer < 0) {
			timer = (GetRand(4) * 2000) + 4000;
			Enemy_Attack_Chose();
		}
		if (enemy[i].onActive == Draw_ON) {
			switch (enemy[i].mode) {

			case NONE:
				enemy[i].x += speed;
				break;

			case ATTACK:
				if (enemy[i].A_Mode == NONE || enemy[i].A_Mode == BACK) {
					enemy[i].A_Mode = FIRST;
				}

				Enemy_Satellite(i);
				Enemy_Attack_Move(i);
				break;

			case MOVE:
				enemy[i].y += 1;
				enemy[i].x += speed;
				Enemy_Satellite(i);

				if (enemy[i].mode == MOVE && enemy[i].y == enemy[i].fy) {
					enemy[i].mode = NONE;
					enemy[i].A_Mode = NONE;
				}
				break;
			}
		}

		if (epx - 9 <= enemy[i].x + 20 && epx + 18 >= enemy[i].x - 10 &&
			epy - 17 <= enemy[i].y + 20 && epy + 15 >= enemy[i].y - 10 &&
			enemy[i].onActive == Draw_ON && Enemy_Hit_Flg == false) {
			Enemy_Hit_Flg = true;
			enemy[i].onActive = Draw_Anime;
		}

		cntYellow = 0;
		for (j = 0; j < 4; j++) {
			if (enemy[j].onActive == Draw_ON) {
				cntYellow++;
			}
		}
	}
	Create_Blow();

	EnemyShot_Mgr();

	Enemy_Stage_Clear();
	return 0;
}

/***************************************
関数名:Enemy_Control
引数 :なし
戻り値:なし
機能 :Enemyの左右の動きの切り返し部分を操作する。
　　　端のEnemyがすべて倒されると横に動く
   　　　 表示上の敵で切り返す
	   ***************************************/
int Enemy_Control() {
	if (enemy[18].onActive == Draw_OFF && enemy[28].onActive == Draw_OFF && enemy[38].onActive == Draw_OFF) {
		enemy[48].x = enemy[38].fx;
	}
	if (enemy[19].onActive == Draw_OFF && enemy[29].onActive == Draw_OFF && enemy[39].onActive == Draw_OFF && enemy[10].onActive == Draw_OFF) {
		enemy[48].x = enemy[39].fx;
	}
	if (enemy[20].onActive == Draw_OFF && enemy[30].onActive == Draw_OFF && enemy[40].onActive == Draw_OFF && enemy[11].onActive == Draw_OFF && enemy[4].onActive == Draw_OFF) {
		enemy[48].x = enemy[40].fx;
	}
	if (enemy[21].onActive == Draw_OFF && enemy[31].onActive == Draw_OFF && enemy[41].onActive == Draw_OFF && enemy[12].onActive == Draw_OFF && enemy[5].onActive == Draw_OFF) {
		enemy[48].x = enemy[41].fx;
	}
	if (enemy[22].onActive == Draw_OFF && enemy[32].onActive == Draw_OFF && enemy[42].onActive == Draw_OFF && enemy[13].onActive == Draw_OFF && enemy[6].onActive == Draw_OFF) {
		enemy[48].x = enemy[42].fx;
	}
	if (enemy[23].onActive == Draw_OFF && enemy[33].onActive == Draw_OFF && enemy[43].onActive == Draw_OFF && enemy[14].onActive == Draw_OFF && enemy[7].onActive == Draw_OFF) {
		enemy[48].x = enemy[43].fx;
	}

	if (enemy[27].onActive == Draw_OFF && enemy[37].onActive == Draw_OFF && enemy[47].onActive == Draw_OFF) {
		enemy[49].x = enemy[47].fx;
	}
	if (enemy[26].onActive == Draw_OFF && enemy[36].onActive == Draw_OFF && enemy[46].onActive == Draw_OFF && enemy[17].onActive == Draw_OFF) {
		enemy[49].x = enemy[46].fx;
	}
	if (enemy[25].onActive == Draw_OFF && enemy[35].onActive == Draw_OFF && enemy[45].onActive == Draw_OFF && enemy[16].onActive == Draw_OFF && enemy[9].onActive == Draw_OFF) {
		enemy[49].x = enemy[45].fx;
	}
	if (enemy[24].onActive == Draw_OFF && enemy[34].onActive == Draw_OFF && enemy[44].onActive == Draw_OFF && enemy[15].onActive == Draw_OFF && enemy[8].onActive == Draw_OFF) {
		enemy[49].x = enemy[44].fx;
	}
	if (enemy[23].onActive == Draw_OFF && enemy[33].onActive == Draw_OFF && enemy[43].onActive == Draw_OFF && enemy[14].onActive == Draw_OFF && enemy[7].onActive == Draw_OFF) {
		enemy[49].x = enemy[42].fx;
	}
	if (enemy[22].onActive == Draw_OFF && enemy[32].onActive == Draw_OFF && enemy[42].onActive == Draw_OFF && enemy[13].onActive == Draw_OFF && enemy[6].onActive == Draw_OFF) {
		enemy[49].x = enemy[41].fx;
	}
	return 0;
}

/***************************************
関数名:Enemy_Move_Flg
引数 :n (動いた黄色の添え字)
戻り値:なし
機能 :黄色が動いた時に赤も一緒に動かす
***************************************/
int Enemy_Move_Flg(int num) {

	if (num < 0)return 0;

	int Red = 0;

	enemy[num].mode = ATTACK;

	for (j = num + 4; j < num + 7; j++) {
		if (enemy[j].onActive == Draw_ON) {
			SetGax_Sound(4);
			enemy[j].mode = ATTACK;
			Red++;
		}
		if (Red >= 2) {
			Red = 0;
			break;
		}
	}
	return 0;
}

/***************************************
関数名:Enemy_Chose
引数 :なし
戻り値:なし
機能 :どの敵が動くか、選択する。
　　　黄色が動いたときのみ、Enemy_Move_Flgを呼び出す。
   　　　 選び方は、4種類の配列の中身(優先度をつけた)から
	   　 出していく。
		 ***************************************/
int Enemy_Attack_Chose() {

	//動き方の選択
	int Attack_Mode = GetRand(2) + 1;

	int Number = 25;

	//敵が攻撃をした回数を数える
	cntAttack++;
	if (cntAttack >= 20) {
		cntAttack = 0;
	}

	Number = Number - cntAttack;
	if (Number < 20)Number = 20;
	//もし、乱数n(20～140)のあまり算が0の時、黄色を動かす。
	if (GetRand(Number) == 0) {
		switch (cntYellow) {

		case 1:
			if (epx < enemy[32].fx - 20 || enemy[0].onActive == Draw_OFF) {
				n = 3;
			}
			else {
				n = 0;
			}
		case 2:
			if (epx < enemy[32].fx - 20 || enemy[3].onActive == Draw_OFF) {
				n = 0;
			}
			else {
				n = 3;
			}
			break;
		case 3:
			if (epx < enemy[32].fx - 20) {
				if (enemy[0].onActive == Draw_OFF) {
					n = 3;
				}
				if (enemy[3].onActive == Draw_OFF) {
					n = 0;
				}
				if (enemy[0].onActive == Draw_OFF && enemy[3].onActive == Draw_OFF) {
					n = 1;
				}
			}
			else {
				if (enemy[3].onActive == Draw_OFF) {
					n = 0;
				}
				if (enemy[0].onActive == Draw_OFF) {
					n = 3;
				}
				if (enemy[3].onActive == Draw_OFF && enemy[0].onActive == Draw_OFF) {
					n = 1;
				}
			}
			break;
		case 4:
			if (epx < enemy[32].fx - 20) {
				if (enemy[0].onActive == Draw_OFF) {
					n = 3;
				}
				if (enemy[3].onActive == Draw_OFF) {
					n = 0;
				}
				if (enemy[0].onActive == Draw_OFF && enemy[3].onActive == Draw_OFF && enemy[2].onActive == Draw_OFF) {
					n = 1;
				}
				if (enemy[0].onActive == Draw_OFF && enemy[3].onActive == Draw_OFF && enemy[1].onActive == Draw_OFF) {
					n = 2;
				}
			}
			else {
				if (enemy[3].onActive == Draw_OFF) {
					n = 0;
				}
				if (enemy[0].onActive == Draw_OFF) {
					n = 3;
				}
				if (enemy[0].onActive == Draw_OFF && enemy[3].onActive == Draw_OFF && enemy[1].onActive == Draw_OFF) {
					n = 2;
				}
				if (enemy[0].onActive == Draw_OFF && enemy[3].onActive == Draw_OFF && enemy[2].onActive == Draw_OFF) {
					n = 1;
				}
			}
			break;
		default:
			n = -1;
			break;
		}
		Enemy_Move_Flg(n);
		return 0;
	}
	//敵の中心点がプレイヤーの右側なら
	if ((enemy[48].x + enemy[49].x) / 2 > epx) {
		switch (Attack_Mode) {
		case MODE_DOWN:
			for (j = 0; j < EnemyCount; j++) {
				if (enemy[Chose_1[j]].mode == NONE && enemy[Chose_1[j]].onActive == Draw_ON) {
					if (enemy[Chose_1[j]].Type == RED && cntYellow == 0)continue;
					enemy[Chose_1[j]].mode = ATTACK;
					break;
				}
			}
			break;
		case MODE_NEXT:
			for (j = 0; j < EnemyCount; j++) {
				if (enemy[Chose_3[j]].mode == NONE && enemy[Chose_3[j]].onActive == Draw_ON) {
					if (enemy[Chose_3[j]].Type == RED && cntYellow == 0)continue;
					enemy[Chose_3[j]].mode = ATTACK;
					break;
				}
			}
			break;
		}
	}
	else {
		switch (Attack_Mode) {
		case MODE_DOWN:
			for (j = 0; j < EnemyCount; j++) {
				if (enemy[Chose_2[j]].mode == NONE && enemy[Chose_2[j]].onActive == Draw_ON) {
					if (enemy[Chose_2[j]].Type == RED && cntYellow == 0)continue;
					enemy[Chose_2[j]].mode = ATTACK;
					break;
				}
			}
			break;
		case MODE_NEXT:
			for (j = 0; j < EnemyCount; j++) {
				if (enemy[Chose_4[j]].mode == NONE && enemy[Chose_4[j]].onActive == Draw_ON) {
					if (enemy[Chose_4[j]].Type == RED && cntYellow == 0)continue;
					enemy[Chose_4[j]].mode = ATTACK;
					break;
				}
			}
			break;
		}
	}

	return 0;
}

/***************************************
関数名:Enemy_Attack_Move
引数 :Enemyの添え字
戻り値:なし
機能 :enemyが攻撃するときに呼び出される。
　　　最初は円運動からの目標点に向かって動く。
   　　　黄色が逃げるのは未実装。
	  ***************************************/
int Enemy_Attack_Move(int num) {

	if (EnemyCount > num && enemy[num].onActive == Draw_ON) {
		switch (enemy[num].A_Mode) {
		case NONE:
			break;
		case FIRST:
			if (enemy[num].x >= CENTER_X) {
				enemy[num].pt_x = enemy[num].x + 25;
				enemy[num].pt_y = enemy[num].y - 25;
				enemy[num].A_Mode = R_ROLL;
			}
			if (enemy[num].x < CENTER_X) {
				enemy[num].pt_x = enemy[num].x - 25;
				enemy[num].pt_y = enemy[num].y - 25;
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

			if (enemy[num].pt_x > epx + 200) {
				P_Count[num] = 1;
			}
			else if (enemy[num].pt_x > epx - 200) {
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

		//一定範囲にいたら、中心点が移動する。
		//pow(enemyの半径 + 目標点の半径, 2)
		if (pow(16 + 120, 2) >= pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2) &&
			pow(16 + 45, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			enemy[num].A_Mode = CHANGE;
		}

		//一定範囲外なら、中心点に向かって移動する。
		if (pow(16 + 50, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			enemy[num].A_Mode = TRACK;
		}

		//円の周りを回す場合
		//一定範囲内なら
		if (pow(16 + 45, 2) >= pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			if (enemy[num].A_Mode != L_ROLL && enemy[num].x >= CENTER_X) {
				if (enemy[num].A_Mode != R_ROLL) {

					enemy[num].deg = atan2(enemy[num].y + 60, 0);

				}
				enemy[num].A_Mode = R_ROLL;
			}
			if (enemy[num].A_Mode != R_ROLL && enemy[num].x < CENTER_X) {
				if (enemy[num].A_Mode != L_ROLL) {

					enemy[num].deg = atan2(enemy[num].y + 60, 0);

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


		//画面外に行ったら、目標点更新
		if (enemy[num].x < 5) {
			enemy[num].A_Mode = CHANGE;
			P_Count[num] = 3;
			enemy[num].x += 2;
		}
		if (enemy[num].x > 685) {
			enemy[num].A_Mode = CHANGE;
			P_Count[num] = 3;
			enemy[num].x -= 2;
		}
		//画面下に行ったときの処理
		if (enemy[num].y > 730) {
			enemy[num].y = -10;
			enemy[num].x = enemy[num].fx;
			enemy[num].mode = MOVE;
			enemy[num].A_Mode = BACK;
			enemy_satellite[num].x = enemy[num].fx;
			enemy_satellite[num].y = enemy[num].fy;
			P_Count[num] = 0;
			enemy[num].pt_y = 0;
			enemy[num].pt_x = 0;
			switch (enemy[num].Type) {
			case YELLOW:
				enemy[num].anime = 0;
				break;
			case RED:
				enemy[num].anime = 8;
				break;
			case PURPLE:
				enemy[num].anime = 16;
				break;
			case BLUE:
				enemy[num].anime = 24;
				break;
			}
		}
	}
	return 0;
}

/***************************************
関数名:Enemy_POINT
引数 :なし
戻り値:なし
機能 :enemyの目標点をどこに置くかに使用
　　　4つの点があり、
   　　　1つ目は、全体で円弧を描き2,3,4番目のどこに点を置くか決める。
	  　 2,3つ目は、画面左右で扇状(？)に円弧を作る。
		4つ目は、プレイヤーの下に線で動く
		***************************************/
int Enemy_POINT() {

	for (int j = 0; j < 4; j++) {

		if (j != 3) {

			if (point[j].y <= point[j].basis_y + 100) {
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
			point[j].y = point[j].basis_y + 400;
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

/***************************************
関数名:Enemy_Satellite
引数 :enemyの添え字
戻り値:なし
機能 :enemyの最初の回転と最後の回転を出すのに使う
　　　Satelliteは衛星の意。
   ***************************************/
int Enemy_Satellite(int num) {
	switch (enemy[num].A_Mode) {
	case FIRST:
		enemy_satellite[num].rad = 240;
		enemy_satellite[num].deg = enemy_satellite[num].rad * PI / 180.0;
		break;
	case R_ROLL:
		enemy_satellite[num].deg += 0.017;

		enemy_satellite[num].vct_x = 40 * cos(enemy_satellite[num].deg);
		enemy_satellite[num].vct_y = 40 * sin(enemy_satellite[num].deg);

		enemy_satellite[num].x = enemy[num].pt_x + enemy_satellite[num].vct_x;
		enemy_satellite[num].y = enemy[num].pt_y + enemy_satellite[num].vct_y;
		break;
	case L_ROLL:
		enemy_satellite[num].deg -= 0.017;

		enemy_satellite[num].vct_x = 40 * cos(enemy_satellite[num].deg);
		enemy_satellite[num].vct_y = 40 * sin(enemy_satellite[num].deg);

		enemy_satellite[num].x = enemy[num].pt_x + enemy_satellite[num].vct_x;
		enemy_satellite[num].y = enemy[num].pt_y + enemy_satellite[num].vct_y;
		break;
	case BACK:
		enemy_satellite[num].x = enemy[num].fx - 10;
		enemy_satellite[num].y = enemy[num].fy - 20;
		break;
	}
	return 0;
}

/***************************************
関数名:EnemyShot_Mgr
引数 :なし
戻り値:なし
機能 :敵の弾の管理を行う
　　　発射と整理をし、各関数を呼び出す。
   ***************************************/
int EnemyShot_Mgr() {

	for (int l = 0; l < EnemyCount; l++) {
		if (enemy[l].onActive == Draw_ON) {
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
		for (int m = l; m < NUMSHOT; m++) {
			if (tmpEnemyShot[l].onActive == true && enemy_shot[m].onActive == false) {
				enemy_shot[m].onActive = tmpEnemyShot[l].onActive;
				tmpEnemyShot[l].onActive = false;

				enemy_shot[m].x = tmpEnemyShot[l].x;

				enemy_shot[m].y = tmpEnemyShot[l].y;
			}
		}
	}

	EnemyShot_Move();

	EnemyShot_Draw();

	return 0;
}

/***************************************
関数名:EnemyShot_Move
引数 :なし
戻り値:なし
機能 :敵の弾を動かす。
　　　画面外に行くと表示を消す。
   　スコアの呼び出しをここで行う
	***************************************/
int EnemyShot_Move() {

	for (j = 0; j < NUMSHOT; j++) {
		enemy_shot[j].y += 5;

		if (enemy_shot[j].y >= 820) {
			enemy_shot[j].onActive = false;
		}

	}

	for (int j = 0; j < EnemyCount; j++) {
		if (enemy[j].onActive == Draw_ON) {
			enemy[j].onActive = Player_HIT(j);
		}
		if (enemy[j].onActive == Draw_OFF) {
			cntBlow++;
			if (cntBlow > REMITBLOW)cntBlow = 0;
			PUSH_BLOW(cntBlow, enemy[j].x, enemy[j].y);
		}
		Enemy_Score(j);
	}

	return 0;
}

/***************************************
関数名:Enemy_Score
引数 :破壊されたEnemyの添え字
戻り値:e_Score
機能 :破壊されたEnemyのスコアは加算する。
　　　Enemy_State_Initを呼び出し、
   　 PlayerにEnemyの状態を渡す。
	 ***************************************/
int Enemy_Score(int killed) {
	if (enemy[killed].onActive == Draw_OFF) {
		if (enemy[killed].mode == NONE) {
			switch (enemy[killed].Type) {
			case 0:
				e_score += 60;
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
				e_score += 200;
				break;
			case 1:
				e_score += 100;
				break;
			case 2:
				e_score += 80;
				break;
			case 3:
				e_score += 60;
				break;
			}
		}
		enemy[killed].onActive = Breaken;
	}

	for (i = 0; i < EnemyCount; i++) {
		Enemy_State_Init(i);
	}

	return e_score;
}

//敵の弾の当たり判定
/***************************************
関数名:Enemy_Hit
引数 :なし
戻り値:なし
機能 :プレイヤーの当り判定
　　　Enemyの弾とEnemy自身に当たる。
   　 trueとfalseでPlayerに判定を送る
	 ***************************************/
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
		if (epx - 8 <= enemy[j].x + 20 && epx + 16 >= enemy[j].x - 10 &&
			epy - 17 <= enemy[j].y + 20 && epy + 15 >= enemy[j].y - 10 &&
			enemy[j].onActive == Draw_ON && Enemy_Hit_Flg == false) {
			Enemy_Hit_Flg = true;
			enemy[j].onActive = Draw_Anime;

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
		for (int m = l; m < REMITBLOW; m++) {
			if (tmpBlow[l].onActive == true && blow[m].onActive == false) {
				blow[m].onActive = tmpBlow[l].onActive;
				tmpBlow[l].onActive = false;

				blow[m].x = tmpBlow[l].x;

				blow[m].y = tmpBlow[l].y;
			}
		}
	}
	return 0;
}

//プレイヤーと敵の角度を出す
/*************************************************
関数名:Enemy_Deg
引数 :Enemyの添え字
戻り値:なし
機能 :EnemyとPlayerの角度を出す
　　　回転運動時のみ、Enemy_Satelliteを目標にする。
   *************************************************/
int Enemy_Deg(int num) {

	enemy[num].deg2 = atan2(epy - enemy[num].y, epx - enemy[num].x);
	if (enemy[num].mode == ATTACK && (enemy[num].A_Mode == R_ROLL || enemy[num].A_Mode == L_ROLL) ||
		enemy[num].mode == MOVE) {
		enemy[num].deg2 = atan2(enemy_satellite[num].y - enemy[num].y, enemy_satellite[num].x - enemy[num].x);
	}
	if (enemy[num].deg2 < 0) {
		enemy[num].deg2 = enemy[num].deg2 + 2 * PI;
	}
	enemy[num].deg2 = (enemy[num].deg2 * 360 / (2 * PI));

	switch (enemy[num].Type) {
	case 0:
		switch ((int)enemy[num].deg2 / 15) {
		case 0:
			enemy[i].anime2 = 5;
			break;
		case 1:
			enemy[i].anime2 = 4;
			break;
		case 2:
			enemy[i].anime2 = 3;
			break;
		case 3:
			enemy[i].anime2 = 2;
			break;
		case 4:
			enemy[i].anime2 = 1;
			break;
		case 5:
			enemy[i].anime2 = 0;
			break;
		case 6:
			enemy[i].anime2 = 0;
			break;
		case 7:
			enemy[i].anime2 = 1;
			break;
		case 8:
			enemy[i].anime2 = 2;
			break;
		case 9:
			enemy[i].anime2 = 3;
			break;
		case 10:
			enemy[i].anime2 = 4;
			break;
		case 11:
			enemy[i].anime2 = 5;
			break;
		case 12:
			enemy[i].anime2 = 5;
			break;
		case 13:
			enemy[i].anime2 = 4;
			break;
		case 14:
			enemy[i].anime2 = 3;
			break;
		case 15:
			enemy[i].anime2 = 2;
			break;
		case 16:
			enemy[i].anime2 = 1;
			break;
		case 17:
			enemy[i].anime2 = 0;
			break;
		case 18:
			enemy[i].anime2 = 0;
			break;
		case 19:
			enemy[i].anime2 = 1;
			break;
		case 20:
			enemy[i].anime2 = 2;
			break;
		case 21:
			enemy[i].anime2 = 3;
			break;
		case 22:
			enemy[i].anime2 = 4;
			break;
		case 23:
			enemy[i].anime2 = 5;
			break;
		}
		break;
	case 1:
		switch ((int)enemy[num].deg2 / 15) {
		case 0:
			enemy[i].anime2 = 13;
			break;
		case 1:
			enemy[i].anime2 = 12;
			break;
		case 2:
			enemy[i].anime2 = 11;
			break;
		case 3:
			enemy[i].anime2 = 10;
			break;
		case 4:
			enemy[i].anime2 = 9;
			break;
		case 5:
			enemy[i].anime2 = 8;
			break;
		case 6:
			enemy[i].anime2 = 8;
			break;
		case 7:
			enemy[i].anime2 = 9;
			break;
		case 8:
			enemy[i].anime2 = 10;
			break;
		case 9:
			enemy[i].anime2 = 11;
			break;
		case 10:
			enemy[i].anime2 = 12;
			break;
		case 11:
			enemy[i].anime2 = 13;
			break;
		case 12:
			enemy[i].anime2 = 13;
			break;
		case 13:
			enemy[i].anime2 = 12;
			break;
		case 14:
			enemy[i].anime2 = 11;
			break;
		case 15:
			enemy[i].anime2 = 10;
			break;
		case 16:
			enemy[i].anime2 = 9;
			break;
		case 17:
			enemy[i].anime2 = 8;
			break;
		case 18:
			enemy[i].anime2 = 8;
			break;
		case 19:
			enemy[i].anime2 = 9;
			break;
		case 20:
			enemy[i].anime2 = 10;
			break;
		case 21:
			enemy[i].anime2 = 11;
			break;
		case 22:
			enemy[i].anime2 = 12;
			break;
		case 23:
			enemy[i].anime2 = 13;
			break;
		}
		break;
	case 2:
		switch ((int)enemy[num].deg2 / 15) {
		case 0:
			enemy[i].anime2 = 21;
			break;
		case 1:
			enemy[i].anime2 = 20;
			break;
		case 2:
			enemy[i].anime2 = 19;
			break;
		case 3:
			enemy[i].anime2 = 18;
			break;
		case 4:
			enemy[i].anime2 = 17;
			break;
		case 5:
			enemy[i].anime2 = 16;
			break;
		case 6:
			enemy[i].anime2 = 16;
			break;
		case 7:
			enemy[i].anime2 = 17;
			break;
		case 8:
			enemy[i].anime2 = 18;
			break;
		case 9:
			enemy[i].anime2 = 19;
			break;
		case 10:
			enemy[i].anime2 = 20;
			break;
		case 11:
			enemy[i].anime2 = 21;
			break;
		case 12:
			enemy[i].anime2 = 21;
			break;
		case 13:
			enemy[i].anime2 = 20;
			break;
		case 14:
			enemy[i].anime2 = 19;
			break;
		case 15:
			enemy[i].anime2 = 18;
			break;
		case 16:
			enemy[i].anime2 = 17;
			break;
		case 17:
			enemy[i].anime2 = 16;
			break;
		case 18:
			enemy[i].anime2 = 16;
			break;
		case 19:
			enemy[i].anime2 = 17;
			break;
		case 20:
			enemy[i].anime2 = 18;
			break;
		case 21:
			enemy[i].anime2 = 19;
			break;
		case 22:
			enemy[i].anime2 = 20;
			break;
		case 23:
			enemy[i].anime2 = 21;
			break;
		}
		break;
	case 3:
		switch ((int)enemy[num].deg2 / 15) {
		case 0:
			enemy[i].anime2 = 29;
			break;
		case 1:
			enemy[i].anime2 = 28;
			break;
		case 2:
			enemy[i].anime2 = 27;
			break;
		case 3:
			enemy[i].anime2 = 26;
			break;
		case 4:
			enemy[i].anime2 = 25;
			break;
		case 5:
			enemy[i].anime2 = 24;
			break;
		case 6:
			enemy[i].anime2 = 24;
			break;
		case 7:
			enemy[i].anime2 = 25;
			break;
		case 8:
			enemy[i].anime2 = 26;
			break;
		case 9:
			enemy[i].anime2 = 27;
			break;
		case 10:
			enemy[i].anime2 = 28;
			break;
		case 11:
			enemy[i].anime2 = 29;
			break;
		case 12:
			enemy[i].anime2 = 29;
			break;
		case 13:
			enemy[i].anime2 = 28;
			break;
		case 14:
			enemy[i].anime2 = 27;
			break;
		case 15:
			enemy[i].anime2 = 26;
			break;
		case 16:
			enemy[i].anime2 = 25;
			break;
		case 17:
			enemy[i].anime2 = 24;
			break;
		case 18:
			enemy[i].anime2 = 24;
			break;
		case 19:
			enemy[i].anime2 = 25;
			break;
		case 20:
			enemy[i].anime2 = 26;
			break;
		case 21:
			enemy[i].anime2 = 27;
			break;
		case 22:
			enemy[i].anime2 = 28;
			break;
		case 23:
			enemy[i].anime2 = 29;
			break;
		}
		break;
	}
	return 0;
}
/**********************************************
関数名:Cnt_Yellow
引数 :なし
戻り値:なし
機能 :黄色の敵を数える
***********************************************/
int Cnt_Yellow() {
	cntYellow = 0;
	for (i = 0; i < 4; i++) {
		if (enemy[i].onActive == Draw_ON)cntYellow++;
	}
	return 0;
}

/**********************************************
関数名:Cnt_Red
引数 :なし
戻り値:なし
機能 :赤色の敵を数える
***********************************************/
int Cnt_Red() {
	cntRed = 0;
	for (i = 4; i < 10; i++) {
		if (enemy[i].onActive == Draw_ON)cntRed++;
	}
	return 0;
}

/**********************************************
関数名:Cnt_Pourple
引数 :なし
戻り値:なし
機能 :紫色の敵を数える
***********************************************/
int Cnt_Pourple() {
	cntPourple = 0;
	for (i = 10; i < 18; i++) {
		if (enemy[i].onActive == Draw_ON)cntPourple++;
	}
	return 0;
}

/**********************************************
関数名:Cnt_Blue
引数 :なし
戻り値:なし
機能 :青色の敵を数える
***********************************************/
int Cnt_Blue() {
	cntBlue = 0;
	for (i = 18; i < 48; i++) {
		if (enemy[i].onActive == Draw_ON)cntBlue++;
	}
	return 0;
}


//Enemyのアニメーション
/***************************************
関数名:Enemy_Animetion
引数 :Enemyの添え字
戻り値:なし
機能 :通常の左右移動時のアニメーションを作る。
***************************************/
int Enemy_Animetion(int num) {
	enemy[num].anime_cnt++;
	if (enemy[num].anime_cnt / 70 > 3)enemy[num].anime_cnt = 0;
	switch (enemy[num].anime_cnt / 70) {
	case 0:
	case 2:
		switch (enemy[num].Type) {
		case YELLOW:
			enemy[num].anime = 0;
			break;
		case RED:
			enemy[num].anime = 8;
			break;
		case PURPLE:
			enemy[num].anime = 16;
			break;
		case BLUE:
			enemy[num].anime = 24;
			break;
		}
		break;
	case 1:
		switch (enemy[num].Type) {
		case YELLOW:
			enemy[num].anime = 0;
			break;
		case RED:
			enemy[num].anime = 14;
			break;
		case PURPLE:
			enemy[num].anime = 22;
			break;
		case BLUE:
			enemy[num].anime = 30;
			break;
		}
		break;
	case 3:
		switch (enemy[num].Type) {
		case YELLOW:
			enemy[num].anime = 0;
			break;
		case RED:
			enemy[num].anime = 15;
			break;
		case PURPLE:
			enemy[num].anime = 23;
			break;
		case BLUE:
			enemy[num].anime = 31;
			break;
		}
		break;
	}
	return 0;
}

/***************************************
関数名:Enemy_Draw
引数 :なし
戻り値:なし
機能 :Enemyの表示をする。
***************************************/
int Enemy_Draw() {

	for (i = 0; i < EnemyCount; i++) {

		Enemy_Animetion(i);
		if (enemy[i].mode == ATTACK || (enemy[i].mode == MOVE)) {
			continue;
		}
		switch (enemy[i].onActive) {
		case Draw_ON:
			DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime], true, 0, 0);
			break;
		case Draw_OFF:
		case Draw_Anime:
		case Breaken:
			break;
		}
	}
	for (i = 0; i < EnemyCount; i++) {
		if (enemy[i].mode != ATTACK && enemy[i].mode != MOVE) {
			continue;
		}
		switch (enemy[i].onActive) {
		case Draw_ON:

			Enemy_Deg(i);
			if (enemy[i].deg2 / 15 >= 0 && enemy[i].deg2 / 15 < 7) {
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime2], true, false, true);
			}
			if (enemy[i].deg2 / 15 >= 7 && enemy[i].deg2 / 15 < 13) {
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime2], true, true, true);
			}
			if (enemy[i].deg2 / 15 >= 13 && enemy[i].deg2 / 15 < 19) {
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime2], true, true, false);
			}
			if (enemy[i].deg2 / 15 >= 19 && enemy[i].deg2 / 15 < 25) {
				DrawRotaGraph(enemy[i].x, enemy[i].y, 2.5, 0, Enemy_Handle[enemy[i].anime2], true, false, false);
			}
			break;
		case Draw_OFF:
		case Draw_Anime:
		case Breaken:
			break;
		}
	}

	return 0;
}

/***************************************
関数名:EnemyShot_Draw
引数 :なし
戻り値:なし
機能 :Enemyの弾と爆発の表示をする。
***************************************/
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
	DrawFormatString(205, 40, GetColor(255, 0, 0), "%d", e_score);
	DrawFormatString(455, 40, GetColor(255, 0, 0), "%d", e_score);
	return 0;
}

/***************************************
関数名:Enemy_Stage_Clear
引数 :なし
戻り値:なし
機能 :Enemyがすべて破壊されると
　　　ステージクリア
   ***************************************/
int Enemy_Stage_Clear() {

	//まだ撃破されてなかったら、returnで-1を返す。
	for (i = 0; i < EnemyCount; i++) {
		if (enemy[i].onActive == Draw_ON) {
			return -1;
		}
	}
	Scene_Mgr_ChangeScene(E_Scene_Result);

	//黄色以外が全部撃破されてたら…
	Cnt_Yellow();

	//黄色が2体以上残ってる状態でクリアしたら、二体分引き継ぐ
	if (cntYellow >= 2)cntYellow = 2;

	return cntYellow;
}

/***************************************
関数名:Enemy_Pos_Init_x
引数 :Enemyの添え字
戻り値:Enemyのx座標
機能 :Enemyのx座標を渡す
***************************************/
int Enemy_Pos_Init_x(int num) {
	return enemy[num].x;
}

/***************************************
関数名:Enemy_Pos_Init_y
引数 :Enemyの添え字
戻り値:Enemyのy座標
機能 :Enemyのy座標を渡す
***************************************/
int Enemy_Pos_Init_y(int num) {
	return enemy[num].y;
}

/***************************************
関数名:Enemy_State_Init
引数 :Enemyの添え字
戻り値:Enemyの状態
機能 :Enemyの状態を渡す
***************************************/
int Enemy_State_Init(int num) {
	return enemy[num].onActive;
}

/***************************************
関数名:Enemy_End
引数 :なし
戻り値:なし
機能 :Enemyの終了？
***************************************/
int Enemy_End() {
	return 0;
}