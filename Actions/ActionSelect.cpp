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
	//getting the last clcked point on the interface
	Point drawAreaPoint = pGUI->getLastPointClicked();
	//getting a pointer to a selected figure
	CFigure* selectedFig = pManager->GetFigure(drawAreaPoint.x, drawAreaPoint.y);
	
	if (selectedFig)//check if the pointer is not null
	{
		if (selectedFig->IsSelected())//case if the shape is already selected
		{
			selectedFig->SetSelected(false);
			pGUI->ClearStatusBar();
		}
		else 	//****v3.1*** maslooh
		{
			if (GetKeyState(VK_CONTROL)& 0x8000)//check if control buttom is down to use multible select 
			{
				selectedFig->SetSelected(true);
				selectedFig->PrintInfo(pGUI);
			}
			else //****v3.1*** maslooh
			{    //single shape select
				pManager->unselectAll();
				selectedFig->SetSelected(true);
				selectedFig->PrintInfo(pGUI);
			}
			
		}
	}
}