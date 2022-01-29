#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_COLOR	,//v2 Color Selector mode
	MODE_SIZE   //v3 size mode 

};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SQUR,		//Square item in menu
	ITM_ELPS,		//Ellipse item in menu
	ITM_HEXA,		//Hexa item in menu
	
	
	//TODO: Add more items names here
	//*************v2*****************
	ITM_CHNG_DRAW_CLR,		//Change draw color item in menu
	ITM_CHNG_FILL_CLR,		//Change fill color item in menu
	ITM_CHNG_BKGRND_CLR,    //Change background color item in menu  //v4 eslam
	ITM_RESIZE,    //v3 resize 
	//maslooh *****v3*****
	ITM_DELETE,             //delete selected items
	//fadwa ****v3****
	ITM_BACK,              //to send the selected figure to back
	ITM_FRONT,             //to bring the selected figure to front
	//reem ***v3***
	ITM_TO_PLAY,
	//anmany*****v3.1*******
	ITM_SAVE,       //save item in menu
	ITM_LOAD,
	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};
//*******v3******** reem
enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	ITM_BY_TYPE,	//Play and hide by type item in menu
	ITM_BY_COLOR,	//Play and hide by color item in menu
	ITM_BY_BOTH,	//Play and hide by both color and type item in menu
	ITM_TO_DRAW,	// RETURN To draw mode item in menu

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

//v2***********************************************
enum ColorMenuItem //The items of the Color menu (you should add more items)
{
	ITM_BLACK,		//Black color item in menu
	ITM_WHITE,		//White color item in menu	
	ITM_RED,		//Red color item in menu
	ITM_GREEN,		//Green color item in menu
	ITM_BLUE,		//Blue color item in menu

	COLOR_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};
//////alaa
enum SizeMenuItem // The items of size
{
	ITM_BACK1,
	ITM_QUARTER,
	ITM_HALF,

	ITM_DOUBLE,
	ITM_QUADRUPLE,



	SIZE_ITM_COUNT
};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	
	bool isFilled;//v2

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif