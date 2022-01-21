#include "ApplicationManager.h"
#include "GUI\GUI.h"
int CFigure::counter = 0; //*****v2*******

int main()
{
	/*
	GUI* g=new GUI();
	
	
	window* w=g->CreateWind(200, 300, 10, 10);
	int x, y;
	w->WaitMouseClick(x, y);
	*/
	
	ApplicationManager AppManager;
	AppManager.Run();	
	return 0;
}

