#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//�ϐ��錾
int Credit_Sound;						 // �N���W�b�g����Q�[����ʂɉf�鎞�鎞�̉�
int Enemy_LastOne;						 // �G�������Ă��ɂꗬ�� ����������
int Enemy_LastTwo;						 // �G�������Ă��ɂꗬ���@
int Enemy_Attack_Sound;					 // �G�������Ă��鉹
int Enemy_Hit_Sound;					 // �G�̃q�b�g���̌��ʉ�
int HitGalaxian_Sound;					 // ���F���G��|������
int Player_Miss_Sound;					 // �v���C���[�����ꂽ�Ƃ��̌��ʉ�
int Player_Shot_Sound;			         // ���˂̌��ʉ�
int StartMenu_Sound;					 // �X�^�[�g���j���[��BGM
int Gax_Sound = 0;						 // ���ʉ���Switch �����ɑ���Ή��������

int volume;

 //������
int Sound_Init() {
	/*
	LoadSoundMem�c�������ɃT�E���h������
	�p�X�w��
	*/
	Credit_Sound       = LoadSoundMem("S_Galaxian/gax_CreditSound.wav");    // �N���W�b�gSE�̃p�X
	Enemy_LastOne      = LoadSoundMem("S_Galaxian/gax_Enemy_LastOne.wav");	// �G�������Ă��ɂꗬ�� ����������
	Enemy_LastTwo      = LoadSoundMem("S_Galaxian/gax_Enemy_LastTwo.wav");	// �G�������Ă��ɂꗬ��
	Enemy_Attack_Sound = LoadSoundMem("S_Galaxian/gax_EnemyAttack.wav");	// �G�������Ă��鉹
	Enemy_Hit_Sound    = LoadSoundMem("S_Galaxian/gax_HitEnemy.wav");		// �G��|�����Ƃ���SE�̃p�X�w��
	HitGalaxian_Sound  = LoadSoundMem("S_Galaxian/gax_HitGalaxian.wav");	// ���F���G��|������
	Player_Miss_Sound  = LoadSoundMem("S_Galaxian/gax_Miss.wav");			// �v���C���[�����ꂽ����SE�̃p�X�w��
	Player_Shot_Sound  = LoadSoundMem("S_Galaxian/gax_Shot.wav");			// ���ˉ��̃p�X�w��																
	StartMenu_Sound    = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");		// �����ƭ�BGM�̃p�X�w��
	return 0;
}

//�v�Z
int Sound_Dpct() {
	/*
	PlaySoundMem�c�������ɓ��ꂽ�T�E���h���Đ�
	NORMAL�c�m�[�}���Đ�
	BACK�c�c�o�b�N�O���E���h�Đ�
	LOOP�c�c���[�v�Đ�
	*/

	switch (Gax_Sound) {

	case 1:
		// �Q�[����ʂɉf�鎞�Ȃ鎞�̉�
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);	// �Đ�
		Gax_Sound = 0;	// �������������0�ɂ��Ă���return����
		break;
	case 2:
		// �G�������Ă��ɂꗬ��	����������
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(150, Enemy_LastOne);
		Gax_Sound = 0;
		break;
	case 3:
		// �G�������Ă��ɂꗬ��
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(150,Enemy_LastTwo);
		Gax_Sound = 0;
		break;
	case 4:
		// �G���~���Ă��Ă�����ʉ�
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 5:
		// �G�̃q�b�g���̌��ʉ�
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 6:
		// ���F���G��|������
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 7:
		// �v���C���[�����ꂽ�Ƃ��̌��ʉ�
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 8:
		// ���˂̌��ʉ�
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 9:
		// �X�^�[�g���j���[��BGM
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 10:
		// �G���~���Ă��鉹���~�߂鏙�X�ɏ���������
		for (volume = 255; volume < 0; volume--) {
		
			ChangeVolumeSoundMem(volume, Enemy_Attack_Sound);
		}
		Gax_Sound = 0;
		break;
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