#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include"Actions\ActionAddEllipse.h" //v1
#include"Actions\ActionAddHexagon.h" //v1
#include "Actions\ActionSelect.h" //v2
#include "Actions/ChngDrawClrAction.h" //v2
#include "Actions/ChngFillClrAction.h" //v2
#include <string>
#include <string.h>
#include <iostream>


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;	
	
	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{		
		//1- Read user action
		ActType = pGUI->MapInputToActionType();

		//2- Create the corresponding Action
		Action *pAct = CreateAction(ActType);
		
		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();	

	}while(ActType != EXIT);
	
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType) 
{
	Action* newAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_SQUARE:
			newAct = new ActionAddSquare(this);
			break;

		case DRAW_ELPS: //v1
			newAct = new ActionAddEllipse(this);

			break;
		case DRAW_HEX: //v1
			newAct = new ActionAddHexagon(this);
			break;
		case DRAWING_AREA: //v2
			newAct = new ActionSelect(this);
			break;
			
			//Color Change Actions//
		case CHNG_DRAW_CLR: //v2
			newAct = new ChngDrawClrAction(this);
			break;

		case CHNG_FILL_CLR: //v2
			newAct = new ChngFillClrAction(this);
			break;

		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return NULL;
			break;
	}	
	return newAct;
}
//////////////////////////////////////////////////////////////////////
//Executes the created Action
void ApplicationManager::ExecuteAction(Action* &pAct) 
{	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
//Reads a color from the color toolbar
bool ApplicationManager::GetColor(color& inputColor) //v2
{

	bool isColor = true;
	//Creating the color toolbar
	pGUI->CreateColorToolBar();

	//Inputting draw color action
	ActionType inputColorAction = pGUI->MapInputToActionType();

	switch (inputColorAction) {
	case SET_BLACK:
		inputColor = BLACK;
		break;

	case SET_WHITE:
		inputColor = WHITE;
		break;

	case SET_RED:
		inputColor = RED;
		break;

	case SET_GREEN:
		inputColor = GREEN;
		break;

	case SET_BLUE:
		inputColor = BLUE;
		break;

	default:
		isColor = false;
	}

	//Restoring the draw toolbar
	pGUI->CreateDrawToolBar();

	return isColor;
}
////////////////////////////////////////////////////////////////////////////////////

CFigure *ApplicationManager::GetFigure(int x, int y) const////*****v2*****
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	
	for (int i=0;i<FigCount;i++)
	{
		if (FigList[i]->InPoint(x,y))
		{
			return FigList[i];
		}
	}

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for(int i=0; i<FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the interface
GUI *ApplicationManager::GetGUI() const
{	return pGUI; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pGUI;
	
}
