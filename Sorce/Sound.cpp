#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//#define SE_CNT 9		//���ʉ��̐�

//�ϐ��錾
int Credit_Sound;						 // �N���W�b�g����Q�[����ʂɉf�鎞�Ȃ鎞�̉�
int Enemy_LastOne;						 // ��SE
int Enemy_LastTwo;						 // ��SE 2
int Enemy_Attack_Sound;					 // �G�̔��ˌ��ʉ�
int Enemy_Hit_Sound;					 // �G�̃q�b�g���̌��ʉ�
int HitGalaxian_Sound;					 // ��SE 3
int Player_Miss_Sound;					 // �v���C���[�����ꂽ�Ƃ��̌��ʉ�
int Player_Shot_Sound;			         // ���˂̌��ʉ�
int StartMenu_Sound;					 // �X�^�[�g���j���[��BGM

int Gax_Sound = 0;						 // ���ʉ���Switch

/*
int PlaySound_Payer() {					//Prayer
	PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
	return 0;
}
*/

//������
int Sound_Init() {
	/*
	switch (){

	case 1:

		// �N���W�b�g����Q�[����ʂɉf�鎞�Ȃ鎞�̉�
		*/
		Credit_Sound = LoadSoundMem("S_Galaxian/gax_CreditSound.wav");			// �N���W�b�gSE�̃p�X
		/*break;
	case 2:

		// ��SE*/
		Enemy_LastOne = LoadSoundMem("S_Galaxian/gax_Enemy_LastOne.wav");		// NAZO
		/*break;
	case 3:

		// ��SE 2*/
		Enemy_LastTwo = LoadSoundMem("S_Galaxian/gax_Enemy_LastTwo.wav");		// NAZO
		/*break;
	case 4:

		// �G�̔��ˌ��ʉ�*/
		Enemy_Attack_Sound = LoadSoundMem("S_Galaxian/gax_EnemyAttack.wav");	// �G�̔��ˉ��̃p�X�w��
		/*break;
	case 5:

		// �G�̃q�b�g���̌��ʉ�*/
		Enemy_Hit_Sound = LoadSoundMem("S_Galaxian/gax_HitEnemy.wav");			// �G��|�����Ƃ���SE�̃p�X�w��
		/*break;
	case 6:

		// ��SE 3*/
		HitGalaxian_Sound = LoadSoundMem("S_Galaxian/gax_HitGalaxian.wav");		// NAZO
		/*break;
	case 7:

		// �v���C���[�����ꂽ�Ƃ��̌��ʉ�*/
		Player_Miss_Sound = LoadSoundMem("S_Galaxian/gax_Miss.wav");			// �v���C���[�����ꂽ����SE�̃p�X�w��
		/*break;
	case 8:

		// ���˂̌��ʉ�*/
		Player_Shot_Sound = LoadSoundMem("S_Galaxian/gax_Shot.wav");			// ���ˉ��̃p�X�w��
		/*break;
	case 9:

		// �X�^�[�g���j���[��BGM*/
		StartMenu_Sound = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");		// �����ƭ�BGM�̃p�X�w��
		/*break;

	}*/
	return 0;
}

//�v�Z
int Sound_Dpct() {

	/*
	switch (Gax_Sound) {

	case 1:

		// �N���W�b�g����Q�[����ʂɉf�鎞�Ȃ鎞�̉�
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);
		break;
	case 2:

		// ��SE
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_BACK);
		break;
	case 3:

		// ��SE 2
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_BACK);
		break;
	case 4:

		// �G�̔��ˌ��ʉ�
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
		break;
	case 5:

		// �G�̃q�b�g���̌��ʉ�
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
		break;
	case 6:

		// ��SE 3
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
		break;
	case 7:

		// �v���C���[�����ꂽ�Ƃ��̌��ʉ�
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
		break;
	case 8:

		// ���˂̌��ʉ�
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
		break;
	case 9:

		// �X�^�[�g���j���[��BGM
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
		break;
	}
	*/

	if (Gax_Sound == 1) {
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 2) {
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 3) {
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 4) {
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 5) {
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 6) {
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 7) {
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 8) {
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_NORMAL);
	}
	if (Gax_Sound == 9) {
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
	}

	return Gax_Sound;
}

void SetGax_Sound(int flag) {			// �����ɑ��������switch�ɓ���
	Gax_Sound = flag;					// switch�ɑ��
}

//�`��
int Sound_Draw() {

	return 0;
}


int Sound_End() {
	//����
	return 0;
}