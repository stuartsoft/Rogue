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
	splashFont = new TextDX;
	winFont = new TextDX;
	loseFont = new TextDX;
}

//=============================================================================
// Destructor
//=============================================================================
Rogue::~Rogue()
{
	releaseAll();               // call deviceLost() for every graphics item
	SAFE_DELETE(splashFont);
	SAFE_DELETE(winFont);
	SAFE_DELETE(loseFont);
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
	player.setHealth(playerNS::MAX_HEALTH);

	if(!WallTM.initialize(graphics,WALL_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init wall texture"));
	for (int i=0;i<MAX_WALLS;i++){
		if (!wall[i].initialize(this, WallNS::WIDTH, WallNS::HEIGHT, 0, &WallTM))
			throw(GameError(gameErrorNS::WARNING, "wall not initialized"));
		wall[i].setX(0);
		wall[i].setY(0);
		wall[i].setActive(false);
	}

	if(!ExitTM.initialize(graphics,EXIT_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init exit texture"));
	if (!levelExit.initialize(this, 128, 128, 0, &ExitTM))
			throw(GameError(gameErrorNS::WARNING, "exit not initialized"));
	levelExit.setActive(false);
	RECT r = {-64,-64,64,64};
	levelExit.setEdge(r);
	levelExit.setCollisionType(entityNS::COLLISION_TYPE::BOX);

	if(!CrateTM.initialize(graphics,"images\\crate2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init crate texture"));

	for (int i=0;i<MAX_CRATES;i++){
		if (!crate[i].initialize(this, CrateNS::WIDTH, CrateNS::HEIGHT, 0, &CrateTM))
			throw(GameError(gameErrorNS::WARNING, "crate not initialized"));
		crate[i].setPositionX(0);
		crate[i].setPositionY(0);
		crate[i].setActive(false);
	}

	if(!GuardTM.initialize(graphics, "images\\guard2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init guard texture"));
	for (int i=0;i<MAX_GUARDS;i++)
	{
		if (!guard[i].initialize(this, guardNS::WIDTH, guardNS::HEIGHT, guardNS::TEXTURE_COL, &GuardTM))
			throw(GameError(gameErrorNS::WARNING, "guard not initialized"));
		guard[i].setPositionX(0);
		guard[i].setPositionY(0);
		guard[i].setTarget(&player);
		guard[i].setActive(false);
	}

	if(!WeaponhudTM.initialize(graphics,"images\\weaponhud2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init weaponhud texture"));
	if(!WeaponHud.initialize(this, weaponhudNS::WIDTH, weaponhudNS::HEIGHT, weaponhudNS::TEXTURE_COL, &WeaponhudTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init weaponhud"));

	if (!WeaponTM.initialize(graphics, "images\\Weapons2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init weapon texture"));
	WeaponHud.initWeapons(&WeaponTM);

	if(!backgroundtm.initialize(graphics, "images\\background2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init background texture"));
	if (!background.initialize(graphics, 2560, 1600,0,&backgroundtm))
		throw(GameError(gameErrorNS::WARNING, "background not initialized"));

	if(!SplashTM.initialize(graphics, "images\\splash.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init splash1 texture"));
	if (!Splash.initialize(graphics, 1280, 720,0,&SplashTM))
		throw(GameError(gameErrorNS::WARNING, "splash1 not initialized"));

	if(!GameOverTM.initialize(graphics, "images\\background2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init lose splash texture"));
	if (!GameOverSplash.initialize(graphics, 1280, 800,0,&GameOverTM))
		throw(GameError(gameErrorNS::WARNING, "lose splash not initialized"));

	if(!GameWinTM.initialize(graphics, "images\\background2x.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init win splash texture"));
	if (!GameWinSplash.initialize(graphics, 1280, 800,0,&GameWinTM))
		throw(GameError(gameErrorNS::WARNING, "win splash not initialized"));

	if(splashFont->initialize(graphics, 52, true, false, "Stencil") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font"));
	if(winFont->initialize(graphics, 52, true, false, "Stencil") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font"));
	if(loseFont->initialize(graphics, 52, true, false, "Stencil") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font"));
	
	splashFont->setFontColor(graphicsNS::WHITE);
	winFont->setFontColor(graphicsNS::BLACK);
	loseFont->setFontColor(graphicsNS::RED);

	graphics->setBackColor(graphicsNS::GRAY);

	menu = new Menu();
	menu->initialize(graphics, input);

	camera.x = 0;
	camera.y = 0;

	gameState = MAIN_MENU;
	levelComplete = false;
	timeInState = 0;
	tsoundfx = clock();
	tmouseclick = clock();
	flinch = false;
	flinchTime = 0.0f;

	for (int i=0;i<NUM_WEAPONS;i++){
		weapons[0][i] = new Shuriken();
		if(!((Shuriken*)weapons[0][i])->initialize(this,weaponNS::WIDTH,weaponNS::HEIGHT,4,&WeaponTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing weapon"));
		((Shuriken*)weapons[0][i])->setActive(false);
		((Shuriken*)weapons[0][i])->setCurrentFrame(0);//shuriken image
	}
	return;
}

//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void Rogue::reset()
{
	player.setVelocity(VECTOR2(0,0));
	player.setHealth(playerNS::MAX_HEALTH);
	player.setPositionX(0);
	player.setPositionY(0);
	player.setHealth(playerNS::MAX_HEALTH);
	flinch = false;
	flinchTime = 0.0f;

	for(int i=0; i<MAX_WALLS; i++)
	{
		wall[i].setActive(false);
		wall[i].setX(0);
		wall[i].setY(0);
	}
	for(int i=0; i<MAX_CRATES; i++)
	{
		crate[i].setActive(false);
		crate[i].setVelocity(VECTOR2(0,0));
		crate[i].setPositionX(0);
		crate[i].setPositionY(0);
	}
	for(int i=0; i<MAX_GUARDS; i++)
	{
		guard[i].reset();
	}
	levelExit.setActive(false);
	levelExit.setX(0);
	levelExit.setY(0);

	return;
}

void Rogue::loadLevel()
{
	ifstream file;
	switch(gameState)
	{
	case LEVEL1:
		file.open("Levels\\L1.txt");
		break;
	case LEVEL2:
		file.open("Levels\\L2.txt");
		break;
	case LEVEL3:
		file.open("Levels\\L3.txt");
		break;
	}
	
	if (file.is_open())
	{
		string line;
		int p;
		getline(file,line);
		p = atoi(line.c_str());
		numWalls = p;
		getline(file,line);
		p = atoi(line.c_str());
		numCrates = p;
		getline(file,line);
		p = atoi(line.c_str());
		numGuards = p;
		getline(file,line);
		for (int i=0; i<numWalls; i++)
		{
			string line;
			int x,y;
			getline(file,line);
			x = atoi(strtok(strdup(line.c_str()),","));
			y = atoi(strtok(NULL,","));
			wall[i].setX(x*WallNS::WIDTH);
			wall[i].setY(y*WallNS::HEIGHT);
			wall[i].setActive(true);
		}
		getline(file,line);
		for(int i=0; i<numCrates; i++)
		{
			string line;
			int x,y;
			getline(file,line);
			x = atoi(strtok(strdup(line.c_str()),","));
			y = atoi(strtok(NULL,","));
			crate[i].setPositionX(x*WallNS::WIDTH+WallNS::WIDTH/2);
			crate[i].setPositionY(y*WallNS::HEIGHT+WallNS::HEIGHT/2);
			crate[i].setActive(true);
		}
		getline(file,line);
		for(int i=0; i<numGuards; i++)
		{
			string line;
			int x,y,p;
			bool up;
			getline(file,line);
			x = atoi(strtok(strdup(line.c_str()),","));
			y = atoi(strtok(NULL,","));
			getline(file,line);
			p = atoi(line.c_str());
			if(p == 1)
				up = true;
			else
				up = false;
			guard[i].setPatrol(x*WallNS::WIDTH+WallNS::WIDTH/2,
							   y*WallNS::HEIGHT+WallNS::HEIGHT/2,
							   up);
			guard[i].setActive(true);
		}
		getline(file,line);
		string line2;
		int x,y;
		getline(file,line2);
		x = atoi(strtok(strdup(line2.c_str()),","));
		y = atoi(strtok(NULL,","));
		levelExit.setX(x*WallNS::WIDTH+WallNS::WIDTH/2);
		levelExit.setY(y*WallNS::HEIGHT+WallNS::HEIGHT/2);
		levelExit.setActive(true);
	}
	
	file.close();
}

void Rogue::gameStateUpdate(float f)
{
	timeInState += f;

	if(gameState == MAIN_MENU && timeInState > 0.5f && input->isKeyDown(ENTER_KEY) && menu->getSelectedItem() == 0)
	{
		gameState = SPLASH1;
		timeInState = 0;
		levelComplete = false;
		reset();
	}
	if(gameState == SPLASH1 && timeInState >= 2.5f)
	{
		gameState = LEVEL1;
		timeInState = 0.0f;
		loadLevel();
	}
	if(gameState == LEVEL1 && levelComplete)
	{
		gameState = SPLASH2;
		timeInState = 0.0f;
		levelComplete = false;
		reset();
	}
	if(gameState == SPLASH2 && timeInState >= 2.5f)
	{
		gameState = LEVEL2;
		timeInState = 0.0f;
		loadLevel();
	}
	if(gameState == LEVEL2 && levelComplete)
	{
		gameState = SPLASH3;
		timeInState = 0.0f;
		levelComplete = false;
		reset();
	}
	if(gameState == SPLASH3 && timeInState >= 2.5f)
	{
		gameState = LEVEL3;
		timeInState = 0.0f;
		loadLevel();
	}
	if(gameState == LEVEL3 && levelComplete)
	{
		gameState = GAME_WIN;
		timeInState = 0.0f;
		levelComplete = false;
	}
	if((gameState == GAME_OVER || gameState == GAME_WIN) && timeInState >= 0.5f && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
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
	case LEVEL2:
	case LEVEL3:
		player.update(frameTime);
		camera.x = GAME_WIDTH/2 - player.getCenterX();
		camera.y = GAME_HEIGHT/2 - player.getCenterY();
		
		if(player.getHealth() <= 0)
		{
			gameState = GAME_OVER;
			timeInState = 0.0f;
			audio->playCue("Hit");
			break;
		}

		if (WeaponHud.getAmmoForCurrentWeapon()>0 && input->getMouseLButton() && prevMouseLState ==false){
			VECTOR2 aimvec = VECTOR2(input->getMouseX(),input->getMouseY());
			VECTOR2 cam = VECTOR2(GAME_WIDTH/2, GAME_HEIGHT/2);
			aimvec -= cam;
			D3DXVec2Normalize(&aimvec,&aimvec);
			aimvec*=500;
			
			//deduct ammo from weapon
			WeaponHud.setAmmoForWeapon(WeaponHud.getAmmoForCurrentWeapon()-1,WeaponHud.getCurrentWeapon());
			switch (WeaponHud.getCurrentWeapon())
			{
			case 0:
				for (int i=0;i<NUM_WEAPONS;i++){
					if (!weapons[0][i]->getActive()){
						weapons[0][i]->setActive(true);//activate weapon
						weapons[0][i]->setVelocity(aimvec);
						weapons[0][i]->setPosition(player.getPosition());
						tmouseclick = clock();
						break;
					}
				}
				break;
			}
		}

		if(flinch)
		{
			flinchTime += frameTime;
			if(flinchTime >= FLINCH_DURATION)
			{
				flinch = false;
				flinchTime = 0;
			}
		}

		int tempx = (((int(camera.x))%(256)) - GAME_WIDTH/2);
		int tempy = (((int(camera.y))%(256)) - GAME_HEIGHT/2);
		background.setX(tempx);
		background.setY(tempy);
		
		for (int i=0;i<numWalls;i++){
			if(wall[i].getActive()){
				wall[i].update(frameTime);
			}
		}
		for (int i=0;i<numCrates;i++){
			if(crate[i].getActive())
			{
				crate[i].update(frameTime);
				crate[i].CollidedThisFrame=false;
			}
		}
		for (int i=0;i<numGuards;i++){
			if(guard[i].getActive())
				guard[i].update(frameTime);
		}
		for (int i=0;i<NUM_WEAPONS;i++){
			if(weapons[0][i]->getActive()){
				((Shuriken*)weapons[0][i])->update(frameTime);
			}

		}

		WeaponHud.update(frameTime);

		break;
	}
	prevMouseLState = input->getMouseLButton();
	prevMouseRState = input->getMouseRButton();

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
	case LEVEL2:
	case LEVEL3:
		background.draw();
		if(levelExit.getActive())
		{
			levelExit.setX(levelExit.getX()+camera.x);
			levelExit.setY(levelExit.getY()+camera.y);
			levelExit.draw();
			levelExit.setX(levelExit.getX()-camera.x);
			levelExit.setY(levelExit.getY()-camera.y);
		}
		if(!flinch)
			player.draw(camera);
		else
			player.draw(camera, graphicsNS::ALPHA25);

		for (int i=0;i<numCrates;i++){
			if(crate[i].getActive())
				crate[i].draw(camera);
		}
		for (int i=0;i<numGuards;i++){
			if(guard[i].getActive())
				guard[i].draw(camera);
		}

		for (int i=0;i<numWalls;i++){
			wall[i].draw(camera);
		}
		for (int i=0;i<NUM_WEAPONS;i++){
			if(weapons[0][i]->getActive()){
				((Shuriken*)weapons[0][i])->draw(camera);
			}
		}
		
		WeaponHud.draw(camera);
		break;

	case SPLASH1:
		Splash.draw();
		splashFont->print("ALPHA MISSION: BEGIN",GAME_WIDTH/4,GAME_HEIGHT/4);
		break;
	case SPLASH2:
		Splash.draw();
		splashFont->print("BETA MISSION: BEGIN",GAME_WIDTH/4,GAME_HEIGHT/4);
		break;
	case SPLASH3:
		Splash.draw();
		splashFont->print("CHARLIE MISSION: BEGIN",GAME_WIDTH/4,GAME_HEIGHT/4);
		break;
	case GAME_OVER:
		GameOverSplash.draw();
		loseFont->print("MISSION FAILED",GAME_WIDTH/3,GAME_HEIGHT/4);
		break;
	case GAME_WIN:
		GameWinSplash.draw();
		winFont->print("MISSION SUCCESS!",GAME_WIDTH/3,GAME_HEIGHT/4);
		break;
	}
	graphics->spriteEnd();
}

//=============================
// handles entity ai
//=============================
void Rogue::ai()
{
	switch(gameState)
	{
	case LEVEL1:
	case LEVEL2:
	case LEVEL3:
		bool hey;
		for (int i=0;i<numGuards;i++)
		{
			hey = false;
			guard[i].ai(hey);
			if(hey)
			{
				audio->playCue("Jump");
			}
		}
	}
}

//==================================================================
// Handle collision between entities
//==================================================================
void Rogue::collisions()
{
	VECTOR2 collisionVector = D3DXVECTOR2(0,0);
	tnow = clock();
	
	switch(gameState)
	{
	case LEVEL1:
	case LEVEL2:
	case LEVEL3:
		if(player.collidesWith(levelExit,collisionVector))
		{
			levelComplete = true;
		}

		for (int i=0;i< numWalls;i++){
			if (wall[i].collidesWith(player, collisionVector)){
				player.setPositionX(player.getPositionX() - player.getVelocity().x* frameTime);
				player.setPositionY(player.getPositionY() - player.getVelocity().y* frameTime);
				if(tnow - tsoundfx >1000){
					audio->playCue("Bump");
					tsoundfx = clock();
				}
			}

			for (int j=0;j<NUM_WEAPONS;j++){
				if(weapons[0][j]->getActive()){
					if (weapons[0][j]->collidesWith(wall[i],collisionVector)){
						weapons[0][j]->setActive(false);
					}

				}

			}


			for(int j=0; j<numGuards ; j++)
			{
				if(guard[j].getActive() && wall[i].collidesWith(guard[j], collisionVector)){
					guard[j].setPositionX(guard[j].getPositionX() - guard[j].getVelocity().x*frameTime);
					guard[j].setPositionY(guard[j].getPositionY() - guard[j].getVelocity().y*frameTime);
				}
			}
		}
		
		for(int i=0; i<numGuards; i++)
		{
			if (guard[i].getActive()){

				for (int j=0;j<NUM_WEAPONS;j++){
					if (weapons[0][j]->getActive()){
						if(weapons[0][j]->collidesWith(guard[i],collisionVector)){
														guard[i].setHealth(guard[i].getHealth() - guardNS::COLLISION_DAMAGE);
							guard[i].flinchTime = 0.0f;
							weapons[0][i]->setActive(false);
							if (guard[i].getHealth()<=0.0f){
								guard[i].setActive(false);
							}
						}
					}
				}
				
				if(!flinch && guard[i].collidesWith(player,collisionVector))
				{
					player.setHealth(player.getHealth() - guardNS::COLLISION_DAMAGE);
					flinch = true;
					flinchTime = 0.0f;
				}
				for(int j=0;j<numCrates;j++){
					if(!crate[j].CollidedThisFrame && D3DXVec2Length(&crate[j].getVelocity())>0.5){
						if(crate[j].collidesWith(guard[i],collisionVector) && guard[i].flinchTime > FLINCH_DURATION){
							guard[i].setHealth(guard[i].getHealth() - guardNS::COLLISION_DAMAGE);
							guard[i].flinchTime = 0.0f;
							crate[j].CollidedThisFrame=true;
							if (guard[i].getHealth()<=0.0f){
								guard[i].setActive(false);
							}
						}
					}
				}
			}
		}

		for (int i=0;i< numCrates;i++){
			if (crate[i].collidesWith(player, collisionVector)){
				crate[i].setVelocity(player.getVelocity()*2.5);
				audio->playCue("Bump");
				tsoundfx = clock();
			}
			for (int j=0;j<numWalls;j++){
				if(crate[i].collidesWith(wall[j], collisionVector)){
					//calculate elastic collision physics here
					VECTOR2 vf1,vf2;
					ElasticCollision(crate[i].getMass(), 10000.0f,crate[i].getVelocity(),VECTOR2(0.0f,0.0f),vf1,vf2);
					crate[i].setPositionX(crate[i].getPositionX() - crate[i].getVelocity().x*frameTime);
					crate[i].setPositionY(crate[i].getPositionY() - crate[i].getVelocity().y*frameTime);
					crate[i].setVelocity(vf1);
					crate[i].CollidedThisFrame = true;
				}
			}
		}

		for (int i=0;i<numCrates;i++){
			for (int j=0;j<numCrates;j++){
				if (i!=j && !crate[i].CollidedThisFrame && !crate[i].CollidedThisFrame){
					if (crate[i].collidesWith(crate[j],collisionVector)){
						audio->playCue("Bump");
						tsoundfx = clock();
						//calculate elastic collision physics here
						VECTOR2 vf1, vf2;
						ElasticCollision(crate[i].getMass(), crate[j].getMass(),crate[i].getVelocity(), crate[j].getVelocity(),vf1,vf2);
						crate[i].setVelocity(vf1);
						crate[j].setVelocity(vf2);
						crate[i].CollidedThisFrame = true;
						crate[j].CollidedThisFrame = true;
					}
				}
			}
		}
		
	}
}

void Rogue::ElasticCollision(float m1, float m2, VECTOR2 vi1, VECTOR2 vi2, VECTOR2 &vf1, VECTOR2 &vf2){
	//calculate elastic collision physics here
	float vxf1 = (vi1.x *(m1-m2) +2*m2*vi2.x)/(m1+m2);
	float vyf1 = (vi1.y *(m1-m2) +2*m2*vi2.y)/(m1+m2);
	float vxf2 = (vi2.x * (m2-m1) + 2*m1*vi1.x)/(m1+m2);
	float vyf2 = (vi2.y * (m2-m1) + 2*m1*vi1.y)/(m1+m2);
	vf1 = D3DXVECTOR2(vxf1,vyf1);
	vf2 = D3DXVECTOR2(vxf2,vyf2);
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Rogue::releaseAll()
{
	splashFont->onLostDevice();
	winFont->onLostDevice();
	loseFont->onLostDevice();
	PlayerTM.onLostDevice();
	GuardTM.onLostDevice();
	WallTM.onLostDevice();
	CrateTM.onLostDevice();
	ExitTM.onLostDevice();
	backgroundtm.onLostDevice();
	WeaponhudTM.onLostDevice();
	SplashTM.onLostDevice();
	GameOverTM.onLostDevice();
	GameWinTM.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Rogue::resetAll()
{
	splashFont->onResetDevice();
	winFont->onResetDevice();
	loseFont->onResetDevice();
	PlayerTM.onResetDevice();
	GuardTM.onResetDevice();
	WallTM.onResetDevice();
	CrateTM.onResetDevice();
	ExitTM.onResetDevice();
	backgroundtm.onResetDevice();
	WeaponhudTM.onResetDevice();
	SplashTM.onResetDevice();
	GameOverTM.onResetDevice();
	GameWinTM.onResetDevice();
	Game::resetAll();
	return;
}
