#include "GUI.h"

//constructor make necessary initializations
GUI::GUI()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 80;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
	
}


//======================================================================================//
//								Input Functions										    //
//======================================================================================//


void GUI::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string GUI::GetSrting() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType GUI::MapInputToActionType() 
{	
	int x,y;
	pWind->WaitMouseClick(x,y);	//Get the coordinates of the user click
	//****v3.1*** maslooh
	setLastPointClicked(x, y);
	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SQUR: return DRAW_SQUARE;
			case ITM_ELPS: return DRAW_ELPS;
			case ITM_HEXA: return DRAW_HEX;
			case ITM_EXIT: return EXIT;	
			//v2***************************
			case ITM_CHNG_DRAW_CLR:return CHNG_DRAW_CLR;
			case ITM_CHNG_FILL_CLR:return CHNG_FILL_CLR;
			case ITM_CHNG_BKGRND_CLR:return CHNG_BK_CLR;	//v4 eslam
			//maslooh ***v3***
			case ITM_DELETE:return DEL;
			//fadwa ****v3****
			case ITM_BACK:return SEND_BACK;
			case ITM_FRONT:return BRNG_FRNT;
			//reem ****v3***
			case ITM_TO_PLAY:return TO_PLAY;
			//amany********v3.1****************
			case ITM_SAVE: return SAVE;
			/// alaa
			case ITM_LOAD: return LOAD;
			case ITM_RESIZE: return RESIZE;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{

			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_COLOR) //v2*******************
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case ITM_RED: return SET_RED;
			case ITM_GREEN: return SET_GREEN;
			case ITM_BLUE: return SET_BLUE;
			case ITM_PINK: return SET_PINK;
			case ITM_MAROON: return SET_MAROON;
			case ITM_PURPLE: return SET_PURPLE;

			default: return EMPTY;
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_SIZE)
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItemOrder)
			{
			case ITM_BACK1:  return BACK1;
			case ITM_QUARTER: return QUARTER;
			case ITM_HALF: return HALF;

			case ITM_DOUBLE:   return DOUBLE1;
			case ITM_QUADRUPLE: return QUADRUPLE;

			default: return EMPTY;
			}
		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		//User clicks on the toolBar area
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_BY_TYPE:return P_BY_TYPE;
			case ITM_BY_COLOR:return P_BY_COLOR;
			case ITM_BY_BOTH:return P_BY_BOTH;
			case ITM_TO_DRAW:return TO_DRAW;
			default: return EMPTY;
			}
		}
		////User clicks on the drawing area
		//if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		//{
		//	return DRAWING_AREA;
		//}
		//return STATUS;
	}


}
//======================================================================================//
//								Output Functions										//
//======================================================================================//

window* GUI::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white Square
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateDrawToolBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_DRAW;
	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SQUR] = "images\\MenuItems\\Menu_Sqr.jpg";
	//********v1*******
	MenuItemImages[ITM_ELPS] = "images\\MenuItems\\Menu_Elps.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\Menu_Hexa.jpg";

	//********v2********
	MenuItemImages[ITM_CHNG_DRAW_CLR] = "images\\MenuItems\\drawcolor1.jpg";
	MenuItemImages[ITM_CHNG_FILL_CLR] = "images\\MenuItems\\fillcolor.jpg";
	/////alaa
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\Resize.jpg";
	//maslooh ***v3***
	MenuItemImages[ITM_DELETE]= "images\\MenuItems\\delete.jpg";
	//fadwa ****v3****
	MenuItemImages[ITM_BACK] = "images\\MenuItems\\sndBack.jpg";
	MenuItemImages[ITM_FRONT] = "images\\MenuItems\\front.jpg";
	MenuItemImages[ITM_CHNG_BKGRND_CLR] = "images\\MenuItems\\Menu_Back.jpg";	//v4 eslam
	//***v3*** reem
	MenuItemImages[ITM_TO_PLAY] = "images\\MenuItems\\game.jpg";
	//amany******v3.1********
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\Menu_Save.jpg";
	/// alaa
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\Menu_Load.jpg";
	
	

	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";


	

	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//*****v3**** reem
