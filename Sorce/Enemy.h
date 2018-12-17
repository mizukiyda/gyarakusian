#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
#define RIGHT 1
#define LEFT -1
#define NUMSHOT 5
#define EnemyCount 48

//�I���̃��[�h
#define MODE_DOWN 1	//�I�΂ꂽ������̂܂܉��Ɍ�������TRUE�ɂ��Ă���
#define MODE_NEXT 2	//�I�΂ꂽ��̎��̗�̏�2��TRUE�ɂ���

//��
#define PI 3.14159265359

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Move_Flg(int);
extern int Enemy_control();
extern int Enemy_Attack_Chose();
extern int Enemy_Attack_Move(int *);
extern int Enemy_Shot(int,int,int);
extern int Enemy_Shot_Set(int *);
extern int EnemyShot_Move();
extern int Enemy_Draw();
extern int Enemy_Score();
extern int Enemy_Hit();
//extern int Enemy_deg(int *);
extern int EnemyShot_Draw();
extern int Enemy_Stage_clear();
extern int Enemy_Pos_Init_x(int);
extern int Enemy_Pos_Init_y(int);
extern int Enemy_State_Init(int);
extern int Enemy_End();


struct P_Enemy {
	int Type;   //0:���F�@1:�ԁ@2:���@3:��
	int x;	//���W
	int y;
	double fx;	//first_x �����ʒu
	double fy;
	double nx;	//next_x ����X�̏ꏊ	
	double deg;	//�p�x
	double vct;
	double vct2;
	double speed;
	int anime;
	int mode;
	//bool Move_Flg;
	//bool Attack_Move_Flg;
	bool Draw_Flg;
};	//Enemy Position

typedef struct {
	int timer;
	bool enemyshot;
}A_Enemy;	//Enemy Atack

typedef struct {	//�\����
	int x;  //enemy��x���W
	int y;  //enemy��y���W
	bool Draw_Flg;
} S_EShot;

typedef enum {
	//MODE
	NONE,
	MOVE,
	ATTACK,
	DEL
}MODE;

#endif