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
	graphics->setBackColor(0xFFFFFF);
	if(!PlayerTM.initialize(graphics,PLAYER_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player texture"));
	if(!player.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COL, &PlayerTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player"));
	player.setCurrentFrame(0);
	player.setX(0);
	player.setY(0);

	if(!WallTM.initialize(graphics,WALL_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init player texture"));
   for (int i=0;i<NUM_WALLS;i++){
	   if (!wall[i].initialize(this, WallNS::WIDTH, WallNS::HEIGHT, 0, &WallTM))
		   throw(GameError(gameErrorNS::WARNING, "wall not initialized"));
	   wall[i].setX(100);
	   wall[i].setY(0);
   }
	
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
	if(input->isKeyDown(ESC_KEY))
	{
		exitGame();
	}
	player.update(frameTime);
	for (int i=0;i<NUM_WALLS;i++){
		wall[i].update(frameTime);
	}

}

//=============================================================================
// render game items
//=============================================================================
void Rogue::render()
{
	graphics->spriteBegin();

	player.draw();
	for (int i=0;i<NUM_WALLS;i++){
		wall[i].draw();
	}

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

	VECTOR2 collisionVector = D3DXVECTOR2(0,0);

	for (int i=0;i< NUM_WALLS;i++){
		if (wall[i].collidesWith(player, collisionVector)){
			player.setPositionX(player.getPositionX() - player.getVelocity().x* frameTime);
			player.setPositionY(player.getPositionY() - player.getVelocity().y* frameTime);
		}

	}
	
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Rogue::releaseAll()
{
	PlayerTM.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Rogue::resetAll()
{
	PlayerTM.onResetDevice();
	Game::resetAll();
	return;
}
