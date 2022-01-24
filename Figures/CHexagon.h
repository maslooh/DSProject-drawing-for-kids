#ifndef CHexagon_H
#define CHexagon_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point TopLeftCorner;
	int length;
	int height; //*****v2*******
public:
	CHexagon(Point, int, GfxInfo FigureGfxInfo); //*****v2*******
	virtual void DrawMe(GUI* pOut) const;
	virtual bool InPoint(int x, int y);//*****v2*******
	virtual void PrintInfo(GUI* pGUI);
};

#endif