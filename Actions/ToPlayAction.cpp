#include "ToPlayAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"


ToPlayAction::ToPlayAction(ApplicationManager *pApp) :Action(pApp)
{}

void ToPlayAction::Execute() {
	//Get a Pointer to the Output Interface
	GUI* pGUI = pManager->GetGUI();

	pGUI->CreatePlayToolBar();
	pGUI->PrintMessage("You switched to Play Mode! Let's Play!");
}