#include"dxlib.h"
#include"Playershot.h" 
#include"Enemy.h"
#include"Player.h"

int Player_Shot_Flg = false;		//�v���C���[������ł��̃t���O
int Player_Shotcnt_y;		//�e�𓮂���
int Handle;				// �f�[�^�n���h���i�[�p�ϐ�
int ex, ey;
int Px, Py;
int score = 0;
S_PShot pbullet;
int Player_Hit_Flg;	//�v���C���[�̒e��player�ɓ�����������Flg

/****������****/

int Playershot_Init()
{
	Handle = LoadGraph("Image/Galaxian_OBJ_bullet.png"); // �摜�����[�h
	ex = Enemy_Pos_Init_x();
	ey = Enemy_Pos_Init_y();
	return 0;
}

/****�v�Z****/
int Playershot_Dpct()
{

	Px = Player_Pos_Init_x();
	Py = Player_Pos_Init_y();

	pbullet.x = Px;
	pbullet.y = Py;

	Player_Shot_Flg = Player_Dpct();

	if (Player_Shot_Flg == true) {
		player_Shot();
	}
	return 0;
}

int player_Shot() {

	Player_Shot_Flg = false;

	pbullet.y -= 10;

	if (pbullet.x == ex && pbullet.y == ey) {
		player_Hit();
		Player_Score();
		Player_Shot_Flg = false;
	}

	if (pbullet.y <= 0) {
		Player_Shot_Flg = false;
	}
	return Player_Shot_Flg;
}

int player_Hit() {
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
	if (Player_Shot_Flg == true) {
		DrawGraph(pbullet.x , pbullet.y ,Handle ,true);
	}

	DrawFormatString(0, 400, GetColor(255, 255, 255), "pbullet.x���W  %d\npbullet.y���W  %d", pbullet.x, pbullet.y);

	return 0;
}
	/**********************************�@�I��(���)�@******************************************/
	int PlayerShot_End()
	{
		//No Script
		return 0;
	}