void GUI::CreatePlayToolBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
	//pWind->SetPen(UI.BkGrndColor, 1);
	//pWind->SetBrush(UI.BkGrndColor);
	
	
		//pWind->DrawRectangle(0, 0, UI.width, UI.height - UI.ToolBarHeight);
		//pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	string PlayMenuItems[PLAY_ITM_COUNT];
	PlayMenuItems[ITM_BY_TYPE] = "images\\MenuItems\\byType.jpg";
	PlayMenuItems[ITM_BY_COLOR] = "images\\MenuItems\\byClr.jpg";
	PlayMenuItems[ITM_BY_BOTH] = "images\\MenuItems\\byBoth.jpg";
	PlayMenuItems[ITM_TO_DRAW] = "images\\MenuItems\\back.jpg";

	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(PlayMenuItems[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}// end of play menu
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::CreateColorToolBar() const //v2******************************************
{
	CreateToolBar();
	UI.InterfaceMode = MODE_COLOR;

	string ColorMenuItems[COLOR_ITM_COUNT];

	ColorMenuItems[ITM_RED] = "images\\MenuItems\\Menu_Red.jpg";
	ColorMenuItems[ITM_GREEN] = "images\\MenuItems\\Menu_Green.jpg";
	ColorMenuItems[ITM_BLUE] = "images\\MenuItems\\Menu_Blue.jpg";
	ColorMenuItems[ITM_PINK] = "images\\MenuItems\\Menu_Pink.jpg";
	ColorMenuItems[ITM_MAROON] = "images\\MenuItems\\Menu_Maroon.jpg";
	ColorMenuItems[ITM_PURPLE] = "images\\MenuItems\\Menu_Purple.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < COLOR_ITM_COUNT; i++)
		pWind->DrawImage(ColorMenuItems[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
///v3 resize 
void GUI::CreateSizeBar() const
{
	CreateToolBar();
	UI.InterfaceMode = MODE_SIZE;

	string MenuItemImages[SIZE_ITM_COUNT];

	MenuItemImages[ITM_BACK1] = "images\\MenuItems\\back.jpg";
	MenuItemImages[ITM_QUARTER] = "images\\MenuItems\\quartter.jpg";
	MenuItemImages[ITM_HALF] = "images\\MenuItems\\hallf.jpg";
	MenuItemImages[ITM_DOUBLE] = "images\\MenuItems\\two.jpg";
	MenuItemImages[ITM_QUADRUPLE] = "images\\MenuItems\\four.jpg";


	///TODO: write code to create Size mode menu
	for (int i = 0; i < SIZE_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void GUI::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////



void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color GUI::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
//alaa
void GUI::setCrntBKGrandColor(color c) {
	UI.BkGrndColor = c;
}
int GUI::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//v2***********************************************
bool GUI::getIsFilled() const {
	return UI.isFilled;
}

void GUI::setCrntDrawColor(color c) {
	UI.DrawColor = c;
}

void GUI::setCrntFillColor(color c) {
	UI.FillColor = c;
}

void GUI::setIsFilled(bool isF) {
	UI.isFilled = isF;
}
//****v3.1*** maslooh
void GUI::setLastPointClicked(int x, int y)
{
	lastPointClicked.x = x;
	lastPointClicked.y = y;
}
//****v3.1*** maslooh
Point GUI::getLastPointClicked()
{
	return lastPointClicked;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void GUI::DrawSquare(Point P1, int length, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P1.x +length, P1.y+length, style);
}
void GUI::DrawEllipse(Point p1, Point p2, GfxInfo ellipGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = ellipGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, ellipGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (ellipGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(ellipGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawEllipse(p1.x, p1.y, p2.x, p2.y, style);

}

void GUI::DrawHexagon(Point P1, int length, int height, GfxInfo HexaGfxInfo, bool selected) const//*****v2*******
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, HexaGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (HexaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int x[] = { P1.x, P1.x + length, P1.x + 1.5 * length, P1.x + length, P1.x, P1.x - 0.5 * length };
	int y[] = { P1.y, P1.y, P1.y + 0.5 * height, P1.y + height, P1.y + height, P1.y + 0.5 * height };
	pWind->DrawPolygon(x, y, 6, style);
}

//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

