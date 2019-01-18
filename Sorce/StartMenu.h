#pragma once

typedef struct {	//構造体
	int x, y;  //座標の変数
	char name[256];     //項目名の変数
} MenuElement_t;

typedef struct {
	
	int Start;
	int CREDIT;
	int HIGH_SCORE;
	int ONE_UP;

} Image_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();