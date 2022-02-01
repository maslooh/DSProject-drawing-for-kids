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
	virtual void Save(ofstream& OutFile); //save the figure****v3.1**** amany
	/////////alaaa
	void SetID(int ind);
	virtual void Load(ifstream& Infile);
	CEllipse();
	void Resize(GUI* pGUI, float size);

	int GetArea();
};

#endif