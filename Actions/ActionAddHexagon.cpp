#include "ActionAddHexagon.h"
#include "..\Figures\CHexagon.h"

#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"

ActionAddHexagon::ActionAddHexagon(ApplicationManager* pApp) :Action (pApp)
{}

//Execute the action
void ActionAddHexagon::Execute()
{
	Point P1, P2;

	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();


	GfxInfo  hexaGfxInfo;
	hexaGfxInfo.isFilled = pGUI->getIsFilled();	//v2******default is not filled;
	//get drawing, filling colors and pen width from the interface
	hexaGfxInfo.DrawClr = pGUI->getCrntDrawColor();
	hexaGfxInfo.FillClr = pGUI->getCrntFillColor();
	hexaGfxInfo.BorderWdth = pGUI->getCrntPenWidth();


	//Step 1 - Read Square data from the user

	pGUI->PrintMessage("New hexagon: Click at first point");
	//Read 1st point and store in point P1
	pGUI->GetPointClicked(P1.x, P1.y);

	pGUI->PrintMessage("New hexagon: Click at second point");
	//Read 2nd point and store in point P2
	pGUI->GetPointClicked(P2.x, P2.y);

	pGUI->ClearStatusBar();


	//Step 2 - prepare hexagon data
	//User has entered two points P1&P2
	//2.1- Identify the Top left corner of the square
	Point topLeft;
	topLeft.x = P1.x < P2.x ? P1.x : P2.x;
	topLeft.y = P1.y < P2.y ? P1.y : P2.y;

	if (P1.y < UI.ToolBarHeight || P2.y < UI.ToolBarHeight
		|| P1.y>UI.height - UI.StatusBarHeight || P2.y>UI.height - UI.StatusBarHeight)
	{
		pGUI->PrintMessage("draw inside drawing area");
	}
	else
	{
		//2.2- Calcuate hexagon side legnth
		//The square side length would be the longer distance between the two points coordinates
		int topLength = abs(P1.x - P2.x);
		int height = abs(P1.y - P2.y);


		//Step 3 - Create a hexagon with the parameters read from the user
		CHexagon* R = new CHexagon(topLeft, topLength, height, hexaGfxInfo);
		//Step 4 - Add the hexagon to the list of figures
		pManager->AddFigure(R);
	}
}

