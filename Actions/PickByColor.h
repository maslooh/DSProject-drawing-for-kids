#ifndef PICK_BY_COLOR_H
#define PICK_BY_COLOR_H

#include "../Figures/CFigure.h"
#include "Action.h"

class PickByColor : public Action {
	static string lastColor;
	int rightAns;
	int wrongAns;
	void score(int, string);

public:
	PickByColor(ApplicationManager* pApp);
	void Execute();
};

#endif
