#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
#define RIGHT 1
#define LEFT -1
#define NUMSHOT 30
#define EnemyCount 48

//選択のモード
#define MODE_DOWN 1	//選ばれた列をそのまま下に向かってTRUEにしていく
#define MODE_NEXT 2	//選ばれた列の次の列の上2つをTRUEにする

//π
#define PI 3.14159265359

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Move_Flg(int);
extern int Enemy_control();
extern int Enemy_Attack_Chose();
extern int Enemy_Attack_Move(int *);
extern int Enemy_Draw();
extern int Enemy_Score();
extern int Enemy_Hit();
//extern int Enemy_deg(int *);

//敵の弾関連の定義
extern int EnemyShot_Mgr();
extern int EnemyShot();
extern int EnemyShot_Move();
extern int EnemyShot_Move();
extern int EnemyShot_Draw();

extern int Enemy_Stage_clear();
extern int Enemy_Pos_Init_x(int);
extern int Enemy_Pos_Init_y(int);
extern int Enemy_State_Init(int);
extern int Enemy_End();


struct P_Enemy {
	int Type;   //0:黄色　1:赤　2:紫　3:青
	int x;	//座標
	int y;
	double fx;	//first_x 初期位置
	double fy;
	double nx;	//next_x 次のXの場所	
	double deg;	//角度
	double vct;
	double vct2;
	double speed;
	int anime;
	int anime_cnt;
	int mode;
	int Draw_Flg;
};	//Enemy Position

typedef struct {	//構造体
	int x;  //enemyのx座標
	int y;  //enemyのy座標
	bool Draw_Flg;
} S_EShot;



typedef enum {
	//MODE
	NONE,
	MOVE,
	ATTACK,
	DEL
}MODE;


//敵のタイプ
typedef enum {
	YELLOW,
	RED,
	PURPLE,
	BLUE
}TYPE;

//
typedef enum {
	SHOT_POINT_FIRST = 280,
	SHOT_POINT_SECOND  = 290,
	SHOT_POINT_THIRD  = 300,
	SHOT_POINT_FOURTH  = 310
}SHOTPOINT;

#endif