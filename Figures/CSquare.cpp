#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	//v2********************
	pointsList[0] = P1;
	pointsList[1].x = P1.x + len;
	pointsList[1].y = P1.y + len;
}

Point* CSquare::getPoints()//v2
{
	return pointsList;
}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
}

