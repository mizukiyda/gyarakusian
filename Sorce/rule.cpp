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
	}
	return 0;

}

int Rule_Draw() {
	DrawGraph(0, 0,Rule,TRUE);
	return 0;

}

int Rule_End() {
	return 0;
}