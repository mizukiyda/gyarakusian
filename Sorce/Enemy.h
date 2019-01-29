#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY

#define N 5
#define NUMSHOT 30
#define REMITBLOW 10
#define EnemyCount 48
//画面サイズ700：700
#define CENTER_X 370
#define CENTER_Y 350

#define PUSH_BLOW(i,E_X,E_Y) 	tmpBlow[i].x = E_X; tmpBlow[i].y = E_Y; blow[i].Blow_Cnt = 0; tmpBlow[i].onActive = true;
#define PUSH_SHOT(i,E_X,E_Y)    tmpEnemyShot[i].x = E_X; tmpEnemyShot[i].y = E_Y; tmpEnemyShot[i].onActive = true;

//選択のモード
#define MODE_DOWN 1	//選ばれた列をそのまま下に向かってTRUEにしていく
#define MODE_NEXT 2	//選ばれた列の次の列の上2つをTRUEにする

//π
#define PI 3.14159265359

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Move_Flg(int);
extern int Enemy_Control();
extern int Enemy_Attack_Chose();
extern int Enemy_Attack_Move(int);
extern int Enemy_Draw();
//スコア関数
extern int Enemy_Score(int);
//当たり判定
extern int Enemy_Hit();

//敵のアニメーション関連と攻撃時の円運動
extern int Enemy_POINT();
extern int Enemy_Satellite(int);
extern int Enemy_Deg(int);
extern int Enemy_Animetion(int);

//敵の弾関連の定義
extern int EnemyShot_Mgr();
extern int EnemyShot_Move();
extern int EnemyShot_Move();
extern int EnemyShot_Draw();

extern int Enemy_Stage_Clear();
extern int Enemy_Pos_Init_x(int);
extern int Enemy_Pos_Init_y(int);
extern int Enemy_State_Init(int);
extern int Enemy_End();

extern int Create_Blow();

extern int Cnt_Yellow();
extern int Cnt_Red();
extern int Cnt_Pourple();
extern int Cnt_Blue();


typedef struct {
	//0:黄色　1:赤　2:紫　3:青
	int Type;
	//座標
	double x;
	double y;
	//first_x 初期位置
	double fx;
	double fy;
	//next_x 次のXの場所
	double nx;
	//角度
	double deg;
	//プレイヤーと敵の角度
	double deg2;
	//目標点
	double pt_x;
	double pt_y;
	//vector
	double vct_x;
	double vct_y;
	//一時的に保持しておく
	double cp_x;
	double cp_y;

	double speed;
	int anime;
	int anime2;

	int anime_cnt;
	int mode;
	int A_Mode;
	int onActive;
}P_Enemy;	//Enemy Position


			/********************************
			敵の攻撃時の移動ポイント
			全部で4つ
			1つ目：画面中央上に配置する。
			2つ目：画面中央部,右に向かって振り子、中央で跳ね返る
			3つ目：画面中央部,左に向かって振り子、中央で跳ね返る
			4つ目：プレイヤーについて回る
			*********************************/
typedef struct {
	double x;
	double y;
	int vct_x;
	int vct_y;
	int vct;
	double basis_x;
	double basis_y;
	int remit_x;
	int remit_y;
	double deg;
	double rad;
}E_POINT;

typedef struct {
	int first_shot;
	int second_shot;
	int third_shot;
	int fourth_shot;
}SHOT_FLAG;

typedef struct {
	int x;
	int y;
	bool onActive;
}POS;

typedef struct {
	int x;
	int y;
	int Blow_Cnt;
	bool onActive;
}Blow;

typedef enum {
	RIGHT = 1,
	LEFT = -1,
	UP = 2,
	DOWN = -2
}VECTORE;

typedef enum {
	//MODE
	NONE = -1,
	MOVE,
	ATTACK,
	DEL,

	//敵の動き、回転
	R_ROLL,
	L_ROLL,
	//敵の動き、追尾
	TRACK,
	//目標点の位置変え
	CHANGE,
	//最初の動きだし
	FIRST,
	//曲がるとき
	R_CURVE,
	L_CURVE,
	BACK

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
	SHOT_POINT_SECOND = 360,
	SHOT_POINT_THIRD = 440,
	SHOT_POINT_FOURTH = 520
}SHOTPOINT;
#endif