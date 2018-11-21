#include"DxLib.h"
#include"Enemy.h"
#include<Math.h>
#include"EnemyShot.h"
/********************  変数宣言  ****************************/

P_Enemy enemy[50];

A_Enemy attack_enemy[50];

//debug用 
unsigned int Color;
double ex = 0;
double ey = 0;
double efx = 0;
double efy = 0;
double enx = 0;
double eny = 0;
double cnt = 0;
int a = 0;
int b = 0;
int c = 0;


//ループ用
static int i, j, k;

//角度
int e_deg;

//敵の移動スピード
double speed=1;
double n_speed = 1;

//Enemyの攻撃に移るまでのタイマー
double timer = 4000;

//行動カウント
int cntEnemy = 0;

//プレイヤーの位置情報格納用
double px;
double py;

int Enemy_Handle[40];

//初期位置(x座標)
static double first_x[50] = {                190,230,270,310					//3
                                       , 150,190,230,270,310,350				//9
                                  , 110, 150,190,230,270,310,350,390			//17
                              , 70, 110, 150,190,230,270,310,350,390,430		//27
                              , 70, 110, 150,190,230,270,310,350,390,430		//37
                              , 70, 110, 150,190,230,270,310,350,390,430		//47
	                          , 70, 430 }; 

//初期位置(y座標)
static double first_y[50] = {			    30, 30, 30, 30
									  , 60, 60, 60, 60, 60, 60
								  , 90, 90, 90, 90, 90, 90, 90, 90
							  ,120,120,120,120,120,120,120,120,120,120
							  ,150,150,150,150,150,150,150,150,150,150
							  ,180,180,180,180,180,180,180,180,180,180
							  ,30,30};

static int priority_L[19] = {	//左側の敵攻撃優先度
	18,28,38,10,19,29,39,11,20,30,40,12,21,31,41,13,22,32,42
};

static int priority_R[19] = {	//右側の敵攻撃優先度
	27,37,47,17,26,36,46,16,25,35,45,15,24,34,44,14,23,33,43
};

