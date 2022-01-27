#pragma once
#include"Action.h"
class Save : public Action
{
private:
	string FileName;
	int FigCnt;
public:
	Save(ApplicationManager* pApp, int FigCount);
	virtual void ReadActionParameters();
	virtual void Execute();
	//void SavePlayMode();
};

