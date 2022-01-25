#ifndef ACTION_SEND_BACK_H
#define ACTION_SEND_BACK_H

#include "Action.h"
//*****v2*******
//Add Square Action class
class ActionSendBack : public Action
{
public:
	ActionSendBack(ApplicationManager* pApp);

	//excute selection
	virtual void Execute();

};

#endif