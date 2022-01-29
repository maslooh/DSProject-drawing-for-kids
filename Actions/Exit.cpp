#include "Exit.h"
#include "Windows.h"
#include"Save.h"
#include"..\ApplicationManager.h"
//******v3.1*********** amany
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
        Action* pAct =pManager->CreateAction(SAVE);
        pManager->ExecuteAction(pAct);
        break;
    }


}
