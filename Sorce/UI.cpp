#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"
#include"Enemy.h"

//�S���@���o

int Score;					//player�����������X�R�A��ۑ����Ă���
int Remain;					//Player�̎c�@�̊m�F
int tmp_Remain;			//EnemyShot����player�ɓ����������̃t���O�����炢�A�c�@���u 1 �v���炷��Ƃ�����
int SCORE_Image, REMAIN_Image, UI_Image;
int Stock[3];
int UI_Init() {

	Score = 0;		//�����̃X�R�A
	Remain = 3;		//�����̎c�@

	SCORE_Image = LoadGraph("Image/SCORE.png");
	REMAIN_Image = LoadGraph("Image/REMAIN.png");
	//UI_Image = LoadGraph("Image/Galaxian_OBJ_other.png");
	LoadDivGraph("Image/Galaxian_OBJ_other.png", 3, 3, 1, 18, 20, Stock,true);
	//���@�摜�̕����ǂݍ��݁@�摜���@���������@���̕������@�c�̕������@���������摜��x,y
	//�����ǂݍ��݂��ē����O���t�B�b�N�n���h����ۑ�����int�^�̔z��ւ̃|�C���^�@�����̔��f


		return 0;
	
}

int UI_Dpct() {

	Score = Enemy_Score();					//player��Player_Score()�ɓ����Ă���X�R�A�����炤
	tmp_Remain = Player_Remain();		//Player�����������t���O�������̃t���O�ɓ����

	return 0;

}

int UI_Draw() {	

	DrawGraph(200, 0, SCORE_Image, TRUE);			 // �f�[�^�n���h�����g���ĉ摜��`��
	DrawGraph(750, 650, REMAIN_Image, TRUE);		 // �f�[�^�n���h�����g���ĉ摜��`��
	DrawExtendGraph(50, 150,100,200, Stock[0], true);		 // �f�[�^�n���h�����g���ĉ摜��`��
	//Extend��t����Ɗg��\���ł��� �T�C�Y�͎w�肷��K�v������
	
	return 0;

}

int UI_End() {

	return 0;
}