#pragma once
#include "Action.h"

class ToPlayAction : public Action {
public:
	ToPlayAction(ApplicationManager *pApp);

	//Executes the switch to play mode
	virtual void Execute();
};
