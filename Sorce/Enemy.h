#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Draw();
extern int Enemy_Pos_Init_x();
extern int Enemy_Pos_Init_y();
extern int Enemy_End();

struct P_Enemy {
	int Type;   //0:���F�@1:�ԁ@2:���@3:��
	double x;	//���W
	double y;
	double fx;	//�����ʒu
	double fy;
	double nx;
	double ny;
	double deg;	//�p�x
	int anime;
	bool Move_Flg;
	bool Attack_Move_Flg;
	bool Draw_Flg;
};	//Enemy Position

typedef struct {
	int timer;
	bool enemyshot;
}A_Enemy;	//Enemy Atack



#endif

