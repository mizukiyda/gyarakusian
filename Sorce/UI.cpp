#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"

//担当　小出

int Score;					//playerからもらったスコアを保存していく
int Remain;					//Playerの残機の確認
int PLAYER_HIT_FLG;			//EnemyShotからplayerに当たった時のフラグをもらい、残機を「 1 」減らす作業をする
int SCORE_Image, REMAIN_Image;
int UI_Init() {

	Score = 0;		//初期のスコア
	Remain = 3;		//初期の残機

	SCORE_Image = LoadGraph("Image/SCORE.png");
	REMAIN_Image = LoadGraph("Image/REMAIN.png");

	return 0;
}

int UI_Dpct() {

	Score = Player_Score();					//playerのPlayer_Score()に入っているスコアをもらう
	PLAYER_HIT_FLG = Player_Remain();		//Playerからもらったフラグを自分のフラグに入れる

	if (PLAYER_HIT_FLG == true) {			//もし true ならPlayerの残機を「　1　」減らす
		Remain--;
	}
	return 0;
}

int UI_Draw() {

	DrawGraph(200, 0, SCORE_Image, TRUE);			 // データハンドルを使って画像を描画
	DrawGraph(750, 650, REMAIN_Image, TRUE);		 // データハンドルを使って画像を描画

	return 0;
}

int UI_End() {

	return 0;
}