#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

Menu::~Menu()
{
	SAFE_DELETE(menuHeadingFont);
	SAFE_DELETE(menuItemFont);
	SAFE_DELETE(menuItemFontHighlight);
}

void Menu::initialize(Graphics *g, Input *i)
{
	menuHeading ="Rogue: Shadow Bandit";
	menuItem1 = "Start Game";
	menuItem2 = "Tutorial";
	menuItem3 = "Toggle Cheat Codes";
	menuItem4 = "Exit";
	highlightColor = graphicsNS::WHITE;
	normalColor = graphicsNS::LTGRAY;
	menuAnchor = D3DXVECTOR2(GAME_WIDTH/10,GAME_HEIGHT/6);
	input = i;
	verticalOffset = GAME_HEIGHT/6;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();
	if(menuItemFont->initialize(graphics, 32, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, 32, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, 72, false, true, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));
	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);
	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
}

void Menu::update()
{
	if (input->isKeyDown(W_KEY))
	{
		upDepressedLastFrame = true;
	}
	if (input->isKeyDown(S_KEY))
	{
		downDepressedLastFrame = true;
	}
	if (!input->isKeyDown(W_KEY) && upDepressedLastFrame)
	{
		linePtr--;
		upDepressedLastFrame = false;
	}
	if (!input->isKeyDown(S_KEY) && downDepressedLastFrame)
	{
		linePtr++;
		downDepressedLastFrame = false;
	}

	if (linePtr > 3) linePtr = 0;
	if (linePtr < 0) linePtr = 3;

	if (input->isKeyDown(VK_RETURN))
		selectedItem = linePtr;

	else selectedItem = -1;
	
}

void Menu::displayMenu()
{
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);
	if (linePtr==0)
		menuItemFontHighlight->print(menuItem1, menuAnchor.x, menuAnchor.y+verticalOffset);
	else
		menuItemFont->print(menuItem1, menuAnchor.x, menuAnchor.y+verticalOffset);
	int foo = 2*verticalOffset;
	if (linePtr==1)
		menuItemFontHighlight->print(menuItem2, menuAnchor.x, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem2, menuAnchor.x, menuAnchor.y+foo);
	foo = 3*verticalOffset;
	if (linePtr==2)
		menuItemFontHighlight->print(menuItem3, menuAnchor.x, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem3, menuAnchor.x, menuAnchor.y+foo);
	foo = 4*verticalOffset;
	if (linePtr==3)
		menuItemFontHighlight->print(menuItem4, menuAnchor.x, menuAnchor.y+foo);
	else
		menuItemFont->print(menuItem4, menuAnchor.x, menuAnchor.y+foo);
}