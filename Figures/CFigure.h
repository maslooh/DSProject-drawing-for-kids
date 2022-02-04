#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\DEFS.h"
#include "..\GUI\GUI.h"

#include<fstream>
#include<string>

//Base class for all figures
class CFigure
{
protected:
	static int counter; 
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	bool isHidden;
	/// Add more parameters if needed.
	string figureName;
public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool );	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	string getFigureName();
	virtual void DrawMe(GUI*) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color


	virtual bool InPoint(int x, int y) = 0;  // if point inside the figure

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Rotate() = 0;	//Rotate the figure
	//virtual void Resize() = 0;	//Resize the figure
	//virtual void Move() = 0;		//Move the figure
	string colorToString(color c) ; //Convert color to string ***v3.1**
	virtual void Save(ofstream& OutFile) = 0;// Save the figure parameters to the file ***v3.1*** amany
	virtual void SetID(int ind) = 0;  //set the id id of each function
	virtual void Load(ifstream& Infile) = 0;	//Load the figure parameters to the file
	virtual color GetStrinColor(string s) const;  //convert from string to color type
	virtual void Resize(GUI* pGUI, float size) = 0;	//Resize the figure

	CFigure();

	virtual void PrintInfo(GUI* pGUI) = 0;	//print all figure info on the status bar

	virtual int GetArea() = 0;

	//***v5 return the color of each figure in string
	string GetFillClr();        

	//*******reem v4********
	void HideShape();
	void displayShape();
	bool isShapeHiddin();
};

#endif