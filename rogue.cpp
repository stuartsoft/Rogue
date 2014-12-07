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
	graphics->setBackColor(0x8888FF);
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
		wall[i].setX(400*i+100);
		wall[i].setY(0);
	}

	if(!CrateTM.initialize(graphics,"images\\crate2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init player texture"));
	for (int i=0;i<NUM_WALLS;i++){
		if (!crate[i].initialize(this, CrateNS::WIDTH, CrateNS::HEIGHT, 0, &CrateTM))
			throw(GameError(gameErrorNS::WARNING, "wall not initialized"));
		crate[i].setPositionX(400*i+100);
		crate[i].setPositionY(500);
	}
	
	graphics->setBackColor(graphicsNS::GRAY);

	menu = new Menu();
	menu->initialize(graphics, input);

	camera.x = 0;
	camera.y = 0;

	gameState = MAIN_MENU;
	timeInState = 0;
	time(&tsoundfx);

	return;
}

//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void Rogue::reset()
{
	return;
}

void Rogue::gameStateUpdate(float f)
{
	timeInState += f;

	if(gameState == MAIN_MENU && timeInState > 0.5f && input->isKeyDown(ENTER_KEY) && menu->getSelectedItem() == 0)
	{
		gameState = LEVEL1;
		timeInState = 0;
	}

}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void Rogue::update()
{
	gameStateUpdate(frameTime);
	time(&tnow);//update current time varaible
	if(input->isKeyDown(ESC_KEY))
	{
		exitGame();
	}

	switch(gameState)
	{
	case MAIN_MENU:
		menu->update();

		if(input->isKeyDown(ENTER_KEY) && menu->getSelectedItem() == 3)
		{
			exitGame();
		}

		break;
	case LEVEL1:

		player.update(frameTime);
		camera.x = GAME_WIDTH/2 - player.getCenterX();
		camera.y = GAME_HEIGHT/2 - player.getCenterY();
	
		for (int i=0;i<NUM_WALLS;i++){
			wall[i].update(frameTime);
		}
		for (int i=0;i<NUM_CRATES;i++){
			crate[i].update(frameTime);
		}

		break;
	}

}

//=============================================================================
// render game items
//=============================================================================
void Rogue::render()
{
	graphics->spriteBegin();

	switch(gameState)
	{
	case MAIN_MENU:
		menu->displayMenu();

		break;
	case LEVEL1:

		player.draw(camera);
		for (int i=0;i<NUM_WALLS;i++){
			wall[i].draw(camera);
		}
		for (int i=0;i<NUM_CRATES;i++){
			crate[i].draw(camera);
		}

		break;
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
			if(difftime(tnow,tsoundfx) >0.075){
				audio->playCue("Bump");
				time(&tsoundfx);
			}
		}
	}

	for (int i=0;i< NUM_CRATES;i++){
		if (crate[i].collidesWith(player, collisionVector)){
			crate[i].setVelocity(player.getVelocity()*2.5);
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
	WallTM.onLostDevice();
	CrateTM.onLostDevice();
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
	WallTM.onResetDevice();
	WallTM.onResetDevice();
	Game::resetAll();
	return;
}
