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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init guard texture"));

	for (int i=0;i<NUM_CRATES;i++){
		if (!crate[i].initialize(this, CrateNS::WIDTH, CrateNS::HEIGHT, 0, &CrateTM))
			throw(GameError(gameErrorNS::WARNING, "crate not initialized"));
		crate[i].setPositionX(400*i+100);
		crate[i].setPositionY(500);
	}

	if(!GuardTM.initialize(graphics, "images\\guard2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init guard texture"));
	for (int i=0;i<NUM_GUARDS;i++)
	{
		if (!guard[i].initialize(this, guardNS::WIDTH, guardNS::HEIGHT, guardNS::TEXTURE_COL, &GuardTM))
			throw(GameError(gameErrorNS::WARNING, "guard not initialized"));
		guard[i].setPositionX(400*i+100);
		guard[i].setPositionY(300);
		guard[i].setTarget(&player);
	}

	if(!WeaponhudTM.initialize(graphics,"images\\weaponhud2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init weaponhud texture"));
	if(!WeaponHud.initialize(this, weaponhudNS::WIDTH, weaponhudNS::HEIGHT, weaponhudNS::TEXTURE_COL, &WeaponhudTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init weaponhud"));


	if(!backgroundtm.initialize(graphics, "images\\background2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init background texture"));
	if (!background.initialize(graphics, 2560, 1600,0,&backgroundtm))
		throw(GameError(gameErrorNS::WARNING, "background not initialized"));

	graphics->setBackColor(graphicsNS::GRAY);

	menu = new Menu();
	menu->initialize(graphics, input);

	camera.x = 0;
	camera.y = 0;

	gameState = MAIN_MENU;
	timeInState = 0;
	time(&tsoundfx);

	alert = false;
	alertTime = 0.0f;
	playerNoise = 0.0f;

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
		
		int tempx = (((int(camera.x))%(256)) - GAME_WIDTH/2);
		int tempy = (((int(camera.y))%(256)) - GAME_HEIGHT/2);
		background.setX(tempx);
		background.setY(tempy);


		if(player.getVelocity() != VECTOR2(0,0))
		{
			playerNoise = D3DXVec2Length(&player.getVelocity()) * 1.5f;
		}

		if(alert)
		{
			alertTime += frameTime;
			if(alertTime >= ALERT_DURATION)
			{
				alert = false;
			}
		}

		for (int i=0;i<NUM_WALLS;i++){
			wall[i].update(frameTime);
		}
		for (int i=0;i<NUM_CRATES;i++){
			crate[i].update(frameTime);
			crate[i].CollidedThisFrame=false;
		}
		for (int i=0;i<NUM_GUARDS;i++){
			guard[i].update(frameTime);
		}
		WeaponHud.update(frameTime);

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
		background.draw();
		player.draw(camera);
		for (int i=0;i<NUM_WALLS;i++){
			wall[i].draw(camera);
		}
		for (int i=0;i<NUM_CRATES;i++){
			crate[i].draw(camera);
		}
		for (int i=0;i<NUM_GUARDS;i++){
			guard[i].draw(camera);
		}
		WeaponHud.draw(camera);
		break;
	}
	graphics->spriteEnd();
}


//=============================
// handles entity ai
//=============================
void Rogue::ai()
{
	for (int i=0;i<NUM_GUARDS;i++)
	{
		guard[i].ai(alert);
	}
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
		for (int j=0;j<NUM_WALLS;j++){
			if(crate[i].collidesWith(wall[j], collisionVector)){
				//calculate elastic collision physics here
				float m1 = crate[i].getMass();
				float m2 = 1000.0f;
				VECTOR2 vi1 = crate[i].getVelocity();
				VECTOR2 vi2 = D3DXVECTOR2(0,0);

				float vxf1 = (vi1.x *(m1-m2) +2*m2*vi2.x)/(m1+m2);
				float vyf1 = (vi1.y *(m1-m2) +2*m2*vi2.y)/(m1+m2);

				VECTOR2 vf1 = D3DXVECTOR2(vxf1,vyf1);

				
				crate[i].setPositionX(crate[i].getPositionX() - crate[i].getVelocity().x*frameTime);
				crate[i].setPositionY(crate[i].getPositionY() - crate[i].getVelocity().y*frameTime);

				crate[i].setVelocity(D3DXVECTOR2(0,0));
				crate[i].setVelocity(vf1);
						
				crate[i].CollidedThisFrame = true;
			}

		}

	}

	if(gameState == LEVEL1){
		for (int i=0;i<NUM_CRATES;i++){
			for (int j=0;j<NUM_CRATES;j++){
				if (i!=j && !crate[i].CollidedThisFrame && !crate[i].CollidedThisFrame){
					if (crate[i].collidesWith(crate[j],collisionVector)){
						//calculate elastic collision physics here
						float m1 = crate[i].getMass();
						float m2 = crate[j].getMass();
						VECTOR2 vi1 = crate[i].getVelocity();
						VECTOR2 vi2 = crate[j].getVelocity();

						float vxf1 = (vi1.x *(m1-m2) +2*m2*vi2.x)/(m1+m2);
						float vyf1 = (vi1.y *(m1-m2) +2*m2*vi2.y)/(m1+m2);

						float vxf2 = (vi2.x * (m2-m1) + 2*m1*vi1.x)/(m1+m2);
						float vyf2 = (vi2.y * (m2-m1) + 2*m1*vi1.y)/(m1+m2);

						VECTOR2 vf1 = D3DXVECTOR2(vxf1,vyf1);
						VECTOR2 vf2 = D3DXVECTOR2(vxf2,vyf2);

						crate[i].setVelocity(D3DXVECTOR2(0,0));
						crate[j].setVelocity(D3DXVECTOR2(0,0));

						crate[i].setVelocity(vf1);
						crate[j].setVelocity(vf2);
						
						crate[i].CollidedThisFrame = true;
						crate[j].CollidedThisFrame = true;
					}
				}
			}
		}
	}

	for(int i=0; i<NUM_GUARDS; i++)
	{
		VECTOR2 dist = *guard[i].getCenter()-*player.getCenter();
		if(D3DXVec2Length(&dist) < playerNoise)
		{
			alert = true;
			alertTime = 0.0f;
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
