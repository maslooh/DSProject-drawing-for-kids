#ifndef GUI_H
#define GUI_H
#define _USE_MATH_DEFINES

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include <math.h>


//This class is responsible for Grphical User Interface handling
//All user input and program outputs MUST be done through this class
//No other class is allowed to perform direct i/o
class GUI	
{
public:	
	window* pWind;	//Pointer to the Graphics Window
	//****v3.1*** maslooh
	Point lastPointClicked;
public:
	GUI();	
	~GUI();	
	window* CreateWind(int, int, int , int) const; //creates the application window
	/////////// Input Functoinality  /////////////////
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting() const ;	 //Returns a string entered by the user
	ActionType MapInputToActionType() ; //Read the user click and map to an action


	/////////// Output Functoinality  ////////////////
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	void CreateColorToolBar() const;//v2  creates Color picker toolbar & menu

	void ClearStatusBar() const;
	void CreateSizeBar() const;
	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a Square
	void DrawEllipse(Point P1, Point p2, GfxInfo ellipGfxInfo, bool selected = false) const;  //Draw an ellipse
	//*****v2*******
	void DrawHexagon(Point P1, int length, int height, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a Hexagon
	
	///TODO: Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;
	void setCrntBKGrandColor(color c);
	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	//v2********************************************************
	bool getIsFilled() const; //get current filled state
	void setCrntDrawColor(color);
	void setCrntFillColor(color);
	void setIsFilled(bool);

	//****v3.1***maslooh
	void setLastPointClicked(int x, int y);
	Point getLastPointClicked();
};


#endif