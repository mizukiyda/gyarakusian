#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"

//�S���@���o

int Score;					//player�����������X�R�A��ۑ����Ă���
int Remain;					//Player�̎c�@�̊m�F
int PLAYER_HIT_FLG;			//EnemyShot����player�ɓ����������̃t���O�����炢�A�c�@���u 1 �v���炷��Ƃ�����
int SCORE_Image, REMAIN_Image;
int UI_Init() {

	Score = 0;		//�����̃X�R�A
	Remain = 3;		//�����̎c�@

	SCORE_Image = LoadGraph("Image/SCORE.png");
	REMAIN_Image = LoadGraph("Image/REMAIN.png");

	return 0;
}

int UI_Dpct() {

	Score = Player_Score();					//player��Player_Score()�ɓ����Ă���X�R�A�����炤
	PLAYER_HIT_FLG = Player_Remain();		//Player�����������t���O�������̃t���O�ɓ����

	if (PLAYER_HIT_FLG == true) {			//���� true �Ȃ�Player�̎c�@���u�@1�@�v���炷
		Remain--;
	}
	return 0;
}

int UI_Draw() {

	DrawGraph(200, 0, SCORE_Image, TRUE);			 // �f�[�^�n���h�����g���ĉ摜��`��
	DrawGraph(750, 650, REMAIN_Image, TRUE);		 // �f�[�^�n���h�����g���ĉ摜��`��

	return 0;
}

int UI_End() {

	return 0;
}