#include "CEllipse.h"

CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	secondPoint = P2;
	//v2******************
	pointsList[0]=P1;
	pointsList[1] = P2;
}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawEllipse(firstPoint, secondPoint, FigGfxInfo, Selected);


}

Point* CEllipse::getPoints() //v2
{
	return pointsList;
}
