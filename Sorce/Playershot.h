#ifndef INCLUDE_PLAYERSHOT
#define INCLUDE_PLAYERSHOT

extern int Playershot_Init();
extern int PlayerShot_Dpct();
extern int Playershot_Draw();
extern int PlayerShot_End();

extern void SetPlayer_Shot_Flg(int);
extern int Player_HIT(int);


typedef struct {

	int x;  //プレイヤーのx座標
	int y;  //プレイヤーのy座標

}S_PShot;

typedef enum {

	Draw_ON,		//表示
	Draw_OFF,		//非表示	
	Draw_Anime,
	Breaken			//破壊された
} S_EnemyType;

#endif