int Enemy_Init() {
    //画像読み込み
	LoadDivBmpToGraph("Image/Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle,true, false);

	for (i = 0; i < 50; i++) {
		enemy[i].fx = first_x[i]+400;
		enemy[i].fy = first_y[i]+50;
		enemy[i].nx = enemy[i].fx - 180;
		enemy[i].ny = enemy[i].fy;
		enemy[i].x = enemy[i].fx;
		enemy[i].y = enemy[i].fy;
		enemy[i].Move_Flg = false;
		enemy[i].Attack_Move_Flg = false;
		enemy[i].Draw_Flg = true;
		enemy[1].Draw_Flg = false;
		enemy[2].Draw_Flg = false;
		enemy[i].deg = 0;
		if (i < 4) {
			enemy[i].Type = 0;
			enemy[i].anime = 0;
		}
		else if(i < 10) {
			enemy[i].Type = 1;
			enemy[i].anime = 8;
		}
		else if (i < 18) {
			enemy[i].Type = 2;
			enemy[i].anime = 16;
		}
		else {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
		}
		attack_enemy[i].timer = 300;
		attack_enemy[i].enemyshot = false;
		enemy[27].nx = enemy[27].fx - 406;
		enemy[37].nx = enemy[37].fx - 276; //130
	}

	//px = Player_Pos_Init_x;
	//py = Player_Pos_Init_y;

	px = 300;  //debug
	py = 400;  //degug

	return 0;
}

int Enemy_Move() {
	//一列文移動するまでのデータ
	if (enemy[27].y == enemy[27].fy/*enemy[27].Move_Flg == true && enemy[27].fy == enemy[27].y*/) {
		efx = enemy[27].fx;
		efy = enemy[27].fy;
		ex = enemy[27].x;
		ey = enemy[27].y;
		enx = enemy[27].nx;
		eny = enemy[27].ny;
		//enemy[27].Attack_Move_Flg = false;
		//enemy[27].Move_Flg = false;
		cnt = 0;
	}
	if (enemy[37].y == enemy[37].fy/*enemy[37].Move_Flg == true && enemy[37].fy == enemy[37].y*/) {
		b = enemy[37].fx;
		a = enemy[37].x;
		c = enemy[37].nx;
		//enemy[37].Attack_Move_Flg = false;
		//enemy[37].Move_Flg = false;
	}


	//左右移動
	if ((enemy[49].x > 1080.0 || enemy[48].x < 200.0)) {
		speed *= -1;
	}	
	//左右移動
	if ((enemy[49].nx > 1080.0 || enemy[48].nx < 200.0)) {
		n_speed *= -1;
	}
	
	px += speed * 5; //debug

	for (i = 0; i < 50; i++) {

		//敵のモーションタイマー
		timer--;
		if (timer <= 0 && cnt ==0) {//タイマーがゼロになったら、元に戻す
			timer = 4000;
			cntEnemy++;

			if (cntEnemy == 5) {
				enemy[0].Attack_Move_Flg = true;
				enemy[0].Move_Flg = true;
			}
			else if (px > 320) { //プレイヤーが画面の右側にいた場合

				for(j=0;j<19;j++){
					if (enemy[priority_R[j]].Attack_Move_Flg == false&& enemy[priority_R[j]].Move_Flg == false) {	//見たところがfalseだったら
						enemy[priority_R[j]].Attack_Move_Flg = true;		//そこをtrueにして、ループを抜ける
						enemy[priority_R[j]].Move_Flg = true;
						break;
					}
				}
			}
			else {
				if (enemy[27].Move_Flg == false && enemy[27].Attack_Move_Flg == false &&
					enemy[37].Move_Flg == false && enemy[37].Attack_Move_Flg == false) {
					enemy[27].Move_Flg = true;
					enemy[27].Attack_Move_Flg = true;
					enemy[37].Move_Flg = true;
					enemy[37].Attack_Move_Flg = true;
				}
				/*for (j = 0; j < 19; j++) {
					if (enemy[priority_L[j]].Attack_Move_Flg == false&& enemy[priority_L[j]].Move_Flg == false) {	//一つOnにして抜ける
						enemy[priority_L[j]].Attack_Move_Flg = true;
						enemy[priority_L[j]].Move_Flg = true;
						break;
					}
				}*/
			}
		}

		enemy[i].fx += speed;
		enemy[i].nx += n_speed;
		if (enemy[i].Move_Flg == false) { //攻撃時じゃないとき左右移動
			enemy[i].x += speed;
		}
		if (enemy[i].Move_Flg == true) {	//攻撃時の移動

			enemy[i].y += 1;	//下方向に向かって移動
			if (i != 48 && i != 49) {
				attack_enemy[i].timer--;	//攻撃のタイマー
			}
			if (attack_enemy[i].timer <= 0) {
				attack_enemy[i].timer = 40;
				attack_enemy[i].enemyshot = true;
			}

			if (enemy[i].Attack_Move_Flg == true) {
				//enemy[i].x += speed;
				//enemy[i].x += (0.003 * sin(enemy[i].x - px) + enemy[i].x - px)/500 ;
				enemy[i].x += pow((enemy[i].x - px )/300 , 5) / 500;
			}

			if (enemy[i].y >= 750) {
				enemy[i].y = -10;
				enemy[i].x = enemy[i].nx;
				enemy[i].Attack_Move_Flg = false;
			}

			//画面下から元の場所に戻ったとき //80ずれる
			if (enemy[i].Attack_Move_Flg == false
				/*&& (enemy[i].x == enemy[i].fx + 3 || enemy[i].x == enemy[i].fx-3)*/ && enemy[i].y == enemy[i].fy) {
				//一回転
				enemy[i].Move_Flg = false;
				enemy[i].deg += 15;
				if (enemy[i].deg >= 360) {
					enemy[i].deg = 0;
				}
			}

		}
	}
	return attack_enemy[i].enemyshot;
}

/*int Enemy_Attack() {

	bool Enemy_Shot_Flg = attack_enemy[i].enemyshot;

	return Enemy_Shot_Flg;
}*/

int Enemy_Draw() {

	Color = GetColor(255, 255, 255);
	DrawFormatString(0,  0, Color, " ex_27 = %.0lf", ex);
	DrawFormatString(0, 80, Color, "efx_27 = %.0lf", efx);
	DrawFormatString(0, 160, Color, "enx_27 = %.0lf", enx);
	DrawFormatString(120, 0, Color, "ex_37 = %d",a);
	DrawFormatString(120, 80, Color, "efx_37 = %d", b);
	DrawFormatString(120, 160, Color, "enx_37 = %d", c);


	for (i = 0; i < 48; i++) {
		e_deg = enemy[i].deg;
		e_deg = 0;
		/*if (e_deg % 90 == 0) {
			if (enemy[i].Type == 0)enemy[i].anime = 0;
			if (enemy[i].Type == 1)enemy[i].anime = 6;
			if (enemy[i].Type == 2)enemy[i].anime = 14;
			if (enemy[i].Type == 3)enemy[i].anime = 22;
		}
		if (e_deg % 90 == 15) {
			if (enemy[i].Type == 0)enemy[i].anime = 1;
			if (enemy[i].Type == 1)enemy[i].anime = 7;
			if (enemy[i].Type == 2)enemy[i].anime = 15;
			if (enemy[i].Type == 3)enemy[i].anime = 23;
		}
		if (e_deg % 90 == 30) {
			if (enemy[i].Type == 0)enemy[i].anime = 2;
			if (enemy[i].Type == 1)enemy[i].anime = 8;
			if (enemy[i].Type == 2)enemy[i].anime = 16;
			if (enemy[i].Type == 3)enemy[i].anime = 24;
		}
		if (e_deg % 90 == 45) {
			if (enemy[i].Type == 0)enemy[i].anime = 3;
			if (enemy[i].Type == 1)enemy[i].anime = 9;
			if (enemy[i].Type == 2)enemy[i].anime = 17;
			if (enemy[i].Type == 3)enemy[i].anime = 25;
		}if (e_deg % 90 == 60) {
			if (enemy[i].Type == 0)enemy[i].anime = 4;
			if (enemy[i].Type == 1)enemy[i].anime = 10;
			if (enemy[i].Type == 2)enemy[i].anime = 18;
			if (enemy[i].Type == 3)enemy[i].anime = 26;
		}if (e_deg % 90 == 75) {
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