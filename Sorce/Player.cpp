#include "Dxlib.h"
#include "Player.h"
#include "keyboard.h"
#include "Enemy.h"
#include "PlayerShot.h"
#include "Sound.h"
#include "Scene_Mgr.h"
#include"Result.h"


//�v���C���[
S_Player Player;

//�c�@
int remain = 500;

//bool Draw_Flg = true;
int HitFlg = false;

//�U���Ɋւ������
bool PlayerShot_Flg = 0;				//���˃t���O

bool Remain_Flg = false;				//UI��Remain�����𑗂�t���O

										//�U�����󂯂��t���O
bool EnemyHit_Flg = false;

//�摜�Ɋւ������
//int None_Num = 0;						//�摜�̃X�^���o�C���
int Gyallaly[8];						//�v���C���[�̉摜�̕ϐ�
int i;									//�摜�\���p�̕ϐ�
float j;
int Player_Image[35] = { 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7 }; //�摜�̏���(�A�j���[�V����)
int Player_Cnt;							//�摜�\���p�J�E���g
int OnActive = true;					//Player�������Ă�����
int BackGround;
int BackGround2;
int starcnt = 0;
int y = 5;
int gy = 750;
int scl_speed = 1;

int Player_Init() {
	remain = Result_Reborn();

	//�v���C���[�̏����ʒu
	Player.x = 350;
	Player.y = 600;

	//�摜
	Gyallaly[8] = { 0 };
	LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);				//�摜�̓ǂݍ���
	i = 0;
	Player_Cnt = 0;

	BackGround = LoadGraph("Image/BackGround.png");
	BackGround2 = LoadGraph("Image/BackGround2.png");

	return 0;
}

int Player_Dpct() {

	y += scl_speed;
	gy += scl_speed;

	starcnt = (starcnt + 1) % 120;

	PlayerShot_Flg = PlayerShot_Dpct();														//Shot����t���O���󂯎��
	//�L�[����
	if (OnActive == true) {																	//�����Ă��Ȃ���Γ����Ȃ�
																							//��
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 3;
		}

		//��
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 3;
		}
	}

	if (OnActive == true) {											//player�������Ă��Ȃ���Ό��ĂȂ�
		if (PlayerShot_Flg == 0) {
			i = 0;													//�e���������Ă���player�̉摜
																	//�e������
			if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
				SetPlayer_Shot_Flg(1);								//�|�C���^�ŕԂ�
				SetGax_Sound(8);									//���ˉ���炷
				i = 1;												//�e���������Ă��Ȃ�player�̉摜
			}
		}
	}

	if (Player.x <= 200) {											//Player��x�̓�����200�Ŏ~�߂�
		Player.x = 200;
	}

	if (Player.x >= 650) {											//Player��x�̓�����1000�Ŏ~�߂�
		Player.x = 650;
	}
	EnemyHit_Flg = Enemy_Hit();									//enemy����̓����蔻����������
	if (OnActive == true) {
		if (EnemyHit_Flg == true) {
			HitFlg = true;
			OnActive = false;
			SetGax_Sound(7);									//player�����񂾂Ƃ�
			Player_Remain();	//Remain�֔��
								//������
			Player_Hit();
		}
	}

	return PlayerShot_Flg;
}

int Player_Remain() {		//�c�@�̏���
	if (HitFlg == true) {
		remain--;
		HitFlg = false;
	}

	if (remain < 1) {
		Scene_Mgr_ChangeScene(E_Scene_Result);
	}
	return remain;
}

int Player_Hit() {

	EnemyHit_Flg = false;

	return EnemyHit_Flg;
}

int Player_Draw() {
	
	if (starcnt < 60) {
		DrawExtendGraph(5, y, 1280, gy, BackGround, true);
	}
	else {
		DrawExtendGraph(-10, y, 1280, gy, BackGround, true);
	}

	if (y == 700) {
		y = 5;
		gy = 750;
	}

	if (starcnt < 60) {
		DrawExtendGraph(5, y-700, 1280, gy-750, BackGround2, true);
	}
	else {
		DrawExtendGraph(-10, y-700, 1280, gy-750, BackGround2, true);
	}

	if (y == 700) {
		y = 5;
		gy = 750;
	}

	if (OnActive == true) {														//�����Ă��鎞�����\��

		DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true);			//�摜�̊g��\��

	}
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "remain:%d", remain);
	if (OnActive == false) {													//�j�󂳂ꂽ���̃A�j���[�V����

		Player_Cnt++;

		//�������̃A�j���[�V����
		switch (Player_Image[Player_Cnt]) {
		case 4:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[4], true);
			break;

		case 5:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[5], true);
			break;

		case 6:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[6], true);
			break;

		case 7:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[7], true);
			break;

		case 8:
			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[2], true);
			break;

		}
		if (Player_Cnt > 400) {		//�����J�E���g��200��
			Player.x = 350;			//�v���C���[�̕����ꏊ��x���W��300�ɂ���B
			Player_Cnt = 0;			//�J�E���g��0�ɂ���
			OnActive = true;		//player������������
		}
	}
	return PlayerShot_Flg;
}

int Player_Pos_Init_x()				//Player�̂����W
{
	return Player.x;
}

int Player_Pos_Init_y()				//Player��y���W
{
	return Player.y;
}

int Player_End()
{
	//remain = 0;
	return 0;
}
