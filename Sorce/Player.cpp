#include"Dxlib.h"
#include"Player.h"
#include"keyboard.h"
#include "Enemy.h"
#include"PlayerShot.h"

	//�v���C���[
	S_Player Player;

	//�c�@
	int remain = 3;
	bool Draw_Flg = true;

	//�U���Ɋւ������
	bool PlayerShot_Flg = 0;   //���˃t���O

	//�摜�Ɋւ������
	//int None_Num = 0;      //�摜�̃X�^���o�C���
	int Gyallaly[8];   //�v���C���[�̉摜�̕ϐ�
	int i;       //�摜�\���p
	float j;
	int Player_Image[35] = { 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7 }; //�摜�̏���(�A�j���[�V����)
	int Player_Cnt;   //�摜�\���p�J�E���g

	int Player_Init() {

		//�v���C���[�̈ʒu
		Player.x = 300;
		Player.y = 600;

		//�摜
		Gyallaly[8] = {0};
		LoadDivGraph("Image/Galaxian_OBJ_token.png", 8, 4, 2, 34, 35, Gyallaly);
		i = 0;
		Player_Cnt = 0;
		//Player_Image[10] = {4,5,6,7};
		//None_Num = 0;

		return 0;
	}

	int Player_Dpct() {
		//�L�[����

		PlayerShot_Flg = PlayerShot_Dpct();

		//��
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
			Player.x -= 1;
		}

		//��
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
			Player.x += 1;
		}

		if (PlayerShot_Flg == 0) {
			i = 0;
		//�e������
		    if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
			    //PlayerShot_Flg = 1;
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

		if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
			//Player_Remain();
			Draw_Flg = false;
		}



		return PlayerShot_Flg;
	}

	int Player_Remain() {		//�c�@�̏���

		if (Enemy_Hit() == true) {

			Draw_Flg = false;
			if (remain > 0) {
				remain = remain - 1;
			}
			else {
				Player_End();
			}
		}

		return 0;//Player_Draw;
	}

	int Player_Draw() {

		if (Draw_Flg == true) {

			DrawRotaGraph(Player.x, Player.y, 2.0, 0.0, Gyallaly[i], true); //�摜�̊g��\��
			DrawFormatString(0, 300, GetColor(255, 255, 255), "x���W  %d\ny���W  %d", Player.x, Player.y);

		}

		if (Draw_Flg == false) {

			Player_Cnt++;

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

				case 9:
					Draw_Flg = true;
					Player.x = 300;
					break;

				}
		}

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
		//remain = 0;
		return 0;
	}
