#include"dxlib.h"
#include"PlayerShot.h" 
#include"Enemy.h"
#include"Player.h"
#include"Sound.h"

//ショットの構造体
S_PShot pbullet;

//どのタイプの敵を倒したかの判別
S_EnemyType Mode;

int a;
int Player_Shot_Flg = 0;					//プレイヤーが球を打つ時のフラグ
int Player_Shotcnt_y;						//弾を動かす
int ex[EnemyCount];							//enemyの数分のｘ座標
int ey[EnemyCount];							//enemyの数分のｙ座標
bool e_draw[EnemyCount];					//enmeyの生存確認
bool Player_Hit_Flg[EnemyCount] = {Draw_ON};	//enmeyの生存確認で当たっていない状態
int Player_Shot_Gyallaly[2];				// 画像格納変数
int Player_None_Num;						// 画像のスタンバイ状態(静止状態)

/****初期化****/
int Playershot_Init() {   //あいうえお

	Player_Shot_Gyallaly[2];
	LoadDivGraph("Image/Galaxian_OBJ_bullet.png", 2, 2, 1, 11, 6, Player_Shot_Gyallaly);		// 画像をロード
	Player_None_Num = 0;																		//スタンバイ状態の向いてる方向を正面へするための画像番号1
	for (int i = 0;i < EnemyCount;i++) {														
		Player_Hit_Flg[i] = Draw_ON;																//初期化処理として全員当たっていない
	}

	return 0;
}

/****計算****/
int PlayerShot_Dpct() {
	for (a = 0;a < EnemyCount;a++) {
		ex[a] = Enemy_Pos_Init_x(a);										//enemyのx座標
		ey[a] = Enemy_Pos_Init_y(a);										//enemyのy座標
		e_draw[a] = Enemy_State_Init(a);									//enemy の生存
	}

	if (Player_Shot_Flg == 1) {												//Playerからポインタでもらう
		pbullet.x = Player_Pos_Init_x();									//弾のx座標をPlayerのx座標に格納する
		pbullet.y = Player_Pos_Init_y();									//弾のy座標をPlayerのy座標に格納する
		Player_Shot_Flg = 2;
	}
	//フラグが2になったら弾を上に撃つ
	if (Player_Shot_Flg == 2) {
		pbullet.y -= 5;														//弾の座標が0まで行ったらフラグを0にして消す		
	}

	if (pbullet.y <= 0) {													//もし弾が画面外に行ったらfalsreにする
		Player_Shot_Flg = 0;
	}

	for (a = 0;a < EnemyCount;a++) {
		if (ex[a] - 25 <= pbullet.x - 10 && pbullet.x + 10 <= ex[a] + 25 &&			//enemyとの当たり判定
			pbullet.y == ey[a] + 25 && e_draw[a] == Draw_ON) {
			Player_Shot_Flg = false;												//弾を消す
			Player_Hit_Flg[a] = Draw_OFF;												//この敵に当たったというフラグ
			Player_HIT(a);															//個の敵に当たったというポインタを入れる	
			pbullet.y = 0;															//当たったらPlayerの中に格納される
			SetGax_Sound(5);							//enemyがやられた時の音(ここではなかった)

		}
	}
	return Player_Shot_Flg;
}

//Enemyへの当たり判定
int Player_HIT(int num) {

	return Player_Hit_Flg[num];
}

int Playershot_Draw() {

	if (Player_Shot_Flg != 0) {
		//画像の拡大表示
		DrawRotaGraph(pbullet.x + 3, pbullet.y - 25, 4.0, 0.0, Player_Shot_Gyallaly[Player_None_Num], true);
	}
	return 0;
}


void SetPlayer_Shot_Flg(int flag) {										//ショットに関するポインタ
	Player_Shot_Flg = flag;
}

/**********************************　終了(一回)　******************************************/
int PlayerShot_End()
{
	//No Script
	return 0;
}
