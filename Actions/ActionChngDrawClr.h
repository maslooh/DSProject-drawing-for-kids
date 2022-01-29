#ifndef ACTION_CHNG_DRAW_CLR_H
#define ACTION_CHNG_DRAW_CLR_H
#include "Action.h"
#include "../Figures/CFigure.h"

class ActionChngDrawClr : public Action {
	ActionType inputColorAction;
	color DrawClr;
	
	bool IsColor;
	bool IsSelected;
public:
	ActionChngDrawClr(ApplicationManager* pApp);

	//Changes current/selected figure draw color
	virtual void Execute();
};

#endif