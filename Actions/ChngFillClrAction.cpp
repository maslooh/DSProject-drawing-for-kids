#include "ChngFillClrAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ChngFillClrAction::ChngFillClrAction(ApplicationManager *pApp) :Action(pApp)
{}

void ChngFillClrAction::Execute() {
	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();

	//Reads the input draw color
	if (!pManager->GetColor(FillClr))
		IsColor = false;
	else
		IsColor = true;

	if (IsColor) {
		pGUI->setIsFilled(true);
		pGUI->setCrntFillColor(FillClr);
	}

}
