#include"Save.h"
#include"..\ApplicationManager.h"
#include"..\Figures\CFigure.h"
#include"..\GUI\GUI.h"

#include <windows.h>
Save::Save(ApplicationManager* pApp, int FigCount) : Action(pApp)
{
	FileName = "TEST";
	FigCnt = FigCount;    //We need the figure number to write it on the file
	
}
void Save::ReadActionParameters()
{   

	
}

void Save::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	char szFileName[MAX_PATH] = "";
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;	
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	//ofn.lpstrDefExt = (LPSTR)L"txt";
	ofn.lpstrDefExt ="txt";

	ofstream OutFile;   //object of ofstream to write on the disk
	if (GetSaveFileName(&ofn)) {
		OutFile.open(szFileName );  // create a file with FileName and .txt exetention

		OutFile << pManager->ConvertToString(UI.DrawColor) << "\t" << pManager->ConvertToString(UI.FillColor) << "\t"<< pManager->ConvertToString(UI.BkGrndColor);  //Write the Current Draw Color 
		OutFile << FigCnt << "\n";  //and Current Fill Color and in the second line write the number of figures 
		pManager->SaveFig(OutFile);  //Now Start Saving each figure proccess 
		OutFile.close(); //Good By :)

	}
	
	printf("the path is : %s\n", ofn.lpstrFile);


	
	


}
