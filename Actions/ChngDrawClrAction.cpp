#include "ChngDrawClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ChngDrawClrAction::ChngDrawClrAction(ApplicationManager *pApp) :Action(pApp)
{}

void ChngDrawClrAction::Execute() {
	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();

	//Reads the input draw color
	if (!pManager->GetColor(DrawClr))
		IsColor = false;
	else
		IsColor = true;

	if (IsColor) {
		pGUI->setCrntDrawColor(DrawClr);
		pManager->changeDrawColor(DrawClr);
	}

}