#include "DxLib.h"
#include "keyboard.h"
#include "Scene_Mgr.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("�M�����N�V�A��");
	//SetWindowSize(1280, 700);
	//SetGraphMode(1280, 700, 32);
	SetWindowSize(600, 700);
	SetGraphMode(700, 700, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

																		 //�������Ǘ��֐��̌Ăяo��
	Scene_Mgr_Init();
	//Init_Mgr();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		//�����ɏ�����ǉ�
		Keyboard_Update();

		Scene_Mgr_Dpct();
		//Dpct_Mgr();		//�v�Z����
		Scene_Mgr_Draw();
		//Drow_Mgr();		//�`�ʏ���

	}
	Scene_Mgr_End();
	//End_Mgr();			//�I������

	DxLib_End(); // DX���C�u�����I������
	return 0;
}
