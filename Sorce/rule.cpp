#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "rule.h"
#include "Sound.h"

int Rule;

int Rule_Init(){

	Rule = LoadGraph("Image/Rule.png");
	return 0;

}

int Rule_Dpct() {
	if (Keyboard_Get(KEY_INPUT_SPACE) == 1) {
		Scene_Mgr_ChangeScene(E_Scene_Game);
		SetGax_Sound(9);
		//SetGax_Sound(2);
		//SetGax_Sound(3);
	}
	return 0;

}

int Rule_Draw() {
	//DrawGraph(0, 0,Rule,TRUE);
	DrawRotaGraph(600, 370, 3.5, 0,Rule, TRUE);

	return 0;

}

int Rule_End() {
	return 0;
}