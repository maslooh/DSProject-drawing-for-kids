#include "CEllipse.h"

CEllipse::CEllipse(Point P1, Point p2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	secondPoint = p2;
}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawEllipse(firstPoint, secondPoint, FigGfxInfo, Selected);

}

bool CEllipse::InPoint(int x, int y)//*****v2*******
{
	if (x >= firstPoint.x && x <= secondPoint.x && y >= firstPoint.y && y <= secondPoint.y)
		return true;
	else
		return false;

}

void CEllipse::PrintInfo(GUI* pGUI)//*****v2*******
{
	// print figure information
	string msg = "ID=";
	msg += to_string(ID);
	msg += ", center point>> X=";
	msg += to_string(firstPoint.x + (secondPoint.x - firstPoint.x) / 2);
	msg += " Y=";
	msg += to_string(firstPoint.y + (secondPoint.y - firstPoint.y) / 2);
	msg += ", radius=";
	msg += to_string((secondPoint.x - firstPoint.x) / 2);
	/*msg += ", area=";
	msg += GetArea();*/
	pGUI->PrintMessage(msg);
}