#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"

int atari = 0;
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
		//�t���O��2�ɂȂ�����e����Ɍ���
		if (Player_Shot_Flg == 2) {
			pbullet.y -= 5;
			//�e�̍��W��0�܂ōs������ӂ炮��0�ɂ��ď���
			
		}
		if (pbullet.y <= 0) {
			Player_Shot_Flg = 0;
		}

		if (300 <= pbullet.x && pbullet.x <= 400 && 
			pbullet.y >=300 && pbullet.y <= 400) {
			Player_Hit();
			Player_Score();
			Player_Shot_Flg = false;
			

		}

	

	return Player_Shot_Flg;
}

int Player_Hit() {
	//�e������������Enemy�n��
	Player_Hit_Flg = true;
	if (Player_Hit_Flg == true) {
		atari = 1;
	}
	
		return Player_Hit_Flg;
}

int Player_Score() {
	//Enemy_Type 
	/*if (Enemy_Type = 3) {  //����	���F�Ȃ�
		score += 10;
	}
	else if(Enemy_Type = 2){  //�������Ȃ�
		score += 30;
	}
	else if(Enemy_Type = 1) {  //�����ԂȂ�
		score += 60;
	}
	else if (Enemy_Type = 0) {
		score += 100;
	}*/
	return score;
}

int Playershot_Draw(){

	if (atari == 1) {


		DrawFormatString(300, 400, GetColor(255, 255, 255), "������");
		if (Player_Shot_Flg == true) {
			atari = 0;
	}
	}
	
	if (Player_Shot_Flg != 0) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);

		DrawCircle(pbullet.x, pbullet.y, 5, GetColor(255, 255, 255), 10, 10);
	}
	DrawBox(300, 300, 400, 400, GetColor(255,255,255), false);
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
