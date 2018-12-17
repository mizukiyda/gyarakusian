#ifndef INCLUDE_PLAYER
#define INCLUDE_PLAYER

extern int Player_Init();
extern int Player_Dpct();
extern int Player_Draw();
extern int Player_End();

extern int Player_Remain();
extern int Player_Pos_Init_x();
extern int Player_Pos_Init_y();
extern int Player_Hit();

typedef struct {
	int x;
	int y;
	int nx;
}S_Player;

#endif
