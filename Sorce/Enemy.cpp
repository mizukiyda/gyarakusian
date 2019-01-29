#include"DxLib.h"
#include"Enemy.h"
#include"PlayerShot.h"
#include"Player.h"
#include<Math.h>
#include<time.h>
#include<stdlib.h>
#include"Sound.h"
#include "Scene_Mgr.h"

/********************  �ϐ��錾  ****************************/

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

//���[�v�p
static int i, j;

//Enemy_Move_Flg�ɓn���B�ǂ̉��F�͓��������n��
int n = 0;

//����Enemy
int ne;
//�E����c
int Chose_1[EnemyCount - 2] = { 27,37,47,17,26,36,46,9,16,25,35,45,8,15,24,34,44,7,14,23,33,43,6,12,22,32,42,5,12,21,31,41,4,11,20,30,40,10,19,29,39,18,28,38 };
//������c
int Chose_2[EnemyCount - 2] = { 18,28,38,10,19,29,39,4,11,20,30,40,5,12,21,31,41,6,13,22,32,42,7,14,23,33,43,8,15,24,34,44,9,16,25,35,45,17,26,36,46,27,37,47 };
//�E���牡
int Chose_3[EnemyCount - 2] = { 27,17,9,37,26,16,8,47,36,25,15,7,46,35,24,14,6,45,34,23,13,5,44,33,22,12,4,43,32,21,11,42,31,20,10,41,30,19,40,29,18,39,28,38 };
//�����牡
int Chose_4[EnemyCount - 2] = { 18,10,4,28,19,11,5,38,29,20,12,6,39,30,21,13,7,40,31,22,14,8,41,32,23,15,9,42,33,24,16,43,34,25,17,44,35,26,45,36,27,46,37,47 };

//Enemy�̍U���Ɉڂ�܂ł̃^�C�}�[
int timer = 24000;

//�G�̈ړ��X�s�[�h
int speed;

//�v���C���[�̈ʒu���i�[�p
int epx;
int epy;

//�摜�i�[�ϐ�
int Enemy_Handle[40];
int Enemy_Shot_Gyallaly[2];

int Enemy_None_Num;

//Enemy�����Ă�ꂽ�t���O
bool Enemy_Hit_Flg = false;

//Enemy�Ő������X�R�A
int e_score;

int cntAttack = 0;

int cntEnemy = 0;
int cntRed = 0;
int cntYellow = 0;
int cntPourple = 0;
int cntBlue = 0;

//�����̐������Z����ϐ�
int NumBlow = 0;
int cntBlow = 0;

//�G�̒e�̐������Z����ϐ�
int numShot = 0;
int cntShot = 0;


int T_Count[EnemyCount] = { 0 };
int P_Count[EnemyCount] = { 0 };

//�����ʒu(x���W)
static double first_x[50] = { 150,190,230,270					//3
, 110,150,190,230,270,310				//9
, 70, 110,150,190,230,270,310,350			//17
, 30, 70, 110,150,190,230,270,310,350,390		//27
, 30, 70, 110,150,190,230,270,310,350,390		//37
, 30, 70, 110,150,190,230,270,310,350,390		//47
, 30,                                 390 };

//�����ʒu(y���W)
static double first_y[50] = { 80, 80, 80, 80
,110,110,110,110,110,110
,140,140,140,140,140,140,140,140
,170,170,170,170,170,170,170,170,170,170
,200,200,200,200,200,200,200,200,200,200
,230,230,230,230,230,230,230,230,230,230
,80,80 };

