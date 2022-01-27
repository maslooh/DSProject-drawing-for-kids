#ifndef LOAD_H
#define LOAD_H

#include "Action.h"
#include <fstream>
//Add Square Action class
class Load : public Action
{
private:
	string FileName;
public:
	Load(ApplicationManager* pApp);
	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif