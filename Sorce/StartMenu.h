#pragma once

typedef struct {	//�\����
	int x, y;  //���W�̕ϐ�
	char name[256];     //���ږ��̕ϐ�
} MenuElement_t;

typedef struct {
	
	int Start;
	int On_Start;
	int End;
	int On_End;

} Image_t;

extern int StartMenu_Init();
extern int StartMenu_Dpct();
extern int StartMenu_Draw();
extern int StartMenu_End();