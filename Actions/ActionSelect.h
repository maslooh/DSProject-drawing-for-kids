#ifndef ACTION_SELECT_H
#define ACTION_SELECT_H

#include "Action.h"
//*****v2*******
//Add Square Action class
class ActionSelect : public Action
{
public:
	ActionSelect(ApplicationManager* pApp);

	//excute selection
	virtual void Execute();

};

#endif