#include "Exit.h"
#include "Windows.h"
#include"..\Figures\CFigure.h"
#include"Save.h"
#include"..\ApplicationManager.h"

Exit::Exit(ApplicationManager* pApp, int FigCount,int flag) : Action(pApp)
{
    FigCnt = FigCount;
    f = flag;
}


void Exit::Execute()
{
    if (FigCnt > 0 && f!=0)
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
            Action* pAct = pManager->CreateAction(SAVE);
            pManager->ExecuteAction(pAct);
       
        }
       

    }
    exit(0);
}