#include"DxLib.h"
#include"Enemy.h"
//#include"Player.h"
//#include"EnemyShot.h
#include<Math.h>

/********************  �ϐ��錾  ****************************/

P_Enemy enemy[50];

A_Enemy attack_enemy[50];

//debug�p 
	/*���݂̃~���b���擾*/
double dNextTime = GetNowCount();
int x, add;
int NowTime;
int ChangeTime;

int e_count[48] = { 0 };
int move[14] = { 0,1,3,4,4,3,1 ,0,-1,-3,-4,-4,-3,-1 };
//���[�v�p
static int i, j, k;

//�p�x
int e_deg = 0;
//
int n = 0;

//�G�̈ړ��X�s�[�h
int speed=1;

//Enemy�̍U���Ɉڂ�܂ł̃^�C�}�[
double timer = 4000;

//�s���J�E���g
int cntEnemy = 0;

//�v���C���[�̈ʒu���i�[�p
double px;
double py;

int Enemy_Handle[40];

//�����ʒu(x���W)
static double first_x [50] = {               590,630,670,710					//3
                                       , 550,590,630,670,710,750				//9
                                  , 510, 550,590,630,670,710,750,790			//17
                              , 470, 510, 550,590,630,670,710,750,790,830		//27
                              , 470, 510, 550,590,630,670,710,750,790,830		//37
                              , 470, 510, 550,590,630,670,710,750,790,830		//47
	                          , 470, 830 }; 

//�����ʒu(y���W)
static double first_y[50] = { 80, 80, 80, 80
									  , 110, 110, 110, 110, 110, 110
								  , 140, 140, 140, 140, 140, 140, 140, 140
							  ,170,170,170,170,170,170,170,170,170,170
							  ,200,200,200,200,200,200,200,200,200,200
							  ,230,230,230,230,230,230,230,230,230,230
							  ,80,80};

static int priority_L[19] = {	//�����̓G�U���D��x
	18,28,38,10,19,29,39,11,20,30,40,12,21,31,41,13,22,32,42
};

static int priority_R[19] = {	//�E���̓G�U���D��x
	27,37,47,17,26,36,46,16,25,35,45,15,24,34,44,14,23,33,43
};

int Enemy_Init() {

    //�摜�ǂݍ���
	LoadDivBmpToGraph("Galaxian_OBJ_enemy.png", 40, 8, 5, 18, 18, Enemy_Handle,true, false);

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
		else if(i < 10) {
			enemy[i].Type = 1;
			enemy[i].anime = 8;
			enemy[i].nx = 120;
		}
		else if (i < 18) {
			enemy[i].Type = 2;
			enemy[i].anime = 16;
			enemy[i].nx = 150;
		}
		else if(i < 28) {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 180;
		}
		else if (i < 38) {
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 210;
		}
		else{
			enemy[i].Type = 3;
			enemy[i].anime = 24;
			enemy[i].nx = 240;
		}
		attack_enemy[i].timer = 300;
		attack_enemy[i].enemyshot = false;

	}

	//px = Player_Pos_Init_x;
	//py = Player_Pos_Init_y;

	px = 300;  //debug
	py = 400;  //degug

	return 0;
}

int Enemy_Move() {

	//���E�ړ�
	if ((enemy[49].x > 1080.0 || enemy[48].x < 200.0)) {
		speed *= -1;
	}	


	for (i = 0; i < 50; i++) {
		//�G�̃��[�V�����^�C�}�[
		timer--;
		if (timer <= 0 ) {//�^�C�}�[���[���ɂȂ�����A���ɖ߂�
			timer = 12000;
			cntEnemy++;

			if (cntEnemy == 5) {
				enemy[0].Attack_Move_Flg = true;
				enemy[0].Move_Flg = true;
				//cntEnemy = -5;
			}
			else if (px > 320) { //�v���C���[����ʂ̉E���ɂ����ꍇ

				for(j=0;j<19;j++){
					if (enemy[priority_R[j]].Attack_Move_Flg == false&& enemy[priority_R[j]].Move_Flg == false && enemy[i].Draw_Flg == true) {	//�����Ƃ��낪false��������
						enemy[priority_R[j]].Attack_Move_Flg = true;		//������true�ɂ��āA���[�v�𔲂���
						enemy[priority_R[j]].Move_Flg = true;
						break;
					}
				}
			}
			else {
				for (j = 0; j < 19; j++) {
					if (enemy[priority_L[j]].Attack_Move_Flg == false&& enemy[priority_L[j]].Move_Flg == false&& enemy[i].Draw_Flg == true) {	//���On�ɂ��Ĕ�����
						enemy[priority_L[j]].Attack_Move_Flg = true;
						enemy[priority_L[j]].Move_Flg = true;
						break;
					}
				}
			}
		}
		//��ɍ��E�ړ�
		enemy[i].fx += speed;
		if (enemy[i].Attack_Move_Flg == false) { //�U��������Ȃ��Ƃ����E�ړ�
			enemy[i].x += speed;
		}
		if (enemy[i].Move_Flg == true) {	//�U�����̈ړ�

			enemy[i].y += 1;	//�������Ɍ������Ĉړ�
			if (i != 48 && i != 49) {
				attack_enemy[i].timer--;	//�U���̃^�C�}�[
			}
			if (attack_enemy[i].timer <= 0) {
				attack_enemy[i].timer = 40;
				attack_enemy[i].enemyshot = true;
				return 1;
				//Enemy_Shot_Flg();
				//return attack_enemy[i].enemyshot = true;
			}

			if (enemy[i].Attack_Move_Flg == true) {
				e_count[i]++;
				if (e_count[i] / 20 > 14) {
					e_count[i] = 0;
				}

				enemy[i].x += move[e_count[i] / 20];
			}
			//��ʊO�ɍs������A�Ԃ���΂�
			if (enemy[i].x < 0 || enemy[i].x>1280) {
				enemy[i].x = 100000;
			}
			//��ʉ��ɍs�����Ƃ��̏���
			if (enemy[i].y >= 750 && i != 48 && i != 49) {
				enemy[i].y = -10;
				enemy[i].x = enemy[i].fx;
				enemy[i].Attack_Move_Flg = false;
			}
		}
			//��ʉ����猳�̏ꏊ�ɖ߂����Ƃ� //80�����
		if (enemy[i].Attack_Move_Flg == false
			&& /*(enemy[i].x == enemy[i].fx + 3 || enemy[i].x == enemy[i].fx-3) &&*/ enemy[i].y == enemy[i].fy) {
			//���]
			enemy[i].Move_Flg = false;
			enemy[i].deg += 15;
			if (enemy[i].deg >= 360) {
				enemy[i].deg = 0;
			}
		}
	}
	return 0;
}

int Enemy_Attack() {

	bool Enemy_Shot_Flg = attack_enemy[i].enemyshot;

	return Enemy_Shot_Flg;
}

int Enemy_Draw() {

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

/*int Enemy_Shot_Flg() {
	return 1;
}*/

int Enemy_End() {
	return 0;
}