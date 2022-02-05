#include "pickByType.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include"../Figures/CFigure.h"
#include"../Figures/CSquare.h"
#include"../Figures/CEllipse.h"
#include"../Figures/CHexagon.h"
#include <iostream>
pickByType::pickByType(ApplicationManager* pApp) :Action(pApp) {
	no_shapes = 0;
	rightAns = 0;
	wrongAns = 0;
}
void pickByType::Execute() {

	for (int i = 0; i < pManager->getFigCount(); i++) {

		Fig = pManager->getFigList(i);
		if (Fig->getFigureName() == "SQUARE") {
			shapes[0]++;	// indx 0 represents no. squares
		}
		else if (Fig->getFigureName() == "ELLIPSE") {
			shapes[1]++;	// indx 1 represents no. Ellipse
		}
		else {
			shapes[2]++;	// indx 2 represents no. Hexagons
		}
	}//end of for loop 

// count how many categories we have  
	for (int j = 0; j < 3; j++) {
		if (shapes[j] != 0) {
			no_shapes++;
		}
	}

	GUI* pGUI = pManager->GetGUI();
	if (no_shapes > 1) {
		// choose a random shape from list to start your game

		/*randomShape = rand() % pManager->getFigCount(); //v1 = rand() % 100 v1 in the range 0 to 99
		Fig = pManager->getFigList(randomShape);*/
		CFigure* Fig = pManager->getRandomFigure();//getting a random figure from figure list

		//Fig = pManager->getFigList(randomShape);
		if (Fig->getFigureName() == "SQUARE") {
			no_shapesEachCategory = shapes[0];
			pGUI->PrintMessage("Collect all Square shapes");
		}
		else if (Fig->getFigureName() == "ELLIPSE") {
			no_shapesEachCategory = shapes[1];
			pGUI->PrintMessage("Collect all Ellipse shapes");
		}
		else {
			no_shapesEachCategory = shapes[2];
			pGUI->PrintMessage("Collect all Hexagon shapes");
		}
		while (no_shapesEachCategory > 0) {

			pGUI->GetPointClicked(p.x, p.y);
			CFigure* selectedShape;
			if (p.y > UI.ToolBarHeight || p.x > (UI.MenuItemWidth * PLAY_ITM_COUNT)) {
				selectedShape = pManager->GetFigure(p.x, p.y);
				if (selectedShape != NULL) {
					if (Fig->getFigureName() == "SQUARE" && (selectedShape->getFigureName() == "SQUARE")) {
						score(1);
						selectedShape->HideShape();
						pManager->UpdateInterface();
						no_shapesEachCategory--;
					}
					else if (Fig->getFigureName() == "ELLIPSE" && (selectedShape->getFigureName() == "ELLIPSE")) {
						score(1);
						selectedShape->HideShape();
						pManager->UpdateInterface();
						no_shapesEachCategory--;
					}
					else if (Fig->getFigureName() == "HEXAGON" && (selectedShape->getFigureName() == "HEXAGON")) {
						score(1);
						selectedShape->HideShape();
						pManager->UpdateInterface();
						no_shapesEachCategory--;
					}
					else {
						score(2);
						selectedShape->HideShape();
						pManager->UpdateInterface();
					}

				}//end of selectedShape != NULL

			}//end of toolbar if
			//if any icons from toolbar is selected
			else {
				pGUI->PrintMessage("Game over! Choose a game to play");
				no_shapesEachCategory = -1;
			}
			if (no_shapesEachCategory == 0) {
				score(3);
				Sleep(1500);
			}
		}//end of while
	}// end of if (no_shapes>1)
	else {
		pGUI->PrintMessage("Please draw more than one different shape to start playing!");
	}
	for (int i = 0; i < pManager->getFigCount(); i++) {
		pManager->getFigList(i)->displayShape();
	}
	pManager->UpdateInterface();
}//end of Execute

void pickByType::score(int _score) {
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
	pGUI->PrintMessage(msg);
}
