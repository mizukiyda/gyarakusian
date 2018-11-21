#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Draw();
extern int Enemy_Pos_Init_x();
extern int Enemy_Pos_Init_y();
extern int Enemy_End();

struct P_Enemy {
	int Type;   //0:黄色　1:赤　2:紫　3:青
	double x;	//座標
	double y;
	double fx;	//初期位置
	double fy;
	double nx;
	double ny;
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