/***************************************
�֐���:Enemy_Init
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�������֐�
***************************************/
int Enemy_Init() {

	//�摜�ǂݍ���
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
�֐���:Enemy_Move
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�̓����𑀍삷��B
�@�@�@�e�֐��͂����ŌĂт����B
   ***************************************/
int Enemy_Move() {

	//�v���C���[�̍��W�󂯎��(�^��)
	epx = Player_Pos_Init_x();
	epy = Player_Pos_Init_y();

	Enemy_POINT();

	Enemy_Control();

	Cnt_Yellow();
	Cnt_Red();
	Cnt_Pourple();
	Cnt_Blue();

	//���E�ړ�
	if ((enemy[49].x > 680.0 || enemy[48].x < 10.0)) {
		speed *= -1;
	}

	for (i = 0; i < EnemyCount + 2; i++) {

		//��ɍ��E�ړ�
		enemy[i].fx += speed;

		//�����œ����G�̏��Ԃ�I��
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
�֐���:Enemy_Control
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�̍��E�̓����̐؂�Ԃ������𑀍삷��B
�@�@�@�[��Enemy�����ׂē|�����Ɖ��ɓ���
   �@�@�@ �\����̓G�Ő؂�Ԃ�
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
�֐���:Enemy_Move_Flg
���� :n (���������F�̓Y����)
�߂�l:�Ȃ�
�@�\ :���F�����������ɐԂ��ꏏ�ɓ�����
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
�֐���:Enemy_Chose
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�ǂ̓G���������A�I������B
�@�@�@���F���������Ƃ��̂݁AEnemy_Move_Flg���Ăяo���B
   �@�@�@ �I�ѕ��́A4��ނ̔z��̒��g(�D��x������)����
	   �@ �o���Ă����B
		 ***************************************/
int Enemy_Attack_Chose() {

	//�������̑I��
	int Attack_Mode = GetRand(2) + 1;

	int Number = 25;

	//�G���U���������񐔂𐔂���
	cntAttack++;
	if (cntAttack >= 20) {
		cntAttack = 0;
	}

	Number = Number - cntAttack;
	if (Number < 20)Number = 20;
	//�����A����n(20�`140)�̂��܂�Z��0�̎��A���F�𓮂����B
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
	//�G�̒��S�_���v���C���[�̉E���Ȃ�
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
�֐���:Enemy_Attack_Move
���� :Enemy�̓Y����
�߂�l:�Ȃ�
�@�\ :enemy���U������Ƃ��ɌĂяo�����B
�@�@�@�ŏ��͉~�^������̖ڕW�_�Ɍ������ē����B
   �@�@�@���F��������͖̂������B
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

		//���͈͂ɂ�����A���S�_���ړ�����B
		//pow(enemy�̔��a + �ڕW�_�̔��a, 2)
		if (pow(16 + 120, 2) >= pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2) &&
			pow(16 + 45, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			enemy[num].A_Mode = CHANGE;
		}

		//���͈͊O�Ȃ�A���S�_�Ɍ������Ĉړ�����B
		if (pow(16 + 50, 2) < pow(enemy[num].pt_x - enemy[num].x, 2) + pow(enemy[num].pt_y - enemy[num].y, 2)) {
			enemy[num].A_Mode = TRACK;
		}

		//�~�̎�����񂷏ꍇ
		//���͈͓��Ȃ�
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

		//�~����̒E�o(CHANGE�ɕς���)
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


		//��ʊO�ɍs������A�ڕW�_�X�V
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
		//��ʉ��ɍs�����Ƃ��̏���
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
�֐���:Enemy_POINT
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :enemy�̖ڕW�_���ǂ��ɒu�����Ɏg�p
�@�@�@4�̓_������A
   �@�@�@1�ڂ́A�S�̂ŉ~�ʂ�`��2,3,4�Ԗڂ̂ǂ��ɓ_��u�������߂�B
	  �@ 2,3�ڂ́A��ʍ��E�Ő��(�H)�ɉ~�ʂ����B
		4�ڂ́A�v���C���[�̉��ɐ��œ���
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
				//��]�̃X�s�[�h
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
				//��]�̃X�s�[�h
				point[j].deg += 0.001;

			}
			if (point[j].vct == RIGHT) {
				point[j].deg -= 0.001;
			}

			//�~�̔��a�@�~�@sin or cos
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
�֐���:Enemy_Satellite
���� :enemy�̓Y����
�߂�l:�Ȃ�
�@�\ :enemy�̍ŏ��̉�]�ƍŌ�̉�]���o���̂Ɏg��
�@�@�@Satellite�͉q���̈ӁB
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
�֐���:EnemyShot_Mgr
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�G�̒e�̊Ǘ����s��
�@�@�@���˂Ɛ��������A�e�֐����Ăяo���B
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

	//�Đ�����0�Ȃ�,return�ŒE�o
	if (numShot <= 0) {
		return 0;
	}

	//�z����̂��̂�O�l�߂ɕ��ёւ���B
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
�֐���:EnemyShot_Move
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�G�̒e�𓮂����B
�@�@�@��ʊO�ɍs���ƕ\���������B
   �@�X�R�A�̌Ăяo���������ōs��
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
�֐���:Enemy_Score
���� :�j�󂳂ꂽEnemy�̓Y����
�߂�l:e_Score
�@�\ :�j�󂳂ꂽEnemy�̃X�R�A�͉��Z����B
�@�@�@Enemy_State_Init���Ăяo���A
   �@ Player��Enemy�̏�Ԃ�n���B
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

//�G�̒e�̓����蔻��
/***************************************
�֐���:Enemy_Hit
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�v���C���[�̓��蔻��
�@�@�@Enemy�̒e��Enemy���g�ɓ�����B
   �@ true��false��Player�ɔ���𑗂�
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
�֐����FCreate_Blow
���e �FEnemy�j�󎞂ɍ��W���擾���A
�@�@�@ ���ёւ���B
	���� �F�Ȃ�
	�ԋp�l�F�Ȃ�
	***********************************/
int Create_Blow() {

	NumBlow = 0;

	//�����̍Đ����𐔂���
	for (int l = 0; l < REMITBLOW; l++) {
		if (tmpBlow[l].onActive == true) {
			NumBlow++;
		}
	}

	//�Đ�����0�Ȃ�,return�ŒE�o
	if (NumBlow <= 0) {
		return 0;
	}

	//�z����̂��̂�O�l�߂ɕ��ёւ���B
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

//�v���C���[�ƓG�̊p�x���o��
/*************************************************
�֐���:Enemy_Deg
���� :Enemy�̓Y����
�߂�l:�Ȃ�
�@�\ :Enemy��Player�̊p�x���o��
�@�@�@��]�^�����̂݁AEnemy_Satellite��ڕW�ɂ���B
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
�֐���:Cnt_Yellow
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :���F�̓G�𐔂���
***********************************************/
int Cnt_Yellow() {
	cntYellow = 0;
	for (i = 0; i < 4; i++) {
		if (enemy[i].onActive == Draw_ON)cntYellow++;
	}
	return 0;
}

/**********************************************
�֐���:Cnt_Red
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�ԐF�̓G�𐔂���
***********************************************/
int Cnt_Red() {
	cntRed = 0;
	for (i = 4; i < 10; i++) {
		if (enemy[i].onActive == Draw_ON)cntRed++;
	}
	return 0;
}

/**********************************************
�֐���:Cnt_Pourple
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :���F�̓G�𐔂���
***********************************************/
int Cnt_Pourple() {
	cntPourple = 0;
	for (i = 10; i < 18; i++) {
		if (enemy[i].onActive == Draw_ON)cntPourple++;
	}
	return 0;
}

/**********************************************
�֐���:Cnt_Blue
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :�F�̓G�𐔂���
***********************************************/
int Cnt_Blue() {
	cntBlue = 0;
	for (i = 18; i < 48; i++) {
		if (enemy[i].onActive == Draw_ON)cntBlue++;
	}
	return 0;
}


//Enemy�̃A�j���[�V����
/***************************************
�֐���:Enemy_Animetion
���� :Enemy�̓Y����
�߂�l:�Ȃ�
�@�\ :�ʏ�̍��E�ړ����̃A�j���[�V���������B
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
�֐���:Enemy_Draw
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�̕\��������B
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
�֐���:EnemyShot_Draw
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�̒e�Ɣ����̕\��������B
***************************************/
int EnemyShot_Draw() {

	for (j = 0; j < NUMSHOT; j++) {

		if (enemy_shot[j].onActive == true) {
			DrawRotaGraph(enemy_shot[j].x, enemy_shot[j].y, 2.5, 0, Enemy_Shot_Gyallaly[Enemy_None_Num], true, 0, 0);
		}
	}
	for (i = 0; i < REMITBLOW; i++) {
		//�Đ�

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
�֐���:Enemy_Stage_Clear
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�����ׂĔj�󂳂���
�@�@�@�X�e�[�W�N���A
   ***************************************/
int Enemy_Stage_Clear() {

	//�܂����j����ĂȂ�������Areturn��-1��Ԃ��B
	for (i = 0; i < EnemyCount; i++) {
		if (enemy[i].onActive == Draw_ON) {
			return -1;
		}
	}
	Scene_Mgr_ChangeScene(E_Scene_Result);

	//���F�ȊO���S�����j����Ă���c
	Cnt_Yellow();

	//���F��2�̈ȏ�c���Ă��ԂŃN���A������A��̕������p��
	if (cntYellow >= 2)cntYellow = 2;

	return cntYellow;
}

/***************************************
�֐���:Enemy_Pos_Init_x
���� :Enemy�̓Y����
�߂�l:Enemy��x���W
�@�\ :Enemy��x���W��n��
***************************************/
int Enemy_Pos_Init_x(int num) {
	return enemy[num].x;
}

/***************************************
�֐���:Enemy_Pos_Init_y
���� :Enemy�̓Y����
�߂�l:Enemy��y���W
�@�\ :Enemy��y���W��n��
***************************************/
int Enemy_Pos_Init_y(int num) {
	return enemy[num].y;
}

/***************************************
�֐���:Enemy_State_Init
���� :Enemy�̓Y����
�߂�l:Enemy�̏��
�@�\ :Enemy�̏�Ԃ�n��
***************************************/
int Enemy_State_Init(int num) {
	return enemy[num].onActive;
}

/***************************************
�֐���:Enemy_End
���� :�Ȃ�
�߂�l:�Ȃ�
�@�\ :Enemy�̏I���H
***************************************/
int Enemy_End() {
	return 0;
}