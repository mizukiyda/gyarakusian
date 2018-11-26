#ifndef INCLUDE_ENEMYSHOT
#define INCLUDE_ENEMYSHOT

typedef struct {	//構造体
	int x;  //enemyのx座標
	int y;  //enemyのy座標
} S_EShot;

extern int EnemyShot_Init();
extern int EnemyShot_Dpct();
extern int EnemyShot_Draw();
extern int EnemyShot_End();

extern void SetPlayer_Shot_Flg(int);

extern int Enemy_Shot_Pos(int*, int*,int);
extern int enemyShot(int);
extern int Enemy_Hit();

#endif