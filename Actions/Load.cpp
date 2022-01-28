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
#include <windows.h>
#include <shobjidl.h> 





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
	//InFile.open("C:/Users/lolom/Downloads/Compressed/DSProject-drawing-for-kids-main/Actions/load.txt",ios ::out ); 
	//////////////////////////
	// int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							InFile.open(pszFilePath);
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
	
	}
	////////////////////

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
		


	}
	

}
	
	

