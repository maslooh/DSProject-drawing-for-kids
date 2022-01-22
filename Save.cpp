#include"Save.h"
#include"..\ApplicationManager.h"
#include"..\Figures\CFigure.h"
#include"..\GUI\GUI.h"
//#include"..\GUI\Output.h"
#include<fstream>
Save::Save(ApplicationManager* pApp, int FigCount) : Action(pApp)
{
	FileName = "TEST";
	FigCnt = FigCount;    //We need the figure number to write it on the file
	
}
void Save::ReadActionParameters()
{   
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Please write the file name then press ENTER");
	FileName = pGUI->GetSrting();  //read the file name
}
void Save::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	ReadActionParameters();     //get the parameters
	
	ofstream OutFile;   //object of ofstream to write on the disk
	OutFile.open(FileName + ".txt");  // create a file with FileName and .txt exetention
	bool flag = false;
	if (OutFile.fail()) //Check the FileName and loop till be Valid name
		flag = true;
	while (flag)
	{
		//pOut->PrintMessage("Please write a valid name then press ENTER");
		pGUI->PrintMessage("Please write a valid name then press ENTER");

		FileName = pGUI->GetSrting();
		OutFile.open(FileName + ".txt");
		if (OutFile.good())
			flag = false;
	}
	OutFile << pManager->ConvertToString(UI.DrawColor) << "\t" << pManager->ConvertToString(UI.FillColor) << "\n";  //Write the Current Draw Color 
	OutFile << FigCnt << "\n";  //and Current Fill Color and in the second line write the number of figures 
	pManager->SaveFig(OutFile);  //Now Start Saving each figure proccess 
	//pManager->set_LastMessage("Graph SAVED");  //Done!
	OutFile.close(); //Good By :)
}
