#include "ActionChngDrawClr.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionChngDrawClr::ActionChngDrawClr(ApplicationManager *pApp) :Action(pApp)
{}

void ActionChngDrawClr::Execute() {
	//Get a Pointer to the Input / Output Interfaces
	GUI* pGUI = pManager->GetGUI();
	IsSelected = pManager->AnySelected();

	//Reads the input draw color
	if (!pManager->GetColor(DrawClr))
		IsColor = false;
	else
		IsColor = true;

	if (IsColor) {
		if (IsSelected)
		{
			pManager->changeDrawColor(DrawClr);
		}
		else
		{
			pGUI->setCrntDrawColor(DrawClr);
		}
	}

}