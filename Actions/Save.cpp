#include"Save.h"
#include"..\ApplicationManager.h"
#include"..\Figures\CFigure.h"
#include"..\GUI\GUI.h"

#include <windows.h>
#include <windows.h>
#include <shobjidl.h> 
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
	ofstream OutFile;   //object of ofstream to write on the disk
	/*
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

	
	if (GetSaveFileName(&ofn)) {
		OutFile.open(szFileName );  // create a file with FileName and .txt exetention
		printf("the path is : %s\n", ofn.lpstrFile);
			OutFile.close(); //Good By :)

		*/
	////////alaa/////
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
							OutFile.open(pszFilePath);
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
	if (OutFile.fail())       //Check if the FileName is a valid name
	{
		pGUI->PrintMessage("Invalid file");
		return;
	}
	else
	{
		/// alaa
		OutFile << pManager->ConvertToString(UI.DrawColor) << "\t";
			if(pGUI->getIsFilled())
			{
				OutFile << pManager->ConvertToString(UI.FillColor) << "\t";
			}
			else
			{
				string s = "NON-FILLED";
				OutFile << s << "\t";
			}


			OutFile << pManager->ConvertToString(UI.BkGrndColor);  //Write the Current Draw Color 
		OutFile << "\n" << FigCnt << "\n";  //and Current Fill Color and in the second line write the number of figures 
		pManager->SaveFig(OutFile);  //Now Start Saving each figure proccess 

	}

}
