extern int Playershot_Init();
extern int PlayerShot_Dpct();
extern int Playershot_Draw();
extern int PlayerShot_End();

extern int Player_HIT();
extern int Player_Score();
extern void SetPlayer_Shot_Flg(int);


typedef struct {

	int x;  //プレイヤーのx座標
	int y;  //プレイヤーのy座標

}S_PShot;