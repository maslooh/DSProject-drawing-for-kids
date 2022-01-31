#pragma once
#include "../Figures/CFigure.h"
#include "Action.h"
class pickByType : public Action {
	CFigure* Fig;
	Point p;
	int shapes[3] = {};
	int no_shapes, rightAns, wrongAns, no_shapesEachCategory, randomShape;
	void score(int);

public:
	pickByType(ApplicationManager* pApp);
	void Execute();
};

