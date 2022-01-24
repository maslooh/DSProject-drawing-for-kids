#include "CHexagon.h"

//fadwa ****v3****
CHexagon::CHexagon(Point P1, int len, int _height, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len;
	height = _height;
}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, length, height, FigGfxInfo, Selected);
}

bool CHexagon::InPoint(int x, int y) //*****v2*******
{
	if (x >= TopLeftCorner.x - 0.5*length && x <= TopLeftCorner.x + 1.5*length && y >= TopLeftCorner.y && y < (TopLeftCorner.y + height))
		return true;
	else
		return false;
}

void CHexagon::PrintInfo(GUI* pGUI) //*****v2*******
{
	// print figure information
	string msg = "ID=";
	msg += to_string(ID);
	msg += ", center Point>> X=";
	msg += to_string(TopLeftCorner.x + 0.5*length);
	msg += " Y=";
	msg += to_string(TopLeftCorner.y + 0.5*height);
	msg += ", length=";
	msg += to_string(length);
	/*msg += ", area=";
	msg += GetArea();*/
	pGUI->PrintMessage(msg);
}