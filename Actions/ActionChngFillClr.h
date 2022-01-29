#ifndef ACTION_CHNG_FILL_CLR_H
#define ACTION_CHNG_FILL_CLR_H
#include "Action.h"

class ActionChngFillClr : public Action {
	ActionType inputColorAction;
	color FillClr;
	
	bool IsColor;
	bool IsSelected;
public:
	ActionChngFillClr(ApplicationManager *pApp);

	//Changes current/selected figure draw color
	virtual void Execute();
};

#endif