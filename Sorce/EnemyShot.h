#ifndef INCLUDE_ENEMYSHOT
#define INCLUDE_ENEMYSHOT

typedef struct {	//�\����
	int x;  //enemy��x���W
	int y;  //enemy��y���W
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