#include "CEllipse.h"
#include <iostream>
#include <string>

CEllipse::CEllipse()
{
	figureName = "ELLIPSE";
	this->Selected = false;
	this->isHidden = false;
};

CEllipse::CEllipse(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	firstPoint = P1;
	if (P1.x != P2.x && P1.y != P2.y)
		secondPoint = P2;
	else
	{
		secondPoint.x = P2.x - 20;
		secondPoint.y = P2.y - 20;
	}
	figureName = "ELLIPSE";
}


void CEllipse::DrawMe(GUI* pGUI) const
{
	//Call Output::DrawRect to draw a Square on the screen	
	pGUI->DrawEllipse(firstPoint, secondPoint, FigGfxInfo, Selected);

}

// ***v5
bool CEllipse::InPoint(int x, int y)//*****v2*******
{
	// calculate radius in two directions
	float RadiusX = abs(secondPoint.x - firstPoint.x) * 0.5;
	float RadiusY = abs(secondPoint.y - firstPoint.y) * 0.5;
	// center point of the ellipse
	Point center;
	center.x = firstPoint.x + RadiusX;
	center.y = firstPoint.y + RadiusY;

	// check if point inside ellipse
	float checkIn = pow((x - center.x), 2) / pow(RadiusX, 2) 
					+ pow((y - center.y), 2) / pow(RadiusY, 2);
	if (checkIn <= 1)
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
	msg += ", Xradius=";
	msg += to_string((secondPoint.x - firstPoint.x) / 2);
	msg += ", Yradius=";
	msg += to_string((secondPoint.y - firstPoint.y) / 2);
	msg += ", area=";
	msg += to_string(GetArea());
	pGUI->PrintMessage(msg);
}

int CEllipse::GetArea()
{
	return (M_PI * ((secondPoint.x - firstPoint.x) / 2) * ((secondPoint.y - firstPoint.y) / 2));
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

	if (test1.y < UI.ToolBarHeight || test2.y > UI.height - UI.StatusBarHeight 
		|| test2.x > UI.width || test1.x < 1 )
	{
		pGUI->PrintMessage("Ellips size will be more than Drawing Area");
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
