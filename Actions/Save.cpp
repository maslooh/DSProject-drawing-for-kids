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
	
	
	string path = "";
	HRESULT hr = CoInitializeEx(NULL, COINITBASE_MULTITHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileSaveDialog* pFileSave;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));
		if (SUCCEEDED(hr))
		{
			// Set default extension
			hr = pFileSave->SetDefaultExtension(L"txt");
			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileSave->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileSave->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							//MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
							char buffer[500];
							wcstombs(buffer, pszFilePath, 500);
							path = buffer;
							CoTaskMemFree(pszFilePath);
							//////////////////
							OutFile.open(pszFilePath); // create a file with FileName and .txt exetention
							OutFile << pManager->ConvertToString(UI.DrawColor) << "\t";
							if (pGUI->getIsFilled())
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
							OutFile.close();
													   //////////////////////////
						}
						pItem->Release();
					}
				}
				pFileSave->Release();
			}
		}
		CoUninitialize();
	}


}
