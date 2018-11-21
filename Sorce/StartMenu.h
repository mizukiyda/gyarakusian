#pragma once

typedef struct {	//\‘¢‘Ì
	int x, y;  //À•W‚Ì•Ï”
	char name[256];     //€–Ú–¼‚Ì•Ï”
} MenuElement_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();