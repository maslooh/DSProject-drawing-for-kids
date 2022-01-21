#include "CSquare.h"

CSquare::CSquare(Point P1, int len, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
}
	

void CSquare::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawSquare(TopLeftCorner, length, FigGfxInfo, Selected);
	

}

bool CSquare::InPoint(int x, int y)//*****v2*******
{
	if (x >= TopLeftCorner.x && x <= (TopLeftCorner.x + length) && y >= TopLeftCorner.y && y <= (TopLeftCorner.y + length))
		return true;
	else
		return false;

}

void CSquare::PrintInfo(GUI* pGUI)//*****v2*******
{
	// print figure information
	string msg = "ID=";
	msg += to_string(ID);
	msg += ", start Point>> X=";
	msg += to_string(TopLeftCorner.x);
	msg += " Y=";
	msg += to_string(TopLeftCorner.y);
	msg += ", length=";
	msg += to_string(length);
	/*msg += ", area=";
	msg += GetArea();*/
	pGUI->PrintMessage(msg);
}