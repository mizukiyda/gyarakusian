#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY

#define N 5
#define NUMSHOT 30
#define REMITBLOW 10
#define EnemyCount 48
//��ʃT�C�Y700�F700
#define CENTER_X 370
#define CENTER_Y 350

#define PUSH_BLOW(i,E_X,E_Y) 	tmpBlow[i].x = E_X; tmpBlow[i].y = E_Y; blow[i].Blow_Cnt = 0; tmpBlow[i].onActive = true;
#define PUSH_SHOT(i,E_X,E_Y)    tmpEnemyShot[i].x = E_X; tmpEnemyShot[i].y = E_Y; tmpEnemyShot[i].onActive = true;

//�I���̃��[�h
#define MODE_DOWN 1	//�I�΂ꂽ������̂܂܉��Ɍ�������TRUE�ɂ��Ă���
#define MODE_NEXT 2	//�I�΂ꂽ��̎��̗�̏�2��TRUE�ɂ���

//��
#define PI 3.14159265359

extern int Enemy_Init();
extern int Enemy_Move();
extern int Enemy_Move_Flg(int);
extern int Enemy_Control();
extern int Enemy_Attack_Chose();
extern int Enemy_Attack_Move(int);
extern int Enemy_Draw();
//�X�R�A�֐�
extern int Enemy_Score(int);
//�����蔻��
extern int Enemy_Hit();

//�G�̃A�j���[�V�����֘A�ƍU�����̉~�^��
extern int Enemy_POINT();
extern int Enemy_Satellite(int);
extern int Enemy_Deg(int);
extern int Enemy_Animetion(int);

//�G�̒e�֘A�̒�`
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
	//0:���F�@1:�ԁ@2:���@3:��
	int Type;
	//���W
	double x;
	double y;
	//first_x �����ʒu
	double fx;
	double fy;
	//next_x ����X�̏ꏊ
	double nx;
	//�p�x
	double deg;
	//�v���C���[�ƓG�̊p�x
	double deg2;
	//�ڕW�_
	double pt_x;
	double pt_y;
	//vector
	double vct_x;
	double vct_y;
	//�ꎞ�I�ɕێ����Ă���
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
			�G�̍U�����̈ړ��|�C���g
			�S����4��
			1�ځF��ʒ�����ɔz�u����B
			2�ځF��ʒ�����,�E�Ɍ������ĐU��q�A�����Œ��˕Ԃ�
			3�ځF��ʒ�����,���Ɍ������ĐU��q�A�����Œ��˕Ԃ�
			4�ځF�v���C���[�ɂ��ĉ��
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

	//�G�̓����A��]
	R_ROLL,
	L_ROLL,
	//�G�̓����A�ǔ�
	TRACK,
	//�ڕW�_�̈ʒu�ς�
	CHANGE,
	//�ŏ��̓�������
	FIRST,
	//�Ȃ���Ƃ�
	R_CURVE,
	L_CURVE,
	BACK

}MODE;

//�G�̃^�C�v
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