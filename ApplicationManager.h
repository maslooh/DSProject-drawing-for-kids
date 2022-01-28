#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures/CFigure.h"
#include "GUI\GUI.h"

class Action;	//Forward Declaration


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	//Pointers to Input and Output classes
	GUI* pGUI;
	

public:	
	ApplicationManager(); 
	~ApplicationManager();
	void Run();//to run the application
	
	// -- Action-Related Functions
	Action* CreateAction(ActionType);
	void ExecuteAction(Action*&) ; //Execute an action

	bool GetColor(color&);			   ////*****v2******* Reads a color from the color toolbar
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	void DeleteFigure(); //delets a figure ***v3***
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	//fadwa ****v3****
	void SendFigureBack();		// send figure back
	void BringFigureFront();	// bring figure front
	void changeFillColor(color FillClr);
	void changeDrawColor(color drawClr);
	int areFiguresSelected();
	void  unselectAll();
	//amany ****v3****
	void SaveFig(ofstream& Out);  //function to call Save Function for each figure***v3.1**	
	string ConvertToString(color c);   //Convert from Color Type to String Type //***v3.1**
	// -- Interface Management Functions	
	GUI *GetGUI() const; //Return pointer to the interface
	void UpdateInterface() const;	//Redraws all the drawing window
	/////////alaaaaaa
	color ConvertToColor(string s);


	void ResetFiglist();
	void Resize_figure(GUI* pGUI, float size) const;
	bool AnySelected();
};

#endif