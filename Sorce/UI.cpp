#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"

int Score;		//player�����������X�R�A��ۑ����Ă���
int Remain;		//Player�̎c�@�̊m�F
int PLAYER_HIT_FLG;			//EnemyShot����player�ɓ����������̃t���O�����炢�A�c�@���u 1 �v���炷��Ƃ�����

int UI_Init() {

	Score = 0;		//�����̃X�R�A
	Remain = 3;		//�����̎c�@

	return 0;
}

int UI_Dpct() {

	Score = Player_Score();				//player��Player_Score()�ɓ����Ă���X�R�A�����炤
	PLAYER_HIT_FLG = Player_Remain();		//Player�����������t���O�������̃t���O�ɓ����

	if (PLAYER_HIT_FLG == true) {		//���� true �Ȃ�Player�̎c�@���u�@1�@�v���炷
		Remain--;
	}
	return 0;
}

int UI_Draw() {

	DrawFormatString(500, 0, GetColor(255, 0, 0), "SCORE:  %d", Score);			//�X�R�A�̕\��
	DrawFormatString(900, 700, GetColor(255, 0, 0), "Remain:  %d", Remain);		//player�̎c�@�̕\��

	return 0;
}

int UI_End() {

	return 0;
}