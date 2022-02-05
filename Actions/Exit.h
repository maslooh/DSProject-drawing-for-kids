#pragma once
#include"Action.h"
class Exit:public Action
{
	int FigCnt;
	int f;
public:
	Exit(ApplicationManager* pApp, int FigCount, int flag);


	virtual void Execute();
	
};
