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

//******v3.1***** amany
void  CSquare::Save(ofstream& OutFile)
{
	OutFile << "Square\t"
		<< ID << "\t" << this->TopLeftCorner.x << "\t" << this->TopLeftCorner.y << "\t"
		<< this->length << "\t"
		<< this->colorToString(this->FigGfxInfo.DrawClr) << "\t";
	if (this->FigGfxInfo.isFilled)
		OutFile << this->colorToString(this->FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NON-FILLED\n";

}
/////////alaa//////////
void CSquare::SetID(int ind)
{
	ID = ind;
}
void CSquare::Load(ifstream& Infile)
{
	this->FigGfxInfo.BorderWdth = 3;
	this->Selected = false;
	//SetSelected(false);
	string s;
	Infile >> this->ID >> this->TopLeftCorner.x >> this->TopLeftCorner.y
		>> this->length;

	Infile >> s;
	this->FigGfxInfo.DrawClr = GetStrinColor(s);

	Infile >> s;

	if (!(s == "NON-FILLED"))
		this->FigGfxInfo.FillClr = GetStrinColor(s);
	else
		this->FigGfxInfo.isFilled = false;


}
CSquare::CSquare() {};
void CSquare::Resize(GUI* pGUI, float size)
{


	float length_test = length;
	Point test1 = TopLeftCorner;
	Point test2;
	test2.x = test1.x + length;
	test2.y = test1.y + length;
	length_test *= size;
	test2.x = test1.x + length_test;
	test2.y = test1.y + length_test;
	if (test1.y < UI.ToolBarHeight ||
		test2.y>UI.height - UI.StatusBarHeight || test2.x > UI.width + UI.wx || test1.x < UI.wx)
	{

		pGUI->PrintMessage("Square size will be more than Dwawing Area");
		Sleep(1000);
	}
	else if (length_test < 20)

	{
		pGUI->PrintMessage("Square size will be very small");
		Sleep(1000);
	}
	else
	{
		TopLeftCorner = test1;
		length = length_test;
		//PrintInfo(pGUI);
	}


}