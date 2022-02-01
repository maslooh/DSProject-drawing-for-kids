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
	//fadwa ****v3****
	CHexagon(Point, int, int, GfxInfo FigureGfxInfo); //*****v2*******
	virtual void DrawMe(GUI* pOut) const;
	virtual bool InPoint(int x, int y);//*****v2*******
	virtual void PrintInfo(GUI* pGUI);
	virtual void Save(ofstream& OutFile);//******v3.1**** amany
	/////////alaaa
	void SetID(int ind);
	virtual void Load(ifstream& Infile);
	CHexagon();
	void Resize(GUI* pGUI, float size);

	//***v5
	float AreaTriangle(float, float, float, float, float, float);
	int GetArea();
};

#endif