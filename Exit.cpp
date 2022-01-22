#include "Exit.h"
#include "Windows.h"
#include"Save.h"
#include"..\ApplicationManager.h"

Exit::Exit(ApplicationManager* pApp) : Action(pApp)
{}

void Exit::ReadActionParameters()
{}
void Exit::Execute()
{
    int msgboxID = MessageBoxW(
        NULL,
        (LPCWSTR)L"save before exit!\n",
        (LPCWSTR)L"Account Details",
        MB_ICONWARNING | MB_YESNO
    );

    switch (msgboxID)
    {
    case IDYES:
        // TODO: add code
       // delete pAct;	//Action is not needed any more ==> delete it
       // pAct = NULL;
     
        pManager->CreateAction(SAVE);
     
        break;
    case IDNO:
        // TODO: add code
        break;

    }


}
