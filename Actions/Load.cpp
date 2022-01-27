#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "..\ApplicationManager.h"

#include "..\GUI\GUI.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "../Figures/CEllipse.h"
#include "../Figures/CHexagon.h"
#include "../Figures/CSquare.h"

#include "Load.h"
#include<fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <tchar.h>






Load::Load(ApplicationManager* pApp) :Action(pApp)
{}
void Load::ReadActionParameters()
{
	GUI* pGUI = pManager->GetGUI();
  // pGUI->PrintMessage("Please write the file name :) ");
 	//FileName = pGUI->GetSrting();     //get the file name
}

//Execute the action
void Load::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	string bkgclr, DrawClr, FillClr, name;
	int Cnt;
	CFigure* fig = NULL;

	ReadActionParameters();   //read the inputs
	//std::string filename = "load.txt"; // could come from command line.
	//ifstream InFile;         //object of ifstream class
	//InFile.open(filename);
	//InFile.open(FileName+".txt"); 
	std::ifstream InFile;
	//InFile.open("E:/DS Project/Project/Project Framework/Actions/load.txt",ios ::out ); 
	//////////////////////////
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = _T("Text Files\0*.txt\0Any File\0*.*\0");
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = _T("Select a File, yo!");
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n";
		InFile.open(filename);
		
	}
	////////////////////////////////////////////////////////////////////////////
	if (InFile.fail())       //Check if the FileName is a valid name
	{
		pGUI->PrintMessage("Invalid file");
		return;
	}
	else
	{
		InFile >> DrawClr >> FillClr >> bkgclr;     //Read the Current FillColor and DrawColor
		/*UI.DrawColor = pManager->ConvertToColor(DrawClr);  //Convert them
		UI.FillColor = pManager->ConvertToColor(FillClr);  //To Color
		UI.BkGrndColor = pManager->ConvertToColor(bkgclr);
		*/
		if (FillClr == "NON-FILLED")
		{
			pGUI->setIsFilled(false);
		}
		else
		{
			pGUI->setIsFilled(true);

		}

		pGUI->setCrntDrawColor((pManager->ConvertToColor(DrawClr)));
		pGUI->setCrntFillColor((pManager->ConvertToColor(FillClr)));
		pGUI->setCrntBKGrandColor((pManager->ConvertToColor(bkgclr)));
		pGUI->ClearDrawArea();
		pManager->ResetFiglist();       //Delete The figure list
		InFile >> Cnt;
		while (Cnt)            //For each line on the file we will read it and determine its type
		{
			InFile >> name;

			if (name == "Square")
				fig = new CSquare;
			else if (name == "Hexagon")
				fig = new CHexagon;

			else if (name == "Ellipse")
				fig = new  CEllipse;


			fig->Load(InFile);  //Now we created the object and we should load it
			pManager->AddFigure(fig); //Add to the figure list
			Cnt--; //decrease the count 
		}



		pManager->UpdateInterface();     //Draw the figure list
		pGUI->PrintMessage("Graph Loaded Successfully");
		//pGUI->ClearStatusBar();
		//pGUI->CreateStatusBar();


	}
	

}
	
	

