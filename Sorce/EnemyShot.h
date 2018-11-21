#ifndef INCLUDE_ENEMYSHOT
#define INCLUDE_ENEMYSHOT

typedef struct {	//\‘¢‘Ì
	int x;  //enemy‚ÌxÀ•W
	int y;  //enemy‚ÌyÀ•W
} S_EShot;

extern int EnemyShot_Init();
extern int EnemyShot_Dpct();
extern int EnemyShot_Draw();
extern int EnemyShot_End();

extern int Enemy_Shot_Pos(int*, int*,int);
extern int enemyShot(int);
extern int Enemy_Hit();

#endif