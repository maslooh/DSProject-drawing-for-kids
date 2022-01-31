#include "CEllipse.h"
#include <iostream>
#include <string>
CEllipse::CEllipse(Point P1, Point p2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	secondPoint = p2;
	figureName = "ELLIPSE";
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
//******v3.1****** amany
void CEllipse::Save(ofstream& OutFile)      //Write yourself on the file
{
	OutFile << "Ellipse\t" << ID << "\t" << this->firstPoint.x << "\t" << this->firstPoint.y << "\t"
		<< this->secondPoint.x << "\t" << this->secondPoint.y << "\t"
		<< this->colorToString(this->FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		OutFile << this->colorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NON-FILLED\n";
	//OutFile << this->FigGfxInfo.Resize_Factor << "\n";
}
/////////////alaa///
void CEllipse::SetID(int ind)
{
	ID = ind;
}

void CEllipse::Load(ifstream& Infile)
{
	this->FigGfxInfo.BorderWdth = 3;

	string s;
	Infile >> this->ID >> this->firstPoint.x >> this->firstPoint.y
		>> this->secondPoint.x >> this->secondPoint.y;

	Infile >> s;
	this->FigGfxInfo.DrawClr = GetStrinColor(s);

	Infile >> s;
	if (!(s == "NON-FILLED"))
		this->FigGfxInfo.FillClr = GetStrinColor(s);
	else
		this->FigGfxInfo.isFilled = false;


}
CEllipse::CEllipse() 
{
	this->Selected = false;
	this->isHidden = false;
};
void CEllipse::Resize(GUI* pGUI, float size)
{
	Point test1 = firstPoint, test2 = secondPoint;
	if (size == .5) size = -0.5;
	else if (size == .25) size = -(4.0 / 3);
	else if (size == 2) size = 1;
	else size = 3;

	// half radius (horizontal x && vertical y)
	float deltaX, deltaY;
	deltaX = 0.5 * (secondPoint.x - firstPoint.x);
	deltaY = 0.5 * (secondPoint.y - firstPoint.y);



	test1.x -= deltaX * size;
	test2.x += deltaX * size;
	test1.y -= deltaY * size;
	test2.y += deltaY * size;

	if (test1.y < UI.ToolBarHeight ||
		test2.y>UI.height - UI.StatusBarHeight || test2.x > UI.width + UI.wx || test1.x < UI.wx || test2.y < 0 || test1.x < 0) //||test1.y<0||test2.x<0
	{

		pGUI->PrintMessage("Ellips size will be more than Dwawing Area");
		Sleep(1000);
	}
	else if (((test2.x - test1.x) / 2) < 15 || ((test2.y - test1.y) / 2) < 10)
	{
		pGUI->PrintMessage("Ellips size will be very small");
		Sleep(1000);
	}
	else
	{
		firstPoint = test1;
		secondPoint = test2;
		//PrintInfo(pGUI);
	}



}
