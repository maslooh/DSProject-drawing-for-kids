#include "ActionSelect.h"

#include "..\ApplicationManager.h"
#include <Windows.h>
#include "..\GUI\GUI.h"
#include <string>
#include <string.h>
#include <iostream>
//*****v2*******
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
	//****v3.1*** maslooh
	Point drawAreaPoint = pGUI->getLastPointClicked();
	
	CFigure* selectedFig = pManager->GetFigure(drawAreaPoint.x, drawAreaPoint.y);
	
	if (selectedFig)
	{
		if (selectedFig->IsSelected())
		{
			selectedFig->SetSelected(false);
			pGUI->ClearStatusBar();
		}
		else 	//****v3.1*** maslooh
		{
			if (GetKeyState(VK_CONTROL)& 0x8000)
			{
				selectedFig->SetSelected(true);
				selectedFig->PrintInfo(pGUI);
			}
			else //****v3.1*** maslooh
			{
				pManager->unselectAll();
				selectedFig->SetSelected(true);
				selectedFig->PrintInfo(pGUI);
			}
			
		}
	}
}