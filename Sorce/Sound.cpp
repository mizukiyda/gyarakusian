#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//変数宣言
int Player_Shot_Sound;			         // 発射の効果音
int StartMenu_Sound;					 // スタートメニューのBGM


//初期化
int Sound_Init() {
	Player_Shot_Sound = LoadSoundMem("S_Galaxian/gax_Shot.wav");		// 発射音のパス指定と変数への代入
	StartMenu_Sound = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");	// ｽﾀｰﾄﾒﾆｭｰBGMのパス指定と代入
	return 0;
}

//計算
int Sound_Dpct() {

		//PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
	
	return 0;
}

//描写
int Sound_Draw() {

	return 0;
}

int Sound_End() {
	//無し
	return 0;
}