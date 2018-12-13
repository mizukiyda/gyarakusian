extern int Playershot_Init();
extern int PlayerShot_Dpct();
extern int Playershot_Draw();
extern int PlayerShot_End();

extern void SetPlayer_Shot_Flg(int);
extern int PlayerShot_Pos_Init_x();
extern int PlayerShot_Pos_Init_y();
extern int Player_HIT(int);


typedef struct {

	int x;  //プレイヤーのx座標
	int y;  //プレイヤーのy座標

}S_PShot;