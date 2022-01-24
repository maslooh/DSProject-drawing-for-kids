#include "ActionBringFront.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

//*****v2*******
ActionBringFront::ActionBringFront(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionBringFront::Execute()
{
	pManager->BringFigureFront();
}