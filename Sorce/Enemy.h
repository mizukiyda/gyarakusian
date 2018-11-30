#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
#define RIGHT 1
#define LEFT -1
#define NUMSHOT 4
#define EnemyCount 48

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Move_Flg(int *);
extern int Enemy_Attack_Chose(int *);
extern int Enemy_Attack_Move(int *);
extern int Enemy_Shot(int,int,int);
extern int Enemy_Draw();
extern int Enemy_Pos_Init_x();
extern int Enemy_Pos_Init_y();
extern int Enemy_End();


struct P_Enemy {
	int Type;   //0:黄色　1:赤　2:紫　3:青
	int x;	//座標
	int y;
	double fx;	//first_x 初期位置
	double fy;
	double nx;	//next_x 次のXの場所	
	double deg;	//角度
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

