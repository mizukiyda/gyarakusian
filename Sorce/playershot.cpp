#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int Player_Shot_Flg = 0;		//�v���C���[������ł��̃t���O
int Player_Shotcnt_y;		//�e�𓮂���
int Handle;				// �f�[�^�n���h���i�[�p�ϐ�
int ex, ey;
int Px, Py;
int score = 0;
S_PShot pbullet;
int Player_Hit_Flg;	//�v���C���[�̒e��player�ɓ�����������Flg

/****������****/

int Playershot_Init(){

	Handle = LoadGraph("Image/Galaxian_OBJ_bullet.png"); // �摜�����[�h
	ex = Enemy_Pos_Init_x();
	ey = Enemy_Pos_Init_y();
	return 0;
}

/****�v�Z****/
int PlayerShot_Dpct(){

		if (Player_Shot_Flg == 1) {
			pbullet.x = Player_Pos_Init_x();
			pbullet.y = Player_Pos_Init_y();
			Player_Shot_Flg = 2;
			//pbullet.y -= 5;
		}

		if (Player_Shot_Flg == 2) {
			pbullet.y -= 5;
			if (pbullet.y <= 0) {
				Player_Shot_Flg = 0;
			}
		}

	/*
	pbullet.x = Player_Pos_Init_x();
	pbullet.y = Player_Pos_Init_y();

	Player_Shot_Flg = Player_Dpct();

	if (Player_Shot_Flg == true) {
 		
	    pbullet.y -= 100;

		if (pbullet.x == ex && pbullet.y == ey) {
			Player_Hit();
			Player_Score();
			Player_Shot_Flg = false;
		}

		if (pbullet.y <= 0) {
			Player_Shot_Flg = false;
		}
	}
	return Player_Shot_Flg;
	*/
	return Player_Shot_Flg;
}

int Player_Hit() {
	//�e������������Enemy�n��
	Player_Hit_Flg = true;

	return Player_Hit_Flg;
}

int Player_Score() {
	/*if () {  //�����΂Ȃ�
		score += 10;
	}
	else if(){  //�������Ȃ�
		score += 30;
	}
	else if() {  //�����ԂȂ�
		score += 60;
	}
	else if () {
		score += 100;
	}*/
	return score;
}

int Playershot_Draw(){
	if (Player_Shot_Flg != 0) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);

		DrawCircle(pbullet.x, pbullet.y, 5, GetColor(255, 255, 255), 10, 10);
	}

	DrawFormatString(0, 400, GetColor(255, 255, 255), "pbullet.x���W  %d\npbullet.y���W  %d", pbullet.x, pbullet.y);

	return 0;
}


void SetPlayer_Shot_Flg(int flag) {
	Player_Shot_Flg = flag;
}

	/**********************************�@�I��(���)�@******************************************/
	int PlayerShot_End()
	{
		//No Script
		return 0;
	}
