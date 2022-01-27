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
	//****v3.1***** amany
	virtual void Save(ofstream& OutFile);
	/////////alaaa
	void SetID(int ind);
	virtual void Load(ifstream& Infile);
	CSquare();

	void Resize(GUI* pGUI, float size);
	
};

#endif