#pragma once
#ifndef CELLIPSE_H
#define CELLIPSE_H
#include "CFigure.h"

class CEllipse : public CFigure
{
private:
	Point firstPoint;
	Point secondPoint;
	Point pointsList[2]; //v2
public:
	CEllipse(Point, Point, GfxInfo FigureGfxInfo);
	virtual void DrawMe(GUI* pOut) const;
	virtual Point* getPoints();//v2
};

#endif