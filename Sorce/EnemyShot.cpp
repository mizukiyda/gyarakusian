#include "DxLib.h"
#include "EnemyShot.h"
#include"Player.h"
#include"Enemy.h"

#define EnemyCount 48				//enemyの敵の数

S_EShot ebullet[EnemyCount];		//構造体///主に座標

static int i,j;						//for文用
int Enemy_Shot_Flg = false;			//エネミーが球を打つ時のフラグ
int Enemy_Shot_Gyallaly[2];						// データハンドル格納用変数 画像表示に使用
int Enemy_None_Num;			// 画像のスタンバイ状態(静止状態)
int Enemy_Hit_Flg = false;			//エネミーの弾がplayerに当たった時のFlg
int px;								//player のx座標
int py;								//player のy座標

int Enemy_Shot_Pos(int *x, int *y,int num) {
	//エネミーからもらった座標をポインタに入れる

	*x = ebullet[num].x;
	*y = ebullet[num].y;
	return 0;
}

int EnemyShot_Init() {
	//初期化処理
	Enemy_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Enemy_Shot_Gyallaly); // 画像をロード
	Enemy_None_Num = 1;			// 画像のスタンバイ状態(静止状態)

	for (i = 0;i < EnemyCount;i++) {
		ebullet[i].x = Enemy_Pos_Init_x();					//enemyから弾が出るｘ座標をもらう
		ebullet[i].y = Enemy_Pos_Init_y();					//enemyから弾が出るｙ座標をもらう
	}
	return 0;
}

int EnemyShot_Dpct( ) {
	//計算処理

	px = Player_Pos_Init_x();				//playerからｘ座標をもらう
	py = Player_Pos_Init_y();				//playerからy座標をもらう

	Enemy_Shot_Flg = Enemy_Move();

	if (Enemy_Shot_Flg == true) {			//もしenemyが弾を打つなら
		enemyShot(1);
	}
	return 0;
}

int enemyShot(int num) {
	//エネミーの弾の発射処理

	for (i = 0;i < 2;i++) {										//弾を二つ打っている
		ebullet[i].y += 500;

		if (px == ebullet[num].x && py == ebullet[num].y) {		//弾がPlayerにヒットした　→　弾が消える
			Enemy_Hit();
			Enemy_Shot_Flg = false;
		}

		if (ebullet[num].y >= 600) {							//エネミーの弾が画面外に出たら消える　→　Flgが再びfalseになる

			Enemy_Shot_Flg = false;
		}
	}
	return Enemy_Shot_Flg;
}

int Enemy_Hit() {
	//弾がヒットしたらPlayerに渡す →　Playerが爆破
	Enemy_Hit_Flg = true;

	return Enemy_Hit_Flg;
}


int EnemyShot_Draw() {
	//描写処理

	for (i = 0;i < EnemyCount;i++) {
		for (j = 0;j < 2;j++) {											//弾を二つ打つ
			if (Enemy_Shot_Flg == true) {
				DrawRotaGraph(ebullet[i].x + 3, ebullet[i].y - 25, 4.0, 0.0, Enemy_Shot_Gyallaly[Enemy_None_Num], true);// データハンドルを使って画像を描画
			}
		}
		if(Enemy_Shot_Flg == false)		
		{
			DrawRotaGraph(ebullet[i].x + 3, ebullet[i].y - 25, 4.0, 0.0, Enemy_Shot_Gyallaly[Enemy_None_Num], false);		// データハンドルを使って画像を描画を消す
		}
		DrawFormatString(0, 500, GetColor(255, 255, 255), "ebullet.x座標  %d\nebullet.y座標  %d", ebullet[i].x, ebullet[i].y);
	}
	return 0;
}

int EnemyShot_End() {
	//終了処理
	return 0;
}