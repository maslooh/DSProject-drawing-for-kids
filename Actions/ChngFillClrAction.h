#pragma once
#include "Action.h"

class ChngFillClrAction : public Action {
	ActionType inputColorAction;
	color FillClr;
	
	bool IsColor;
public:
	ChngFillClrAction(ApplicationManager *pApp);

	//Changes current/selected figure draw color
	virtual void Execute();
};
