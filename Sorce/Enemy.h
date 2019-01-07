#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
#define RIGHT 1
#define LEFT -1
#define NUMSHOT 30
#define REMITBLOW 10
#define EnemyCount 48

#define PUSH_BLOW(i,E_X,E_Y) 	tmpBlow[i].x = E_X; tmpBlow[i].y = E_Y; blow[i].Blow_Cnt = 0; tmpBlow[i].onActive = true;
#define PUSH_SHOT(i,E_X,E_Y)    tmpEnemyShot[i].x = E_X; tmpEnemyShot[i].y = E_Y; tmpEnemyShot[i].onActive = true;

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
extern int Enemy_Draw();
extern int Enemy_Score(int);
extern int Enemy_Hit();
extern int Enemy_deg(int *);

//�G�̒e�֘A�̒�`
extern int EnemyShot_Mgr();
extern int EnemyShot();
extern int EnemyShot_Move();
extern int EnemyShot_Move();
extern int EnemyShot_Draw();

extern int Enemy_Stage_clear();
extern int Enemy_Pos_Init_x(int);
extern int Enemy_Pos_Init_y(int);
extern int Enemy_State_Init(int);
extern int Enemy_End();

extern int Create_Blow();


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
	int anime_cnt;
	int mode;
	int Draw_Flg;
};	//Enemy Position

typedef struct {
	int x;
	int y;
	bool onActive;
}POS;

typedef struct {
	int x;
	int y;
	int Blow_Cnt;
	bool onActive;
}Blow;



typedef enum {
	//MODE
	NONE,
	MOVE,
	ATTACK,
	DEL
}MODE;


//�G�̃^�C�v
typedef enum {
	YELLOW,
	RED,
	PURPLE,
	BLUE
}TYPE;

//
typedef enum {
	SHOT_POINT_FIRST = 280,
	SHOT_POINT_SECOND = 300,
	SHOT_POINT_THIRD = 320,
	SHOT_POINT_FOURTH = 340
}SHOTPOINT;




#endif