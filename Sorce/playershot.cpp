#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int a;
int atari = 0;
int Player_Shot_Flg = 0;		//�v���C���[������ł��̃t���O
int Player_Shotcnt_y;		//�e�𓮂���
int ex[EnemyCount];
int ey[EnemyCount];
bool e_draw[EnemyCount];
int Px, Py;
int score = 0;
S_PShot pbullet;
bool Player_Hit_Flg[EnemyCount] = { false };	//�v���C���[�̒e��enemy�ɓ�����������Flg
int Player_Shot_Gyallaly[2];		// �摜�i�[�ϐ�
int Player_None_Num;			// �摜�̃X�^���o�C���(�Î~���)

								/****������****/

int Playershot_Init() {

	Player_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Player_Shot_Gyallaly); // �摜�����[�h
	Player_None_Num = 0;        //�X�^���o�C��Ԃ̌����Ă�����𐳖ʂւ��邽�߂̉摜�ԍ�1
	return 0;
}

/****�v�Z****/
int PlayerShot_Dpct() {
	for (a = 0;a < EnemyCount;a++) {
		ex[a] = Enemy_Pos_Init_x(a);
		ey[a] = Enemy_Pos_Init_y(a);
		e_draw[a] = Enemy_State_Init(a);
	}
	if (Player_Shot_Flg == 1) {
		pbullet.x = Player_Pos_Init_x();
		pbullet.y = Player_Pos_Init_y();
		Player_Shot_Flg = 2;
		//pbullet.y -= 5;
	}
	//�t���O��2�ɂȂ�����e����Ɍ���
	if (Player_Shot_Flg == 2) {
		pbullet.y -= 5;
		//�e�̍��W��0�܂ōs������ӂ炮��0�ɂ��ď���

	}
	if (pbullet.y <= 0) {
		Player_Shot_Flg = 0;
	}
	for (a = 0;a < EnemyCount;a++) {
		if (ex[a] - 25 <= pbullet.x - 10 && pbullet.x + 10 <= ex[a] + 25 &&
			pbullet.y == ey[a] + 25 && e_draw[a] == true) {
			Player_Shot_Flg = false;
			Player_HIT(a);
		}
	}

	return Player_Shot_Flg;
}

int Player_HIT(int num) {

	Player_Hit_Flg[num] = true;

	return Player_Hit_Flg[num];
}

int Playershot_Draw() {

	if (atari == 1) {

		DrawFormatString(300, 400, GetColor(255, 255, 255), "������");
		if (Player_Shot_Flg == true) {
			atari = 0;
		}
	}

	if (Player_Shot_Flg != 0) {
		//�摜�̊g��\��
		DrawRotaGraph(pbullet.x + 3, pbullet.y - 25, 4.0, 0.0, Player_Shot_Gyallaly[Player_None_Num], true);
	}

	return 0;
}


void SetPlayer_Shot_Flg(int flag) {
	Player_Shot_Flg = flag;
}

int PlayerShot_Pos_Init_x() {

	return pbullet.x;
}

int PlayerShot_Pos_Init_y() {

	return pbullet.y;
}

/**********************************�@�I��(���)�@******************************************/
int PlayerShot_End()
{
	//No Script
	return 0;
}
