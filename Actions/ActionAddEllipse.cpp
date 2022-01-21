#include "ActionAddEllipse.h"
#include "..\Figures\CEllipse.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddEllipse::ActionAddEllipse(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionAddEllipse::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo ellipGfxInfo;
	ellipGfxInfo.isFilled = pGUI->getIsFilled();	//v2******default is not filled
	//get drawing, filling colors and pen width from the interface
	ellipGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	ellipGfxInfo.FillClr = pGUI->getCrntFillColor();
	ellipGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	pGUI->PrintMessage("New ellipse: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New ellipse: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->ClearStatusBar();
	if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight
		|| P1.y>UI.height - UI.StatusBarHeight || P2.y>UI.height - UI.StatusBarHeight)
	{
		pGUI->PrintMessage("draw inside drawing area");
	}
	else 
	{
		//Step 3 - Create a ellipse with the parameters read from the user
		CEllipse* E = new CEllipse(P1, P2, ellipGfxInfo);

		//Step 4 - Add the ellipse to the list of figures
		pManager->AddFigure(E);
	}
}
