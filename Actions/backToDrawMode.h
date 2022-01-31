#pragma once
#include "Action.h"
class backToDrawMode :public Action {
public:
	backToDrawMode(ApplicationManager* pApp);
	virtual void Execute();
};