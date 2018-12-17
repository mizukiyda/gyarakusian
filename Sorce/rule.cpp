#include "StartMenu.h"
#include "Dxlib.h"
#include "Keyboard.h"
#include "Scene_Mgr.h"
#include "rule.h"
#include "Sound.h"

int Rule;

int Rule_Init(){

	Rule = LoadGraph("Image/Rule.png");
}

int Rule_Dpct() {
	
}

int Rule_Draw() {
	DrawGraph(0, 0,Rule,TRUE);
}

int Rule_End() {

}