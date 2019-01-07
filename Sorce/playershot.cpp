#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"
#include"Sound.h"

//�V���b�g�̍\����
S_PShot pbullet;

//�ǂ̃^�C�v�̓G��|�������̔���
S_EnemyType Mode;

int a;
int Player_Shot_Flg = 0;					//�v���C���[������ł��̃t���O
int Player_Shotcnt_y;						//�e�𓮂���
int ex[EnemyCount];							//enemy�̐����̂����W
int ey[EnemyCount];							//enemy�̐����̂����W
bool e_draw[EnemyCount];					//enmey�̐����m�F
bool Player_Hit_Flg[EnemyCount] = {Draw_ON};	//enmey�̐����m�F�œ������Ă��Ȃ����
int Player_Shot_Gyallaly[2];				// �摜�i�[�ϐ�
int Player_None_Num;						// �摜�̃X�^���o�C���(�Î~���)

/****������****/
int Playershot_Init() {   //����������

	Player_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Player_Shot_Gyallaly);		// �摜�����[�h
	Player_None_Num = 0;																		//�X�^���o�C��Ԃ̌����Ă�����𐳖ʂւ��邽�߂̉摜�ԍ�1
	for (int i = 0;i < EnemyCount;i++) {														
		Player_Hit_Flg[i] = Draw_ON;																//�����������Ƃ��đS���������Ă��Ȃ�
	}

	return 0;
}

/****�v�Z****/
int PlayerShot_Dpct() {
	for (a = 0;a < EnemyCount;a++) {
		ex[a] = Enemy_Pos_Init_x(a);										//enemy��x���W
		ey[a] = Enemy_Pos_Init_y(a);										//enemy��y���W
		e_draw[a] = Enemy_State_Init(a);									//enemy �̐���
	}

	if (Player_Shot_Flg == 1) {												//Player����|�C���^�ł��炤
		pbullet.x = Player_Pos_Init_x();									//�e��x���W��Player��x���W�Ɋi�[����
		pbullet.y = Player_Pos_Init_y();									//�e��y���W��Player��y���W�Ɋi�[����
		Player_Shot_Flg = 2;
	}
	//�t���O��2�ɂȂ�����e����Ɍ���
	if (Player_Shot_Flg == 2) {
		pbullet.y -= 5;														//�e�̍��W��0�܂ōs������t���O��0�ɂ��ď���		
	}

	if (pbullet.y <= 0) {													//�����e����ʊO�ɍs������falsre�ɂ���
		Player_Shot_Flg = 0;
	}

	for (a = 0;a < EnemyCount;a++) {
		if (ex[a] - 25 <= pbullet.x - 10 && pbullet.x + 10 <= ex[a] + 25 &&			//enemy�Ƃ̓����蔻��
			pbullet.y == ey[a] + 25 && e_draw[a] == Draw_ON) {
			Player_Shot_Flg = false;												//�e������
			Player_Hit_Flg[a] = Draw_OFF;												//���̓G�ɓ��������Ƃ����t���O
			Player_HIT(a);															//�̓G�ɓ��������Ƃ����|�C���^������	
			pbullet.y = 0;															//����������Player�̒��Ɋi�[�����
			SetGax_Sound(5);							//enemy�����ꂽ���̉�(�����ł͂Ȃ�����)

		}
	}
	return Player_Shot_Flg;
}

//Enemy�ւ̓����蔻��
int Player_HIT(int num) {

	return Player_Hit_Flg[num];
}

int Playershot_Draw() {

	if (Player_Shot_Flg != 0) {
		//�摜�̊g��\��
		DrawRotaGraph(pbullet.x + 3, pbullet.y - 25, 4.0, 0.0, Player_Shot_Gyallaly[Player_None_Num], true);
	}
	return 0;
}


void SetPlayer_Shot_Flg(int flag) {										//�V���b�g�Ɋւ���|�C���^
	Player_Shot_Flg = flag;
}

/**********************************�@�I��(���)�@******************************************/
int PlayerShot_End()
{
	//No Script
	return 0;
}
