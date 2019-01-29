#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include"Sound.h"

Image_t Image;
int star;
int count = 0;
int starcount = 0;

int StartMenu_Init() {

	Image.Start = LoadGraph("Image/PUSH SPACE BUTTON.png");				//�摜�̏K��	
	Image.CREDIT = LoadGraph("Image/CREDIT.png");
	Image.HIGH_SCORE = LoadGraph("Image/HIGH SCORE.png");
	Image.ONE_UP = LoadGraph("Image/1UP.png");
	star = LoadGraph("Image/BackGround.png");

	return 0;
}

int StartMenu_Dpct() {
	//Dqct�͖��t���[���Ă΂��

	count = (count + 1) % 100;											//�����̓_�ł�����	

	starcount = (starcount + 1) % 100;									//�w�i�̓_��

	if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
		Scene_Mgr_ChangeScene(E_Scene_Game);							//�X�y�[�X�L�[���������玟�̃V�[����
		SetGax_Sound(9);
	}
	return 0;
}

int StartMenu_Draw() {
	//�����ŕ`��

	if (starcount > 50) {
		DrawRotaGraph(550, 370, 3.5, 0, star, TRUE);					//���݂ɕ\������
	}

	if (starcount < 50) {
		DrawRotaGraph(600, 370, 3.5, 0, star, TRUE);					//���݂ɕ\������
	}

	if (count < 50) {
		DrawGraph(-30, 500, Image.Start, TRUE);							//�_��
	}
	DrawGraph(-70, 650, Image.CREDIT, TRUE);
	DrawGraph(160, 0, Image.HIGH_SCORE, TRUE);
	DrawGraph(60, 0, Image.ONE_UP, TRUE);

	return 0;
}

int StartMenu_End() {
	//NoScript
	return 0;
}
