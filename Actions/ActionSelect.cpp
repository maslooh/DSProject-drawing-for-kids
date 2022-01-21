#include "ActionSelect.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string>
#include <string.h>
#include <iostream>

ActionSelect::ActionSelect(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionSelect::Execute()
{
	Point P1;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();



	//Step 1 - Read data from the user

	//pGUI->PrintMessage("click on object to select it");

	////Read point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	CFigure* selectedFig = pManager->GetFigure(P1.x, P1.y);
	

	if (selectedFig)
	{
		if (selectedFig->IsSelected())
		{
			selectedFig->SetSelected(false);
		}
		else
		{
			selectedFig->SetSelected(true);
		}
	}
	else
	{
		pGUI->ClearStatusBar();
	}
}