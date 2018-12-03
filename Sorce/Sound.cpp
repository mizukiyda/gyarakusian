#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//�ϐ��錾
int Player_Shot_Sound;			         // ���˂̌��ʉ�
int StartMenu_Sound;					 // �X�^�[�g���j���[��BGM


//������
int Sound_Init() {
	Player_Shot_Sound = LoadSoundMem("S_Galaxian/gax_Shot.wav");		// ���ˉ��̃p�X�w��ƕϐ��ւ̑��
	StartMenu_Sound = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");	// �����ƭ�BGM�̃p�X�w��Ƒ��
	return 0;
}

//�v�Z
int Sound_Dpct() {

		//PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
	
	return 0;
}

//�`��
int Sound_Draw() {

	return 0;
}

int Sound_End() {
	//����
	return 0;
}