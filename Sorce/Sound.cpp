#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//#define SE_CNT 9		//効果音の数

//変数宣言
int Credit_Sound;						 // クレジットからゲーム画面に映る時なる時の音
int Enemy_LastOne;						 // 謎SE
int Enemy_LastTwo;						 // 謎SE 2
int Enemy_Attack_Sound;					 // 敵の発射効果音
int Enemy_Hit_Sound;					 // 敵のヒット時の効果音
int HitGalaxian_Sound;					 // 謎SE 3
int Player_Miss_Sound;					 // プレイヤーがやられたときの効果音
int Player_Shot_Sound;			         // 発射の効果音
int StartMenu_Sound;					 // スタートメニューのBGM

int Gax_Sound = 0;						 // 効果音のSwitch

/*
int PlaySound_Payer() {					//Prayer
	PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
	return 0;
}
*/

//初期化
int Sound_Init() {
	/*
	switch (){

	case 1:

		// クレジットからゲーム画面に映る時なる時の音
		*/
		Credit_Sound = LoadSoundMem("S_Galaxian/gax_CreditSound.wav");			// クレジットSEのパス
		/*break;
	case 2:

		// 謎SE*/
		Enemy_LastOne = LoadSoundMem("S_Galaxian/gax_Enemy_LastOne.wav");		// NAZO
		/*break;
	case 3:

		// 謎SE 2*/
		Enemy_LastTwo = LoadSoundMem("S_Galaxian/gax_Enemy_LastTwo.wav");		// NAZO
		/*break;
	case 4:

		// 敵の発射効果音*/
		Enemy_Attack_Sound = LoadSoundMem("S_Galaxian/gax_EnemyAttack.wav");	// 敵の発射音のパス指定
		/*break;
	case 5:

		// 敵のヒット時の効果音*/
		Enemy_Hit_Sound = LoadSoundMem("S_Galaxian/gax_HitEnemy.wav");			// 敵を倒したときのSEのパス指定
		/*break;
	case 6:

		// 謎SE 3*/
		HitGalaxian_Sound = LoadSoundMem("S_Galaxian/gax_HitGalaxian.wav");		// NAZO
		/*break;
	case 7:

		// プレイヤーがやられたときの効果音*/
		Player_Miss_Sound = LoadSoundMem("S_Galaxian/gax_Miss.wav");			// プレイヤーがやられた時のSEのパス指定
		/*break;
	case 8:

		// 発射の効果音*/
		Player_Shot_Sound = LoadSoundMem("S_Galaxian/gax_Shot.wav");			// 発射音のパス指定
		/*break;
	case 9:

		// スタートメニューのBGM*/
		StartMenu_Sound = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");		// ｽﾀｰﾄﾒﾆｭｰBGMのパス指定
		/*break;

	}*/
	return 0;
}

//計算
int Sound_Dpct() {

	/*
	switch (Gax_Sound) {

	case 1:

		// クレジットからゲーム画面に映る時なる時の音
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);
		break;
	case 2:

		// 謎SE
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_BACK);
		break;
	case 3:

		// 謎SE 2
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_BACK);
		break;
	case 4:

		// 敵の発射効果音
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
		break;
	case 5:

		// 敵のヒット時の効果音
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
		break;
	case 6:

		// 謎SE 3
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
		break;
	case 7:

		// プレイヤーがやられたときの効果音
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
		break;
	case 8:

		// 発射の効果音
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
		break;
	case 9:

		// スタートメニューのBGM
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
		break;
	}
	*/

	if (Gax_Sound == 1) {
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 2) {
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 3) {
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 4) {
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 5) {
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 6) {
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 7) {
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
	}
	if (Gax_Sound == 8) {
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_NORMAL);
	}
	if (Gax_Sound == 9) {
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
	}

	return Gax_Sound;
}

void SetGax_Sound(int flag) {			// ここに代入したらswitchに入る
	Gax_Sound = flag;					// switchに代入
}

//描写
int Sound_Draw() {

	return 0;
}


int Sound_End() {
	//無し
	return 0;
}