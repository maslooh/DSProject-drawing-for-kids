#include "ActionDelete.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include <string>
#include <string.h>
#include <iostream>
//*****************************v3***********************************
ActionDelete::ActionDelete(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionDelete::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->ClearDrawArea();
	pManager->DeleteFigure();
}