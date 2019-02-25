#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"
#include"Enemy.h"
#include"Keyboard.h"

//�S���@���o

int Score;					//player�����������X�R�A��ۑ����Ă���
int Remain;					//Player�̎c�@�̊m�F
int tmp_Remain;			//EnemyShot����player�ɓ����������̃t���O�����炢�A�c�@���u 1 �v���炷��Ƃ�����
int SCORE_Image, REMAIN_Image, UI_Image;
int Stock[3];
int cnt =0;              //���@�\���̃��[�v�p�J�E���g
int HIGH_SCORE;
int ONE_UP;

int UI_Init() {

	Score = 0;		//�����̃X�R�A
	Remain = 3;		//�����̎c�@
	cnt = 0;        //�摜�̃J�E���g

	SCORE_Image = LoadGraph("Image/SCOREdot.png");
	REMAIN_Image = LoadGraph("Image/REMAIN.png");
	LoadDivGraph("Image/Galaxian_OBJ_other.png", 3, 3, 1, 18, 20, Stock, true); //���@�P

	HIGH_SCORE = LoadGraph("Image/HIGH SCOREdot.png");
	ONE_UP = LoadGraph("Image/1UPdot.png");
	LoadDivGraph("Image/Galaxian_OBJ_other.png", 3, 3, 1, 18, 20, Stock, true); //��
	//���@�摜�̕����ǂݍ��݁@�摜���@���������@���̕������@�c�̕������@���������摜��x,y
	//�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�̔z��ւ̃|�C���^�@�����̔��f
		return 0;
	
}

int UI_Dpct() {

	tmp_Remain = Player_Remain();		//Player�����������t���O�������̃t���O�ɓ����
	return 0;

}

int UI_Draw() {	
	int x = 0;
	int y = 0;
	int Rx = 0;
	int Ry = 0;

	//���㒸�_�̍��Wx,y,�E�����_x,y �{�P�̍��W �O���t�B�b�N�n���h���A�������̗L��
	    x = 120;
		y = 650;
		Rx = 170;
		Ry = 700;
	for (int i = 0; i < tmp_Remain; i++) {
		
		//DrawExtendGraph(280, 650, 330, 700, Stock[0], true);   //�������Ԗڂ̎��@
		DrawExtendGraph(x +(i*40), y, Rx+(i*40), Ry, Stock[0], true);   //�������Ԗڂ̎��@
		
		//DrawExtendGraph(320, 650, 370, 700, Stock[0], true);   //�������ڂ̎��@
		cnt++;
	};

	DrawGraph(160, -30, HIGH_SCORE, TRUE);
	DrawGraph(60, 0, ONE_UP, TRUE);
	
	DrawExtendGraph(800, 635, 850, 680, Stock[1], true);   //�E�̃X�e�[�W���ɉ����đ������
	//Extend��t����Ɗg��\���ł��� �T�C�Y�͎w�肷��K�v������
	
	return 0;

}


int UI_End() {

	return 0;
}