#ifndef ACTION_BRING_FRONT_H
#define ACTION_BRING_FRONT_H

#include "Action.h"
//*****v2*******
//Add Square Action class
class ActionBringFront : public Action
{
public:
	ActionBringFront(ApplicationManager* pApp);

	//excute selection
	virtual void Execute();

};

#endif