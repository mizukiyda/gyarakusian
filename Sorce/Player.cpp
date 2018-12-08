#include "Dxlib.h"
#include "Player.h"
#include "keyboard.h"
#include "PlayerShot.h"
#include "Sound.h"

//�v���C���[
S_Player Player;

//�c�@
int remain = 3;

//�U���Ɋւ������
bool PlayerShot_Flg = 0;   //���˃t���O

						   //�摜�Ɋւ������
						   //int None_Num = 0;      //�摜�̃X�^���o�C���
int Gyallaly[8];   //�v���C���[�̉摜�̕ϐ�
int i;

int Player_Init() {

	//�v���C���[�̈ʒu
	Player.x = 300;
	Player.y = 600;

	//�摜
	Gyallaly[8] = { 0 };
	LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);
	i = 0;
	//None_Num = 0;

	return 0;
}

int Player_Dpct() {
	//�L�[����

	PlayerShot_Flg = PlayerShot_Dpct();

	//��
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
		Player.x -= 3;
	}

	//��
	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
		Player.x += 3;
	}

	if (PlayerShot_Flg == 0) {
		i = 0;
		//�e������
		if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
			SetGax_Sound(8);
			SetPlayer_Shot_Flg(1);

			i = 1;
		}
	}


	if (Player.x <= 200) {
		Player.x = 200;
	}

	if (Player.x >= 1000) {
		Player.x = 1000;
	}

	/*if (Enemy_Hit() == true) {
	Player_Remain();
	}*/

	return PlayerShot_Flg;
}

int Player_Remain() {		//�c�@�̏���


	return 0;
}

int Player_Draw() {

	//DrawGraph(Player.x , Player.y , Gyallaly[None_Num], true);
	DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true); //�摜�̊g��\��
	DrawFormatString(0, 300, GetColor(255, 255, 255), "x���W  %d\ny���W  %d", Player.x, Player.y);

	/*	if (PlayerShot_Flg == 1)
	{
	i = 1;
	}

	if (PlayerShot_Flg == 0)
	{
	i = 0;
	}*/

	/*if (Enemy_Hit() == true) {
	Player_Image = count_x / 8 % 4;

	if (remain > 0) {
	remain = remain - 1;
	}
	else {
	Player_End();
	}
	}*/
	return PlayerShot_Flg;
}

int Player_Pos_Init_x()
{
	return Player.x;
}

int Player_Pos_Init_y()
{
	return Player.y;
}

int Player_End()
{
	return 0;
}
