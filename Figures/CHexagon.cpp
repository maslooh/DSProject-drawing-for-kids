#include "CHexagon.h"

CHexagon::CHexagon(Point P1, int len, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	//v2**********************
	pointsList[0].x = P1.x - len * 0.5;
	pointsList[0].y = P1.y;
	pointsList[1].x = pointsList[0].x+len*2;
	pointsList[1].y = pointsList[0].y + len * 2;
}

Point* CHexagon::getPoints() //v2
{
	return pointsList;
}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, length, FigGfxInfo, Selected);
}
