#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
	Point pointsList[2];//v2
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );
	virtual Point* getPoints() ;//v2
	virtual void DrawMe(GUI* pOut) const;
};

#endif