#include "PickByColor.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"


PickByColor::PickByColor(ApplicationManager* pApp) :Action(pApp) {
	rightAns = 0;
	wrongAns = 0;
}

void PickByColor::Execute() 
{
	// change seed of the random generator
	// initialize the sequence of pseudo-random numbers with a parameter called 'random seed'
	srand(time(0));

	GUI* pGUI = pManager->GetGUI();

	CFigure* fig = NULL;

	// number of figure that will be selected in the current game
	int noOfPlayFigure = 0;
	
	//selected random color
	string playColor;

	if (pManager->getFigCount() > 0)
	{
		//choose random color from existing figures (exclude the last selected color)
		do 
		{
			int randomColor = rand() % pManager->getFigCount();
			playColor = (pManager->getFigList(randomColor))->GetFillClr();
		} while (PickByColor::lastColor == playColor);
		PickByColor::lastColor = playColor;

		// calculate the number of exist figures with selected color
		for (int i = 0; i < pManager->getFigCount(); i++)
		{
			fig = pManager->getFigList(i);
			if (fig->GetFillClr() == playColor)
				noOfPlayFigure++;
		}

		string currentPlayMsg = "Collect all " + playColor + " shapes";
		pGUI->PrintMessage(currentPlayMsg);
	
		// start playing
		while (noOfPlayFigure > 0)
		{
			// get clicked point
			Point P;
			pGUI->GetPointClicked(P.x, P.y);

			//click on drawing mode
			if (P.y > UI.ToolBarHeight && P.y < UI.height - UI.StatusBarHeight)
			{
				fig = pManager->GetFigure(P.x, P.y);
				// if user selected a figure (and not selected before)
				if (fig)
				{
					if (fig->GetFillClr() == playColor)
					{
						fig->HideShape();
						noOfPlayFigure--;
						pManager->UpdateInterface();
						score(1, currentPlayMsg);
					}
					else
					{
						fig->HideShape();
						pManager->UpdateInterface();
						score(2, currentPlayMsg);
					}
				}
			}
			//to start new game
			else if (P.y < UI.ToolBarHeight && P.x < (UI.MenuItemWidth * PLAY_ITM_COUNT))
			{
				pGUI->PrintMessage("Game over! welcome to play mode");
				noOfPlayFigure = -1;
			}
		}
		if (noOfPlayFigure==0)
		{
			// after user selected all correct figures
			score(3, "");
			Sleep(1500);
			//pGUI->PrintMessage("Welcome to play mode");
		}

		//reset original figures
		for (int i = 0; i < pManager->getFigCount(); i++) {
			pManager->getFigList(i)->displayShape();
		}
		pManager->UpdateInterface();
	}
	else
	{
		pGUI->PrintMessage("Please draw any figures to play!");
	}
}

void PickByColor::score(int _score, string currentPlayMsg)
{
	GUI* pGUI = pManager->GetGUI();
	string msg;
	if (_score == 1) {
		rightAns++;
		msg = "Correct!, You have: " + to_string(rightAns) + " correct answers , and " + to_string(wrongAns) + " Wrong.";
	}
	else if (_score == 2) {
		wrongAns++;
		msg = "Wrong!, You have: " + to_string(rightAns) + " correct answers , and " + to_string(wrongAns) + " Wrong.";
	}
	else {
		msg = "Congratulations you Win!, Your score is: " + to_string(rightAns) + " correct answers, and " + to_string(wrongAns) + " Wrong.";
	}
	pGUI->PrintMessage(currentPlayMsg + "                >> " + msg);
}
