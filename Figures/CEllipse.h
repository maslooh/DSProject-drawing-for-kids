#pragma once
#ifndef CELLIPSE_H
#define CELLIPSE_H
#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point firstPoint;
	Point secondPoint;
public:
	CEllipse(Point, Point, GfxInfo FigureGfxInfo);//*****v2*******
	virtual void DrawMe(GUI* pOut) const;
	virtual bool InPoint(int x, int y);//*****v2*******
	virtual void PrintInfo(GUI* pGUI);
};

#endif