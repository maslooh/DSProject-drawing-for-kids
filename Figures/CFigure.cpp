#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	ID = ++CFigure::counter; //*****v2*******
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

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
	if (c == BLACK) return "BLACK";
	else if (c == WHITE) return "WHITE";
	else if (c == BLUE) return "BLUE";
	else if (c == RED) return "RED";
	else if (c == YELLOW) return "YELLOW";
	else if (c == GREEN) return "GREEN";
	else if (c == LIGHTGOLDENRODYELLOW) return "LIGHTGOLDENRODYELLOW";
	else if (c == MAGENTA) return "MAGENTA";
	else if (c == TURQUOISE) return "TURQUOISE";
	return "COLOR";
}
