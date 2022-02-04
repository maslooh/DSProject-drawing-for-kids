#include "pickByBoth.h"
#include "../ApplicationManager.h"
#include"../Figures/CFigure.h"
#include"../GUI/GUI.h"
#include <iostream>
PickByBoth::PickByBoth(ApplicationManager* pApp) :Action(pApp) 
{
	correctAns = 0;
	wrongAns = 0;
	score = 0;
}
void PickByBoth::Execute()
{
	GUI* pGui = pManager->GetGUI();//making gui pinter
	CFigure* randomFig=pManager->getRandomFigure();//getting a random figure from figure list

	if (randomFig) //case that figure list is not empty
	{
		string randomFigClr = randomFig->GetFillClr();//getting color to select in the game 
		string randomFigName = randomFig->getFigureName();//getting figure to select in the game
		string msg = "please select all "+ randomFigClr +" " + randomFigName + "S";
		pGui->PrintMessage(msg);
		int matchingFigCount = getMatchingFigCount(randomFig);
		int flag = 1;
		while (matchingFigCount && flag)
		{
			//get a mouse click
			Point clickedPoint;
			pGui->pWind->WaitMouseClick(clickedPoint.x,clickedPoint.y);
			//checking if the user clicked on tool bar
			if (clickedPoint.y < UI.ToolBarHeight && clickedPoint.x < UI.MenuItemWidth * 4)
				flag = 0;
			//select a figure on screen
			CFigure* selectedFig = pManager->GetFigure(clickedPoint.x, clickedPoint.y);

			if (selectedFig) //case of selecting a figure
			{
				//case of correct answer
				if (doesFigureMatch(selectedFig,randomFig)) 
				{
					score++;
					correctAns++;
					selectedFig->HideShape();
					string msg = "correct! >> correct answers: " +
								 to_string(correctAns) + " ,wrong answers: " + to_string(wrongAns);
					pGui->PrintMessage(msg);
					matchingFigCount--;
					pManager->UpdateInterface();
				}
				//case of wrong answer
				else 
				{
					wrongAns++;
					string msg = "oops,wrong answer! >> correct answers: " +
						          to_string(correctAns) + " ,wrong answers: " + to_string(wrongAns);
					pGui->PrintMessage(msg);
				}
			}
			//case of not selecting a figure
			else
			{
				pGui->PrintMessage("Please select a figure");
			}
		}
		//case of exiting game
		if (!flag) 
		{
			string finalMsg = "exited game!";
			pGui->PrintMessage(finalMsg);
			Sleep(500);
			pManager->displayAllFigures();
		}
		//case of selecting all matching figures
		else 
		{
			string finalMsg = "Finished ,your score is >> correct answers:" +
				to_string(correctAns) + " ,wrong answers: " + to_string(wrongAns);
			pGui->PrintMessage(finalMsg);
			Sleep(500);
			pManager->displayAllFigures();
		}
	}
	//case of empty figure list
	else
	{
		pGui->PrintMessage("no figures drawen please draw or load some figures");
	}
}

/**check if a figure matches a targeted figure (by fill color and name)*/
bool PickByBoth::doesFigureMatch(CFigure* figure, CFigure* targetFigure)
{
	if(figure->GetFillClr() == targetFigure->GetFillClr()//color matching
	&& figure->getFigureName() == targetFigure->getFigureName())//figure name matching
	{
		return true;
	}
	return false;
}

/**get matching figures count that matches targetFigure from figure list */
int PickByBoth::getMatchingFigCount(CFigure* targetFigure)
{
	int figCount = pManager->getFigCount();//count of all figures
	int matchigFigCount = 0;//initial matching figure count

	for (int i = 0; i < figCount; i++) 
	{
		CFigure* currentFig = pManager->getFigList(i);//getting figure by index

		if (doesFigureMatch(currentFig, targetFigure))
		{
			matchigFigCount++;
		}
			
	}
	cout << matchigFigCount << endl;
	return matchigFigCount;
}



