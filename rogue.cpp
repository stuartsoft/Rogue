// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "Rogue.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

//=============================================================================
// Constructor
//=============================================================================
Rogue::Rogue()
{

}

//=============================================================================
// Destructor
//=============================================================================
Rogue::~Rogue()
{
	releaseAll();               // call deviceLost() for every graphics item
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void Rogue::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	graphics->setBackColor(0x000000);
	
	return;
}

//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void Rogue::reset()
{
	return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void Rogue::update()
{
	
}

//=============================================================================
// render game items
//=============================================================================
void Rogue::render()
{
	graphics->spriteBegin();
	
	graphics->spriteEnd();
}


//=============================
// handles entity ai
//=============================
void Rogue::ai()
{
	
}

//==================================================================
// Handle collision between entities
//==================================================================
void Rogue::collisions()
{
	
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Rogue::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Rogue::resetAll()
{
	Game::resetAll();
	return;
}
