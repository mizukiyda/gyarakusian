#ifndef INCLUDE_ENEMYSHOT
#define INCLUDE_ENEMYSHOT

typedef struct {	//ç\ë¢ëÃ
	int x;  //enemyÇÃxç¿ïW
	int y;  //enemyÇÃyç¿ïW
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