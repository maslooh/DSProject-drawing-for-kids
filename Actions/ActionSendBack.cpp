#include "ActionSendBack.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

//*****v2*******
ActionSendBack::ActionSendBack(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionSendBack::Execute()
{
	pManager->SendFigureBack();
}