#ifndef CSQUARE_H
#define CSQUARE_H

#include "CFigure.h"

class CSquare : public CFigure
{
private:
	Point TopLeftCorner;	
	int length;
public:
	CSquare(Point , int, GfxInfo FigureGfxInfo );//*****v2*******
	virtual void DrawMe(GUI* pOut) const;
	virtual bool InPoint(int x, int y) ;//*****v2*******
	virtual void PrintInfo(GUI* pGUI);
	virtual void Save(ofstream& OutFile);//****v3.1***** amany
};

#endif