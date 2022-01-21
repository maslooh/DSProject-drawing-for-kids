#ifndef CHexagon_H
#define CHexagon_H

#include "CFigure.h"

class CHexagon : public CFigure
{
private:
	Point TopLeftCorner;
	int length;
	Point pointsList[2];
public:
	CHexagon(Point, int, GfxInfo FigureGfxInfo);
	virtual Point* getPoints();
	virtual void DrawMe(GUI* pOut) const;
};

#endif