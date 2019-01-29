#include "DxLib.h"
#include "Player.h"
#include "PlayerShot.h"
#include "Enemy.h"
#include "StartMenu.h"
#include "Scene_Mgr.h"

//変数宣言
int Credit_Sound;						 // クレジットからゲーム画面に映る時鳴る時の音
int Enemy_LastOne;						 // 敵が減ってくにつれ流す こっちが先
int Enemy_LastTwo;						 // 敵が減ってくにつれ流す　
int Enemy_Attack_Sound;					 // 敵が落ちている音
int Enemy_Hit_Sound;					 // 敵のヒット時の効果音
int HitGalaxian_Sound;					 // 黄色い敵を倒した時
int Player_Miss_Sound;					 // プレイヤーがやられたときの効果音
int Player_Shot_Sound;			         // 発射の効果音
int StartMenu_Sound;					 // スタートメニューのBGM
int Gax_Sound = 0;						 // 効果音のSwitch ここに送れば音が流れる

int volume;

 //初期化
int Sound_Init() {
	/*
	LoadSoundMem…メモリにサウンドを入れる
	パス指定
	*/
	Credit_Sound       = LoadSoundMem("S_Galaxian/gax_CreditSound.wav");    // クレジットSEのパス
	Enemy_LastOne      = LoadSoundMem("S_Galaxian/gax_Enemy_LastOne.wav");	// 敵が減ってくにつれ流す こっちが先
	Enemy_LastTwo      = LoadSoundMem("S_Galaxian/gax_Enemy_LastTwo.wav");	// 敵が減ってくにつれ流す
	Enemy_Attack_Sound = LoadSoundMem("S_Galaxian/gax_EnemyAttack.wav");	// 敵が落ちている音
	Enemy_Hit_Sound    = LoadSoundMem("S_Galaxian/gax_HitEnemy.wav");		// 敵を倒したときのSEのパス指定
	HitGalaxian_Sound  = LoadSoundMem("S_Galaxian/gax_HitGalaxian.wav");	// 黄色い敵を倒した時
	Player_Miss_Sound  = LoadSoundMem("S_Galaxian/gax_Miss.wav");			// プレイヤーがやられた時のSEのパス指定
	Player_Shot_Sound  = LoadSoundMem("S_Galaxian/gax_Shot.wav");			// 発射音のパス指定																
	StartMenu_Sound    = LoadSoundMem("S_Galaxian/gax_StartMusic.wav");		// ｽﾀｰﾄﾒﾆｭｰBGMのパス指定
	return 0;
}

//計算
int Sound_Dpct() {
	/*
	PlaySoundMem…メモリに入れたサウンドを再生
	NORMAL…ノーマル再生
	BACK……バックグラウンド再生
	LOOP……ループ再生
	*/

	switch (Gax_Sound) {

	case 1:
		// ゲーム画面に映る時なる時の音
		PlaySoundMem(Credit_Sound, DX_PLAYTYPE_BACK);	// 再生
		Gax_Sound = 0;	// もらった数字を0にしてからreturnする
		break;
	case 2:
		// 敵が減ってくにつれ流す	こっちが先
		PlaySoundMem(Enemy_LastOne, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(150, Enemy_LastOne);
		Gax_Sound = 0;
		break;
	case 3:
		// 敵が減ってくにつれ流す
		PlaySoundMem(Enemy_LastTwo, DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(150,Enemy_LastTwo);
		Gax_Sound = 0;
		break;
	case 4:
		// 敵が降ってきている効果音
		PlaySoundMem(Enemy_Attack_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 5:
		// 敵のヒット時の効果音
		PlaySoundMem(Enemy_Hit_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 6:
		// 黄色い敵を倒した時
		PlaySoundMem(HitGalaxian_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 7:
		// プレイヤーがやられたときの効果音
		PlaySoundMem(Player_Miss_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 8:
		// 発射の効果音
		PlaySoundMem(Player_Shot_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 9:
		// スタートメニューのBGM
		PlaySoundMem(StartMenu_Sound, DX_PLAYTYPE_BACK);
		Gax_Sound = 0;
		break;
	case 10:
		// 敵が降ってくる音を止める徐々に小さくする
		for (volume = 255; volume < 0; volume--) {
		
			ChangeVolumeSoundMem(volume, Enemy_Attack_Sound);
		}
		Gax_Sound = 0;
		break;
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