#include "ApplicationManager.h"
#include "Actions\ActionAddSquare.h"
#include"Actions\ActionAddEllipse.h" //v1
#include"Actions\ActionAddHexagon.h" //v1
#include "Actions\ActionSelect.h" //v2
#include "Actions/ActionChngDrawClr.h" //v2
#include "Actions/ActionChngFillClr.h" //v2
#include "Actions/ActionChngBkGrndClr.h"
#include "Actions/ActionDelete.h" //v3
#include "Actions/ActionSendBack.h" //****v3****
#include "Actions/ActionBringFront.h" //****v3****
#include "Actions/ToPlayAction.h"
#include"Actions/Save.h"//v3.1
#include"Actions/Exit.h"//v3.1
#include"Actions/Load.h"//v4
#include"Actions/Resize.h"//v4
#include"Actions/PickByColor.h"//***v5
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
		//Color Change Actions//
		case CHNG_DRAW_CLR:		//v4 eslam
			newAct = new ActionChngDrawClr(this);
			break;

		case CHNG_FILL_CLR:		//v4 eslam
			newAct = new ActionChngFillClr(this);
			break;

		case CHNG_BK_CLR:		//v4 eslam
			newAct = new ActionChngBkGrndClr(this);
			break;

		case DEL:
			newAct = new ActionDelete(this); //***v3***
			break;

		case SEND_BACK:
			newAct = new ActionSendBack(this); //fadwa ****v3****
			break;
		case BRNG_FRNT:
			newAct = new ActionBringFront(this); //fadwa ****v3****
			break;
		case TO_PLAY:
			newAct = new ToPlayAction(this);
			break;
		case SAVE:    //****v3.1****
			newAct = new Save(this, FigCount);
			break;
		case LOAD:
			newAct = new  Load(this);
			break;
		case RESIZE:  ///alaa
			newAct = new Resize(this);
			break;

		case P_BY_COLOR:   //***v5 
			newAct = new PickByColor(this);
			break;

		case EXIT:  //****v3.1*****
			///create ExitAction here
			newAct = new Exit(this);
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

CFigure* ApplicationManager::GetFigure(int x, int y) const////*****v2*****
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = FigCount - 1; i >= 0; i--)
	{
		if (FigList[i]->InPoint(x, y) && !FigList[i]->isShapeHiddin())//********v3*********//***v5
		{
			return FigList[i];
		}
	}
	return NULL;
}

//////////////////////////////////////
//********v4 reem*********
int ApplicationManager::getFigCount()const {
	return FigCount;
}
CFigure* ApplicationManager::getFigList(int i) const
{
	return FigList[i];
}

///////////////////////////////////////////////////////////////////////////////////////////
//**********v3.1***********updated maslooh
void ApplicationManager::DeleteFigure()
{
	int flag = 1;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = 0;
				for (int j = i; j < FigCount - 1; j++)
				{
					swap(FigList[j], FigList[j + 1]);
				}
				delete FigList[FigCount-1];
				FigList[FigCount-1] = NULL;
				this->FigCount--;
				i--;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////
//fadwa ****v3****
void ApplicationManager::SendFigureBack()
{
	int flag = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = 1;
			//selected figure to send it to back
			CFigure* tempFigure = FigList[i];
			//shift figures before it a forward step
			for (int j = i; j > 0; j--)
			{
				FigList[j] = FigList[j - 1];
			}
			//send a figure to the beginning of the figure list
			FigList[0] = tempFigure;
		}
	}
	if (!flag)
		pGUI->PrintMessage("please select a figure first");
}
///////////////////////////////////////////////////////////////////////////////////////////
//fadwa ****v3****
void ApplicationManager::BringFigureFront()
{
	int flag = 0;
	int maxToCheck = FigCount;
	for (int i = 0; i < maxToCheck; i++)
	{
		if (FigList[i]->IsSelected())
		{
			flag = 1;
			//selected figure to bring it to front
			CFigure* tempFigure = FigList[i];
			//shift figures after it a back step
			for (int j = i; j < FigCount-1; j++)
			{
				FigList[j] = FigList[j + 1];
			}
			//bring a figure to the end of the figure list
			FigList[FigCount-1] = tempFigure;
			//to not checked the current figure again
			maxToCheck--;
			i--;
		}
	}
	if (!flag)
		pGUI->PrintMessage("please select a figure first");
}


//**********v3**************
void ApplicationManager::changeFillColor(color FillClr)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngFillClr(FillClr);
		}
	}
}
//**********v3**************
void ApplicationManager::changeDrawColor(color drawClr)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->ChngDrawClr(drawClr);
		}
	}
}

//**********v3.1************** maslooh
void ApplicationManager::unselectAll()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->SetSelected(false);
	}
}

//**********v3.1**************
void ApplicationManager::SaveFig(ofstream& Out)   //Call the Save function for each Figure
{

	for (int i = 0; i < FigCount; ++i)
			FigList[i]->Save(Out);
}
//**********v3.1**************
string ApplicationManager::ConvertToString(color c)   //Convert from Color Type to String Type
{
	if (c == BLACK) return "BLACK";
	else if (c == WHITE) return "WHITE";
	else if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (c == MAGENTA) return "MAGENTA";
	else if (c == TURQUOISE) return "TURQUOISE";
	return "COLOR";
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{    ///alaa
	pGUI->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
	{
		if (!FigList[i]->isShapeHiddin())//********v3**********//****v4 reem
		{
			FigList[i]->DrawMe(pGUI); 	//Call Draw function (virtual member fn)
		}
	}	
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
/////////alaa////////
color ApplicationManager::ConvertToColor(string s)
{
	if (s == "BLACK")
		return BLACK;
	if (s == "BLUE")
		return BLUE;
	if (s == "WHITE")
		return WHITE;
	if (s == "RED")
		return RED;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "GREEN")
		return GREEN;
	if (s == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	if (s == "MAGENTA")
		return MAGENTA;
	if (s == "TURQUOISE")
		return TURQUOISE;
	return BLACK;
}


void ApplicationManager::ResetFiglist()
{
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i] = NULL;
		delete FigList[i];
	}
	FigCount = 0;
}

void ApplicationManager::Resize_figure(GUI* pGUI, float size) const {
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->Resize(pGUI, size);
		}
	}
}
/////////////////////////////////////////////
bool ApplicationManager::AnySelected() 
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			return true;
		}
	}
	return false;
}
