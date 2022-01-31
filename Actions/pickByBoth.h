#ifndef PICK_BY_Both_H
#define PICK_BY_Both_H
#include <string>

#include "../Figures/CFigure.h"
#include "Action.h"

class PickByBoth : public Action {
	int correctAns;
	int wrongAns;
	int score;
public:
	PickByBoth(ApplicationManager* pApp);
	void Execute();
	/**check if a figure matches a targeted figure (by fill color and name)*/
	bool doesFigureMatch(CFigure* figure, CFigure* targetFigure);
	/**get matching figures count that matches targetFigure from figure list */
	int getMatchingFigCount(CFigure* targetFigure);
};

#endif
