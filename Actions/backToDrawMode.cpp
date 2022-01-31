#include "backToDrawMode.h"
#include"../ApplicationManager.h"
#include "../GUI/GUI.h"
backToDrawMode::backToDrawMode(ApplicationManager* pApp) :Action(pApp){}

void backToDrawMode::Execute() {
	GUI* pGUI = pManager->GetGUI();
	pGUI->CreateDrawToolBar();
	pGUI->PrintMessage("Welcome to draw mode ^_^");
}