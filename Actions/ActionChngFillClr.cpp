#include "ActionChngFillClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionChngFillClr::ActionChngFillClr(ApplicationManager *pApp) :Action(pApp)
{}

void ActionChngFillClr::Execute() {
	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();
	IsSelected = pManager->AnySelected();

	//Reads the input draw color
	if (!pManager->GetColor(FillClr))
		IsColor = false;
	else
		IsColor = true;

	if (IsColor) {
		if (IsSelected)
		{
			pManager->changeFillColor(FillClr);
		}
		else
		{
			pGUI->setIsFilled(true);
			pGUI->setCrntFillColor(FillClr);
		}
	}
}
