#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"

int Score;		//playerからもらったスコアを保存していく
int Remain;		//Playerの残機の確認
int PLAYER_HIT_FLG;			//EnemyShotからplayerに当たった時のフラグをもらい、残機を「 1 」減らす作業をする

int UI_Init() {

	Score = 0;		//初期のスコア
	Remain = 3;		//初期の残機

	return 0;
}

int UI_Dpct() {

	Score = Player_Score();				//playerのPlayer_Score()に入っているスコアをもらう
	PLAYER_HIT_FLG = Player_Remain();		//Playerからもらったフラグを自分のフラグに入れる

	if (PLAYER_HIT_FLG == true) {		//もし true ならPlayerの残機を「　1　」減らす
		Remain--;
	}
	return 0;
}

int UI_Draw() {

	DrawFormatString(500, 0, GetColor(255, 0, 0), "SCORE:  %d", Score);			//スコアの表示
	DrawFormatString(900, 700, GetColor(255, 0, 0), "Remain:  %d", Remain);		//playerの残機の表示

	return 0;
}

int UI_End() {

	return 0;
}