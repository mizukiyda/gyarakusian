#include "DxLib.h"
#include "UI.h"
#include "Playershot.h"
#include"Player.h"
#include"Enemy.h"

//担当　小出

int Score;					//playerからもらったスコアを保存していく
int Remain;					//Playerの残機の確認
int tmp_Remain;			//EnemyShotからplayerに当たった時のフラグをもらい、残機を「 1 」減らす作業をする
int SCORE_Image, REMAIN_Image, UI_Image;
int Stock[3];
int UI_Init() {

	Score = 0;		//初期のスコア
	Remain = 3;		//初期の残機

	SCORE_Image = LoadGraph("Image/SCORE.png");
	REMAIN_Image = LoadGraph("Image/REMAIN.png");
	//UI_Image = LoadGraph("Image/Galaxian_OBJ_other.png");
	LoadDivGraph("Image/Galaxian_OBJ_other.png", 3, 3, 1, 18, 20, Stock,true);
	//自機画像の分割読み込み　画像名　分割総数　横の分割数　縦の分割数　分割した画像のx,y
	//分割読み込みして得たグラフィックハンドルを保存するint型の配列へのポインタ　透明の反映


		return 0;
	
}

int UI_Dpct() {

	Score = Enemy_Score();					//playerのPlayer_Score()に入っているスコアをもらう
	tmp_Remain = Player_Remain();		//Playerからもらったフラグを自分のフラグに入れる

	return 0;

}

int UI_Draw() {	

	DrawGraph(200, 0, SCORE_Image, TRUE);			 // データハンドルを使って画像を描画
	DrawGraph(750, 650, REMAIN_Image, TRUE);		 // データハンドルを使って画像を描画
	DrawExtendGraph(50, 150,100,200, Stock[0], true);		 // データハンドルを使って画像を描画
	//Extendを付けると拡大表示できる サイズは指定する必要がある
	
	return 0;

}

int UI_End() {

	return 0;
}