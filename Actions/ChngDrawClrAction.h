#ifndef CHNG_DRAW_CLR_ACTION_H
#define CHNG_DRAW_CLR_ACTION_H
#include "Action.h"
#include "../Figures/CFigure.h"

class ChngDrawClrAction : public Action {
	ActionType inputColorAction;
	color DrawClr;
	
	bool IsColor;
public:
	ChngDrawClrAction(ApplicationManager* pApp);

	//Changes current/selected figure draw color
	virtual void Execute();
};

#endif