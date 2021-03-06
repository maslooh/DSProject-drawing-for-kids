#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	ID = ++CFigure::counter; //*****v2*******
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	isHidden = false;	///*****
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

string CFigure::getFigureName()
{
	return figureName;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
//****v3.1**** amany
string CFigure::colorToString(color c)
{
	if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (c == MAGENTA) return "MAGENTA";
	else if (c == TURQUOISE) return "TURQUOISE";
	else if (c == PINK) return "PINK";
	else if (c == MAROON) return "MAROON";
	else if (c == PURPLE) return "PURPLE";
	return "COLOR";
}
////////////alaaaaa
color CFigure::GetStrinColor(string s) const
{
	if (s == "BLUE")
		return BLUE;
	if (s == "RED")
		return RED;
	if (s == "YELLOW")
		return YELLOW;
	if (s == "GREEN")
		return GREEN;
	if (s == "LIGHTGOLDENRODYELLOW")
		return LIGHTGOLDENRODYELLOW;
	if (s == "MAGENTA")
		return MAGENTA;
	if (s == "TURQUOISE")
		return TURQUOISE;
	if (s == "PINK")
		return PINK;
	if (s == "MAROON")
		return MAROON;
	if (s == "PURPLE")
		return PURPLE;
	return BLACK;
}
CFigure::CFigure() {};

//***v5 fadwa
string CFigure::GetFillClr()
{
	if (FigGfxInfo.isFilled)
		return colorToString(FigGfxInfo.FillClr);
	else
		return "NON-FILLED";
}

///****reem v4***********
bool CFigure::isShapeHiddin() {
	return isHidden;
}
void CFigure::HideShape() {
	isHidden = true;
}
void CFigure::displayShape() {
	isHidden = false;
}