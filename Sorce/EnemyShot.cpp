#include "DxLib.h"
#include "EnemyShot.h"
#include"Player.h"
#include"Enemy.h"

#define EnemyCount 48		//enemy�̓G�̐�

S_EShot ebullet[EnemyCount];		//�\����///��ɍ��W

static int i,j;		//for���p
int Enemy_Shot_Flg = false;		//�G�l�~�[������ł��̃t���O
int Handles;				//// �f�[�^�n���h���i�[�p�ϐ�
int Enemy_Hit_Flg = false;	//�G�l�~�[�̒e��player�ɓ�����������Flg
int px;		//player ��x���W
int py;		//player ��y���W

int Enemy_Shot_Pos(int *x, int *y,int num) {
	//�G�l�~�[�������������W���|�C���^�ɓ����

	*x = ebullet[num].x;
	*y = ebullet[num].y;
	return 0;
}

int EnemyShot_Init() {
	//����������

	Handles = LoadGraph("Image/Galaxian_OBJ_bullet.png"); // �摜�����[�h

	for (i = 0;i < EnemyCount;i++) {
		ebullet[i].x = Enemy_Pos_Init_x();		//enemy����e���o�邘���W�����炤
		ebullet[i].y = Enemy_Pos_Init_y();		//enemy����e���o�邙���W�����炤
	}
	return 0;
}

int EnemyShot_Dpct( ) {
	//�v�Z����

	px = Player_Pos_Init_x();		//player���炘���W�����炤
	py = Player_Pos_Init_y();		//player����y���W�����炤

	Enemy_Shot_Flg = Enemy_Move();

	if (Enemy_Shot_Flg == true) {		//����enemy���e��łȂ�
		enemyShot(1);
	}
	return 0;
}

int enemyShot(int num) {
	//�G�l�~�[�̒e�̔��ˏ���

	for (i = 0;i < 2;i++) {		//�e���ł��Ă���
		ebullet[i].y += 500;

		if (px == ebullet[num].x && py == ebullet[num].y) {		//�e��Player�Ƀq�b�g�����@���@�e��������
			Enemy_Hit();
			Enemy_Shot_Flg = false;
		}

		if (ebullet[num].y >= 600) {		//�G�l�~�[�̒e����ʊO�ɏo���������@���@Flg���Ă�false�ɂȂ�

			Enemy_Shot_Flg = false;
		}
	}
	return Enemy_Shot_Flg;
}

int Enemy_Hit() {
	//�e���q�b�g������Player�ɓn�� ���@Player�����j
	Enemy_Hit_Flg = true;

	return Enemy_Hit_Flg;
}

int EnemyShot_Draw() {
	//�`�ʏ���
	for (i = 0;i < EnemyCount;i++) {
		for (j = 0;j < 2;j++) {			//�e���ł�
			if (Enemy_Shot_Flg == true) {
				DrawGraph(ebullet[i].x, ebullet[i].y, Handles, TRUE); // �f�[�^�n���h�����g���ĉ摜��`��
			}
		}
		if(Enemy_Shot_Flg == false)		
		{
			DrawGraph(ebullet[i].x, ebullet[i].y, Handles, FALSE); // �f�[�^�n���h�����g���ĉ摜��`�������
		}
		DrawFormatString(0, 500, GetColor(255, 255, 255), "ebullet.x���W  %d\nebullet.y���W  %d", ebullet[i].x, ebullet[i].y);
	}
	return 0;
}

int EnemyShot_End() {
	//�I������
	return 0;
}