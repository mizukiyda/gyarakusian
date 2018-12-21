#include "DxLib.h"
#include "Result.h"
#include "StartMenu.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "Player.h"

MenuElement_t ResultMenuElement[MENU_ELEMENT_MAX]{
	{ 100 , 200 , "Restart" },
{ 100 , 400 , "Title" },
{ 100 , 600 , "Exit" }
};

//�����ŕϐ���錾�iC++���g��Ȃ��̂ŃO���[�o���ϐ��j

static int SelectNum;
int reborn;

int Restart;
int On_Restart;
int Title;
int On_Title;
int End;
int On_End;
int Result;

// Init ������
int Result_Init() {
	//�����ŏ�����������
	//step_count = UI_StepCount();			UI���ł�����R�����g���͂���
	SelectNum = 0;
	reborn = 2;

	Restart = LoadGraph("Image/RESTART1.png");				//�X�^�[�g��I�����Ă���摜
	On_Restart = LoadGraph("Image/RESTART.png");				//�X�^�[�g��I�����Ă��Ȃ��摜
	Title = LoadGraph("Image/Title1.png");
	On_Title = LoadGraph("Image/Title.png");
	End = LoadGraph("Image/End.png");				//�G���h��I�����Ă���摜
	On_End = LoadGraph("Image/End2.png");				//�G���h��I�����Ă��Ȃ��摜

	Result = LoadGraph("Image/�肴���.png");
	return 0;
}

int Result_Dpct() {
	//�����Ōv�Z
	//Dqct�͖��t���[���Ă΂��
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		SelectNum = (SelectNum - 1) % 3;	// ���݂̑I�����ڂ����ɂ��炷
	}
	if (SelectNum == -1) {
		SelectNum = MENU_ELEMENT_MAX - 1;
	}

	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		SelectNum = (SelectNum + 1) % 3;	// ���݂̑I�����ڂ�����ɂ��炷
	}
	for (int i = 0; i < MENU_ELEMENT_MAX; i++) {
		if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
			ResultMenuElement[i].x = 80; // ���W��80�ɂ���
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {	//���W��80�ɂȂ��Ă��鍀�ڂŃX�y�[�X�L�[��������
														//���̍��ڂ̒��ɓ���
				int tmp;
				switch (i) {

				case 0:
					Result_Reborn();
					Scene_Mgr_ChangeScene(E_Scene_Game);
					break;

				case 1:
					Scene_Mgr_ChangeScene(E_Scene_StartMenu);
					break;

				case 2:
					Scene_Mgr_End();
					DxLib_End(); // DX���C�u�����I������
					exit(0);
					break;
				}
			}
		}
		else {                     // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
			ResultMenuElement[i].x = 100;// ���W��100�ɂ���
		}
	}

	return 0;
}

int Result_Reborn() {

	return reborn;
}

int Result_Draw() {
	//�����ŕ`��
	//�����������t���[���Ă΂�܂����v�Z�Ƃ͕ʂɏ����܂�

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "�肴���");
	DrawGraph(100, 100, Result, TRUE);

	/*
	for (int i = 0; i<MENU_ELEMENT_MAX; i++) { // ���j���[���ڂ�`��
	DrawFormatString(ResultMenuElement[i].x, ResultMenuElement[i].y, GetColor(255, 255, 255), ResultMenuElement[i].name);
	}*/

	switch (SelectNum)
	{
	case 0://�X�^�[�g����
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, Restart, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, On_Title, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, On_End, TRUE);
		break;
	case 1:
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, On_Restart, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, Title, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, On_End, TRUE);
		break;
	case 2://�G���h����
		DrawGraph(ResultMenuElement[0].x, ResultMenuElement[0].y, On_Restart, TRUE);
		DrawGraph(ResultMenuElement[1].x, ResultMenuElement[1].y, On_Title, TRUE);
		DrawGraph(ResultMenuElement[2].x, ResultMenuElement[2].y, End, TRUE);

		break;
	}
	return 0;
}

int Result_End() {
	//�����ŏI������
	return 0;
}