// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "ninjaGhost.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

//=============================================================================
// Constructor
//=============================================================================
NinjaGhost::NinjaGhost()
{
	gameOverFont1 = new TextDX;
	gameOverFont2 = new TextDX;
	gameCompleteFont1 = new TextDX;
	gameCompleteFont2 = new TextDX;
	cheatFont = new TextDX;
}

//=============================================================================
// Destructor
//=============================================================================
NinjaGhost::~NinjaGhost()
{
	releaseAll();               // call deviceLost() for every graphics item
	SAFE_DELETE(gameOverFont1);
	SAFE_DELETE(gameOverFont2);
	SAFE_DELETE(gameCompleteFont1);
	SAFE_DELETE(gameCompleteFont2);
	SAFE_DELETE(cheatFont);
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void NinjaGhost::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	graphics->setBackColor(0x000000);
	if(!PlayerTextureManager.initialize(graphics, "images\\PlayerB.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player texture"));
	if(!player.initialize(this, Playerns::WIDTH, Playerns::HEIGHT, 2, &PlayerTextureManager))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init player"));

	player.setFrames(0,3);
	player.setCurrentFrame(0);
	player.setFrameDelay(0.33);

	for(int i=0; i<MAX_LIVES; i++)
	{
		if(!liveCounter[i].initialize(this, lifeNS::WIDTH, lifeNS::HEIGHT, 2, &PlayerTextureManager))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init live counter"));
	}

	if(!BackgroundTM.initialize(graphics, "images\\background.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init background texture"));

	if (!Backgroundimg[0].initialize(graphics, 1280,720,0,&BackgroundTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init background image"));
	if (!Backgroundimg[1].initialize(graphics, 1280,720,0,&BackgroundTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init background image"));

	if(!BlackBoardersTM.initialize(graphics, "images\\blackbars.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init black boarder texture"));
	if(!BlackBoarders.initialize(graphics, 1280,720,0,&BlackBoardersTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init black boarder image"));
	
	if(!RedBoardersTM.initialize(graphics, "images\\Redbars.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init Red boarder texture"));
	if(!RedBoarders.initialize(graphics, 1280,720,0,&RedBoardersTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init Red boarder image"));
	

	if(!PlatformTM.initialize(graphics, "images\\platform.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init platform texture"));
	
	for (int i=0;i<MAX_PLATFORMS;i++){
		if(!platforms[i].initialize(this, Platformns::WIDTH, Platformns::HEIGHT, 0, &PlatformTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error init platform"));
	}

	if(!GuardTM.initialize(graphics, GUARD_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init guard texture"));
	if(!GunTM.initialize(graphics, "images\\gun.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init gun texture"));
	if(!BulletTM.initialize(graphics, "images\\bullet.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init bullet texture"));

	for(int i=0; i<MAX_GUARDS; i++)
	{
		if(!guards[i].initialize(this, guardNS::WIDTH, guardNS::HEIGHT, guardNS::TEXTURE_COL, &GuardTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init guard"));
		guards[i].setX(0);
		guards[i].setY(0);
		guards[i].gunInit(&GunTM);
		guards[i].bulletsInit(&BulletTM,this);
	}

	if(!KatanaTM.initialize(graphics, KATANA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init katana texture"));
	if(!katana.initialize(this, katanaNS::WIDTH, katanaNS::HEIGHT, 0, &KatanaTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init katana"));
	katana.setActive(false);
	katana.setPlayer(&player);

	if(!ShurikenTM.initialize(graphics, SHURIKEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init shuriken texture"));
	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		if(!shuriken[i].initialize(this, shurikenNS::WIDTH, shurikenNS::HEIGHT, 0, &ShurikenTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init shuriken"));
		if(!shurikenIndicator[i].initialize(graphics, shurikenNS::WIDTH, shurikenNS::HEIGHT, 0, &ShurikenTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init shuriken ui image"));
	}
	
	if(!ExitTM.initialize(graphics, DOOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init door texture"));
	if(!LevelExit.initialize(this, 64, 128, 0, &ExitTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init door"));
	LevelExit.setCollisionType(entityNS::BOX);
	LevelExit.setCollisionBox(-32,32,-64,64);

	// splash screen init
	if(!MainMenuSplashTM.initialize(graphics, MAIN_MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init menu splash texture"));
	if(!MainMenuSplash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &MainMenuSplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init menu splash image"));
	MainMenuSplash.setX(0);
	MainMenuSplash.setY(0);

	if(!Level1SplashTM.initialize(graphics, SPLASH1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level1 splash texture"));
	if(!Level1Splash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &Level1SplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level1 splash image"));
	Level1Splash.setX(0);
	Level1Splash.setY(0);

	if(!Level2SplashTM.initialize(graphics, SPLASH2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level2 splash texture"));
	if(!Level2Splash.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &Level2SplashTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init level2 splash image"));
	Level2Splash.setX(0);
	Level2Splash.setY(0);

	if(!TutorialTM.initialize(graphics, TUTORIAL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init tutorial texture"));
	if(!Tutorial.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &TutorialTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init tutorial image"));
	Tutorial.setX(0);
	Tutorial.setY(0);

	if(!GameOverTM.initialize(graphics, "images\\gameover.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init gameover texture"));
	if(!GameOverFilter.initialize(graphics, GAME_WIDTH, GAME_HEIGHT, 0, &GameOverTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init gameover filter"));
	GameOverFilter.setX(0);
	GameOverFilter.setY(0);

	if(gameOverFont1->initialize(graphics, 72, true, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover font"));
	if(gameOverFont2->initialize(graphics, 36, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gameover font"));
	gameOverFont1->setFontColor(graphicsNS::WHITE);
	gameOverFont2->setFontColor(graphicsNS::WHITE);

	if(gameCompleteFont1->initialize(graphics, 72, true, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gamecomplete font"));
	if(gameCompleteFont2->initialize(graphics, 36, false, false, "Forte") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gamecomplete font"));
	gameCompleteFont1->setFontColor(graphicsNS::BLACK);
	gameCompleteFont2->setFontColor(graphicsNS::BLACK);

	if(cheatFont->initialize(graphics, 36, false, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheat font"));

	// menu init
	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	// state init
	timeInState = 0;
	gameState = MAIN_MENU;

	//var init
	timeSinceThrow = 0;
	ammo = MAX_SHURIKEN;
	score = 0;
	lives = MAX_LIVES;

	flinch = false;

	Invincibility = false;
	UnlimitedAmmo = false;

	timeSinceMenuPress = 0;

	audio->playCue("IsolatedMind");
	time(&t_backgroundmusicstart);

	return;
}

void NinjaGhost::resetVars()
{
	ammo = MAX_SHURIKEN;
	score = 0;
	lives = MAX_LIVES;
}

//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void NinjaGhost::reset()
{
	player.setVelocity(VECTOR2(0,0));
	player.setHealth(Playerns::MAX_HEALTH);
	player.setX(0);
	player.setY(0);

	flinch = false;
	timeSinceThrow = 0;

	for(int i=0; i<MAX_GUARDS; i++)
	{
		guards[i].setActive(false);
		guards[i].setX(0);
		guards[i].setY(0);
		for(int j=0; j<BULLETS_PER_GUARD; j++)
		{
			guards[i].bullets[j].setActive(false);
			guards[i].bullets[j].setX(0);
			guards[i].bullets[j].setY(0);
		}
	}
	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		shuriken[i].setActive(false);
		shuriken[i].setX(0);
		shuriken[i].setY(0);
	}
	katana.setActive(false);
	LevelExit.setActive(false);

	for(int i=0; i<MAX_PLATFORMS; i++)
	{
		platforms[i].setActive(false);
		platforms[i].setX(0);
		platforms[i].setY(0);
	}

	return;
}


//=================================
// initialize game items for level1
//=================================
void NinjaGhost::LoadLevel()
{
	player.setX(0);
	player.setY(0);
	player.setVelocity(VECTOR2(0,0));

	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		shurikenIndicator[i].setX(GAME_WIDTH/2 + shurikenNS::WIDTH*(i-2));
		shurikenIndicator[i].setY(0);
	}
	for(int i=0; i<MAX_LIVES; i++)
	{
		liveCounter[i].setX(GAME_WIDTH - lifeNS::WIDTH*lifeNS::SCALE*(i+1));
		liveCounter[i].setY(0);
	}

	//position platforms
	YOffset = 0;
	ifstream myfile;
	if(gameState == LEVEL1)
		myfile.open("Levels\\L1.txt");
	if(gameState == LEVEL2)
		myfile.open("Levels\\L2.txt");
	if (myfile.is_open())
	{
		for (int i=0;i<LEVEL_PLATFORMS();i++){
			string line;
			getline(myfile,line);
			int x,y;
			x = atoi(strtok(strdup(line.c_str()),","));
			y = atoi(strtok(NULL,","));
			platforms[i].setX(x);
			platforms[i].setY(y);
			platforms[i].setActive(true);
		}
		LevelExit.setX(platforms[LEVEL_PLATFORMS()-1].getCenterX()-32);
		LevelExit.setY(platforms[LEVEL_PLATFORMS()-1].getY()-128);
		LevelExit.setActive(true);
		for(int i=0; i<LEVEL_GUARDS(); i++)
		{
			string line;
			getline(myfile,line);
			int p;
			p = atoi(line.c_str());
			guards[i].setActive(true);
			guards[i].initializePatrol(&platforms[p], &player);
		}
	}
	
	myfile.close();
}


//===============================
// update game state information
//===============================
void NinjaGhost::gameStateUpdate()
{
	timeInState += frameTime;
	if(gameState == MAIN_MENU && timeInState >= 0.5 && input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 0)
	{
		gameState = INTRO1;
		timeInState = 0;
	}
	if(gameState == MAIN_MENU && timeInState >= 0.5 && input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 1)
	{
		gameState = TUTORIAL;
		timeInState = 0;
	}
	if(gameState == TUTORIAL && timeInState >= 0.5 && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
		timeInState = 0;
	}
	if(gameState == INTRO1 && timeInState > 1.5)
	{
		gameState = LEVEL1;
		timeInState = 0;
		LoadLevel();
	}
	if(gameState == INTRO2 && timeInState > 1.5)
	{
		gameState = LEVEL2;
		timeInState = 0;
		LoadLevel();
	}
	if(gameState == LEVEL1 && input->isKeyDown(E_KEY) && player.collidesWith(LevelExit,collisionVec))
	{
		gameState = INTRO2;
		timeInState = 0;
		reset();
	}
	if(gameState == LEVEL2 && input->isKeyDown(E_KEY) && player.collidesWith(LevelExit,collisionVec))
	{
		gameState = GAME_COMPLETE;
		timeInState = 0;
		reset();
	}
	if(gameState == GAME_OVER && timeInState >= 0.5 && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
		timeInState = 0;
		reset();
		resetVars();
	}
	if(gameState == GAME_COMPLETE && timeInState >= 0.5 && input->isKeyDown(ENTER_KEY))
	{
		gameState = MAIN_MENU;
		timeInState = 0;
		reset();
		resetVars();
	}
}
//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void NinjaGhost::update()
{
	time(&t_now);
	if (difftime(t_now, t_backgroundmusicstart)>123){
		time(&t_backgroundmusicstart);
		audio->playCue("IsolatedMind");
	}

	gameStateUpdate();
	if(input->isKeyDown(ESC_KEY))
	{
		exitGame();
	}

	switch(gameState)
	{
	case MAIN_MENU:
		mainMenu->update();
		timeSinceMenuPress += frameTime;
		if(input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 3)
		{
			exitGame();
		}
		if(input->isKeyDown(ENTER_KEY) && mainMenu->getSelectedItem() == 2 && timeSinceMenuPress > 0.5)
		{
			timeSinceMenuPress = 0;
			if(!Invincibility && !UnlimitedAmmo)
			{
				Invincibility = true;
			}
			else if(Invincibility && !UnlimitedAmmo)
			{
				Invincibility = false;
				UnlimitedAmmo = true;
			}
			else if(!Invincibility && UnlimitedAmmo)
			{
				Invincibility = true;
			}
			else if(Invincibility && UnlimitedAmmo)
			{
				Invincibility = false;
				UnlimitedAmmo = false;
			}
		}
		break;
	case LEVEL1:
	case LEVEL2:
		if(player.getHealth() <= 0)
		{
			if(lives <= 0)
			{
				gameState = GAME_OVER;
				timeInState = 0;
			}
			else
			{
				lives--;
				reset();
				LoadLevel();
			}
		}
		if(player.getY() >= platforms[LEVEL_PLATFORMS()-1].getY()+GAME_HEIGHT)
		{
			gameState = GAME_OVER;
			timeInState = 0;
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
		healthFilter = D3DCOLOR_ARGB(int((1-player.getHealth()/Playerns::MAX_HEALTH)*255),255,255,255);		

		if(input->isKeyDown(ENTER_KEY))
			guards[0].setActive(true);

		player.update(frameTime, platforms);
		VECTOR2 tempv(0,0);

		if( (player.getCenter()->y > GAME_HEIGHT*2/3) && player.getVelocity().y >0){
			tempv.y = -player.getVelocity().y;
		}
		else if(player.getCenter()->y < GAME_HEIGHT/3 && player.getVelocity().y<0){
			tempv.y = -player.getVelocity().y;
		}
		player.setY(player.getY() +tempv.y*frameTime);


		for (int i=0;i<LEVEL_PLATFORMS();i++){
			platforms[i].setVelocity(tempv);
			platforms[i].update(frameTime);
		}
		LevelExit.setVelocity(tempv);
		LevelExit.setY(LevelExit.getY()+LevelExit.getVelocity().y*frameTime);

		for(int i=0; i<LEVEL_GUARDS(); i++)
		{
			guards[i].setVelY(tempv.y);
			guards[i].update(frameTime);
			for(int j=0; j<BULLETS_PER_GUARD; j++)
			{
				guards[i].bullets[j].addVelY(tempv.y);
				guards[i].bullets[j].update(frameTime);
				guards[i].bullets[j].subVelY(tempv.y);
			}
		}
		
		katana.update(frameTime);
		timeSinceThrow += frameTime;
		if(timeSinceThrow >= 100)
			timeSinceThrow = 30;
		if(ammo > 0 && timeSinceThrow >= THROW_COOLDOWN && input->getMouseRButton())
		{
			audio->playCue("Swoosh");
			VECTOR2 pos = VECTOR2(player.getCenterX(),player.getCenterY());
			VECTOR2 dir = VECTOR2(input->getMouseX(),input->getMouseY()) - pos;
			VECTOR2 normdir;
			D3DXVec2Normalize(&normdir,&dir);
			normdir *= min(D3DXVec2Length(&dir)*shurikenNS::SPEED/GAME_WIDTH,shurikenNS::MAX_SPEED);
			spawnShuriken(pos, normdir);
			timeSinceThrow = 0;
			if(!UnlimitedAmmo)
				ammo -= 1;
		}
		for(int i=0; i<MAX_SHURIKEN; i++)
		{
			if(shuriken[i].getActive())
			{
				shuriken[i].update(frameTime);
			}
		}
	}
}

//=============================================================================
// render game items
//=============================================================================
void NinjaGhost::render()
{
	stringstream scorestr;
	scorestr << "Your Score: ";
	scorestr << score;
	graphics->spriteBegin();
	switch(gameState)
	{
	case MAIN_MENU:
		MainMenuSplash.draw();
		mainMenu->displayMenu();
		if(Invincibility)
		{
			cheatFont->print("INVINCIBLE!",GAME_WIDTH/3,GAME_HEIGHT/20);
		}
		if(UnlimitedAmmo)
		{
			cheatFont->print("UNLIMITED AMMO!",2*GAME_WIDTH/3,GAME_HEIGHT/20);
		}
		break;
	case INTRO1:
		Level1Splash.draw();
		break;
	case INTRO2:
		Level2Splash.draw();
		break;
	case LEVEL1:
	case LEVEL2:
	case GAME_OVER:
		Backgroundimg[0].draw();
		
		for (int i=0;i<LEVEL_PLATFORMS();i++)
		{
			platforms[i].draw();
		}
		LevelExit.draw();

		for(int i=0; i<LEVEL_GUARDS(); i++)
		{
			guards[i].draw();
		}

		if(!flinch)
			player.draw();
		else
			player.draw(graphicsNS::ALPHA25);

		if(katana.getActive())
			katana.draw();

		for(int i=0; i<MAX_SHURIKEN; i++)
		{
			if(shuriken[i].getActive())
			{
				shuriken[i].draw();
			}
		}
		for(int i=0; i<min(ammo,MAX_SHURIKEN) && i>=0; i++)
		{
			shurikenIndicator[i].draw();
		}
		if(player.collidesWith(LevelExit,collisionVec))
		{
			gameOverFont2->setFontColor(graphicsNS::RED);
			gameOverFont2->print("Press E to proceed", 2*GAME_WIDTH/5, GAME_HEIGHT/2);
		}
		BlackBoarders.draw();
		RedBoarders.draw(healthFilter);
		for(int i=0; i<min(lives,MAX_LIVES) && i>=0; i++)
		{
			liveCounter[i].draw();
		}

		if(gameState == GAME_OVER)
		{
			//graphics->setBackColor(graphicsNS::BLACK);
			GameOverFilter.draw();
			gameOverFont2->setFontColor(graphicsNS::WHITE);
			gameOverFont1->print("Game Over...",GAME_WIDTH/3,GAME_HEIGHT/4);
			gameOverFont2->print(scorestr.str(),GAME_WIDTH/3,GAME_HEIGHT/2);
			gameOverFont2->print("Press Enter to return to main menu",GAME_WIDTH/3,3*GAME_HEIGHT/4);
		}
		break;
	case GAME_COMPLETE:
		graphics->setBackColor(graphicsNS::WHITE);
		gameCompleteFont1->print("Victory is yours!",GAME_WIDTH/3,GAME_HEIGHT/4);
		gameCompleteFont2->print(scorestr.str(),GAME_WIDTH/3,GAME_HEIGHT/2);
		gameCompleteFont2->print("Press Enter to return to main menu",GAME_WIDTH/3,3*GAME_HEIGHT/4);
		break;
	case TUTORIAL:
		Tutorial.draw();
		break;
	default:
		break;
	}
	
	graphics->spriteEnd();
}


//=============================
// handles entity ai
//=============================
void NinjaGhost::ai()
{
	switch(gameState)
	{
	case LEVEL1:
	case LEVEL2:
		for(int i=0; i<LEVEL_GUARDS(); i++)
		{
			if(guards[i].getActive())
			{
				guards[i].ai();
			}
		}
	}
}

//==================================================================
// Handle collision between entities
//==================================================================
void NinjaGhost::collisions()
{
	if(gameState == LEVEL1 || gameState == LEVEL2)
	{
		collisionVec = VECTOR2(0,0);

		//platforming
		for (int i=0;i<LEVEL_PLATFORMS();i++){
			for (int j = 0;j<MAX_SHURIKEN;j++){
				if (shuriken[j].getActive() && platforms[i].collidesWith(shuriken[j],collisionVec))
					shuriken[j].setActive(false);
			}


			if(player.collidesWith(platforms[i], collisionVec)){
				if (player.getVelocity().y >0){
					if (player.getY()+player.getHeight()*player.getScale() < platforms[i].getY()+platforms[i].getHeight()*platforms[i].getScale()){
						player.setY(platforms[i].getY()-player.getHeight()*player.getScale());
						VECTOR2 tempv = player.getVelocity();
						tempv.y = 0;
						player.setVelocity(tempv);
					}
				}
			}
		}

		//player damaged by bullets
		for(int i=0; i<LEVEL_GUARDS(); i++)
		{
			for(int j=0; j<BULLETS_PER_GUARD; j++)
			{
				//check if bullet collides with platforms
				if(guards[i].bullets[j].getActive()){
					for (int k = 0;k<LEVEL_PLATFORMS();k++){
						if (platforms[k].collidesWith(guards[i].bullets[j],collisionVec))
							guards[i].bullets[j].setActive(false);
					}

				}
				if(!flinch && guards[i].bullets[j].getActive() && player.collidesWith(guards[i].bullets[j],collisionVec) && !Invincibility)
				{
					player.setHealth(player.getHealth()-bulletNS::COLLISION_DAMAGE);
					guards[i].bullets[j].setActive(false);
				}
				if(guards[i].bullets[j].getActive() && katana.getActive() && katana.collidesWith(guards[i].bullets[j],collisionVec))
				{
					guards[i].bullets[j].setActive(false);
				}
			}

			if(guards[i].getActive())
			{
				if(katana.getActive() && katana.collidesWith(guards[i],collisionVec))
				{
					guards[i].setActive(false);
					score += SCORE_PER_MELEE_KILL;
					player.setHealth(min(player.getHealth()+HEALTH_PER_MELEE_KILL,Playerns::MAX_HEALTH));
					if(!UnlimitedAmmo)
						ammo = min(AMMO_PER_MELEE_KILL+ammo,MAX_SHURIKEN);
				}
				
				if(!flinch && player.collidesWith(guards[i],collisionVec) && !Invincibility)
				{
					player.setHealth(player.getHealth()-guardNS::COLLISION_DAMAGE);
					flinch = true;
					flinchTime = 0;
				}
	
				for(int j=0; j<MAX_SHURIKEN; j++)
				{
					if(shuriken[j].getActive() && shuriken[j].collidesWith(guards[i],collisionVec))
					{
						guards[i].setActive(false);
						shuriken[j].setActive(false);
						score += SCORE_PER_RANGED_KILL;
						player.setHealth(min(player.getHealth()+HEALTH_PER_RANGED_KILL,Playerns::MAX_HEALTH));
						if(!UnlimitedAmmo)
							ammo = min(AMMO_PER_RANGED_KILL+ammo,MAX_SHURIKEN);
					}
				}

			}
		}
	
	}
}

//==================================================================
// grab a throwing star and activate it w/ given position & velocity
//==================================================================
void NinjaGhost::spawnShuriken(VECTOR2 pos, VECTOR2 vel)
{
	Shuriken* first = nullptr;
	for(int i=0; i<MAX_SHURIKEN; i++)
	{
		if(!(shuriken[i].getActive()))
		{
			first = &shuriken[i];
			break;
		}
	}
	if(first != nullptr)
	{
		first->setActive(true);
		first->setVelocity(vel);
		first->setX(pos.x);
		first->setY(pos.y);
	}
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void NinjaGhost::releaseAll()
{
	gameOverFont1->onLostDevice();
	gameOverFont2->onLostDevice();
	gameCompleteFont1->onLostDevice();
	gameCompleteFont2->onLostDevice();
	cheatFont->onLostDevice();
	GuardTM.onLostDevice();
	KatanaTM.onLostDevice();
	ShurikenTM.onLostDevice();
	BulletTM.onLostDevice();
	GunTM.onLostDevice();
	PlayerTextureManager.onLostDevice();
	MainMenuSplashTM.onLostDevice();
	Level1SplashTM.onLostDevice();
	Level2SplashTM.onLostDevice();
	TutorialTM.onLostDevice();
	BackgroundTM.onLostDevice();
	BlackBoardersTM.onLostDevice();
	RedBoardersTM.onLostDevice();
	GameOverTM.onLostDevice();
	ExitTM.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void NinjaGhost::resetAll()
{
	gameOverFont1->onResetDevice();
	gameOverFont2->onResetDevice();
	gameCompleteFont1->onResetDevice();
	gameCompleteFont2->onResetDevice();
	cheatFont->onResetDevice();
	GuardTM.onResetDevice();
	KatanaTM.onResetDevice();
	ShurikenTM.onResetDevice();
	GunTM.onResetDevice();
	BulletTM.onResetDevice();
	PlayerTextureManager.onResetDevice();
	MainMenuSplashTM.onResetDevice();
	Level1SplashTM.onResetDevice();
	Level2SplashTM.onResetDevice();
	TutorialTM.onResetDevice();
	BackgroundTM.onResetDevice();
	BlackBoardersTM.onResetDevice();
	RedBoardersTM.onResetDevice();
	GameOverTM.onResetDevice();
	ExitTM.onResetDevice();
	Game::resetAll();
	return;
}
