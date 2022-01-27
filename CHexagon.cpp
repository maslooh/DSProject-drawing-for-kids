#include "CHexagon.h"
#include <iostream>
#include <string>
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

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "Hexagon\t" << this->ID << "\t" << this->TopLeftCorner.x << "\t" << this->TopLeftCorner.y << "\t"
		<< this->length << "\t" << this->height << "\t"
		<< this->colorToString(this->FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		OutFile << this->colorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NON-FILLED\n";
	//OutFile << this->FigGfxInfo.Resize_Factor << "\n";	
}
//////////alaaa
void CHexagon::SetID(int ind)
{
	ID = ind;
}

void CHexagon::Load(ifstream& Infile)
{
	this->FigGfxInfo.BorderWdth = 5;
	this->Selected = false;
//	SetSelected(false) ;
	string s;
	Infile >> this->ID >> this->TopLeftCorner.x >> this->TopLeftCorner.y
		>> this->length >> this->height;

	Infile >> s;
	this->FigGfxInfo.DrawClr = GetStrinColor(s);

	Infile >> s;
	if (!(s == "NON-FILLED"))
		this->FigGfxInfo.FillClr = GetStrinColor(s);
	else
		this->FigGfxInfo.isFilled = false;


}
CHexagon::CHexagon() {};
void CHexagon::Resize(GUI* pGUI, float size)
{

	float length_test = length * size;
	float height_test = height * size;
	if((TopLeftCorner.y + height_test) > UI.height - UI.StatusBarHeight || (TopLeftCorner.x + length_test * 1.5) > UI.width + UI.wx || (TopLeftCorner.x + length_test * 0.5) < UI.wx)
	{

		pGUI->PrintMessage("Hexagon size will be more than Dwawing Area");
		Sleep(1000);
	}
	else if (length_test < 20 || height_test < 20)
	{
		pGUI->PrintMessage("Hexagon size will be very small");
		Sleep(1000);
	}

	else
	{
		length = length_test;
		height = height_test;
		//PrintInfo(pGUI);
	}

}