#include "CHexagon.h"
#include <iostream>
#include <string>
//fadwa ****v3****
CHexagon::CHexagon(Point P1, int len, int _height, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	TopLeftCorner = P1;
	length = len<10 ? -10 : len;
	height = _height<18 ? -18 : _height;
	figureName = "HEXAGON";
}


void CHexagon::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawHexagon(TopLeftCorner, length, height, FigGfxInfo, Selected);
}

bool CHexagon::InPoint(int x, int y) //*****v2*******
{
	// if inside inner rectangle
	if (x >= TopLeftCorner.x && x <= TopLeftCorner.x + length && y >= TopLeftCorner.y && y <= TopLeftCorner.y + height)
		return true;
	///////////////////////
	float sideTrianglesArea = AreaTriangle(TopLeftCorner.x, TopLeftCorner.y, TopLeftCorner.x, TopLeftCorner.y + height, TopLeftCorner.x - 0.5 * length, TopLeftCorner.y + 0.5 * height);
	// if inside left side triangle
	// left triangle >> (x,y), (x, y+h), (x-0.5l, y+0.5h)
	float Area1 = AreaTriangle(x, y, TopLeftCorner.x, TopLeftCorner.y + height, TopLeftCorner.x - 0.5 * length, TopLeftCorner.y + 0.5 * height);
	float Area2 = AreaTriangle(TopLeftCorner.x, TopLeftCorner.y, x, y, TopLeftCorner.x - 0.5 * length, TopLeftCorner.y + 0.5 * height);
	float Area3 = AreaTriangle(TopLeftCorner.x, TopLeftCorner.y, TopLeftCorner.x, TopLeftCorner.y + height, x, y);
	if (Area1 + Area2 + Area3 == sideTrianglesArea)
		return true;
	// if inside right side triangle
	// right triangle >> (x+l,y), (x+l, y+h), (x+1.5l, y+0.5h)
	Area1 = AreaTriangle(x, y, TopLeftCorner.x + length, TopLeftCorner.y + height, TopLeftCorner.x + 1.5 * length, TopLeftCorner.y + 0.5 * height);
	Area2 = AreaTriangle(TopLeftCorner.x + length, TopLeftCorner.y, x, y, TopLeftCorner.x + 1.5 * length, TopLeftCorner.y + 0.5 * height);
	Area3 = AreaTriangle(TopLeftCorner.x + length, TopLeftCorner.y, TopLeftCorner.x + length, TopLeftCorner.y + height, x, y);
	if (Area1 + Area2 + Area3 == sideTrianglesArea)
		return true;
	
	return false;
}

float CHexagon::AreaTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) * 0.5);
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
	msg += ", top & bottom length=";
	msg += to_string(length);
	msg += ", height=";
	msg += to_string(height);
	msg += ", area=";
	msg += to_string(GetArea());
	pGUI->PrintMessage(msg);
}

int CHexagon::GetArea()
{
	return (length*height + height*0.5*length);
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
	this->FigGfxInfo.BorderWdth = 3;

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
CHexagon::CHexagon() 
{
	this->Selected = false;
	this->isHidden = false;
};
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