// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.h v1.0

#ifndef _THREECS_H              // Prevent multiple definitions if this 
#define _THREECS_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "entity.h"
#include "Player.h"
#include "menu.h"
#include "katana.h"
#include "shuriken.h"
#include "platform.h"
#include "guard.h"
#include "bullet.h"
#include "life.h"
#include <sstream>

#define LEVEL_GUARDS() ((gameState == LEVEL1) ? LEVEL1_GUARDS : LEVEL2_GUARDS)
#define LEVEL_PLATFORMS() ((gameState == LEVEL1) ? LEVEL1_PLATFORMS : LEVEL2_PLATFORMS)

class NinjaGhost : public Game
{
private:
	// game items
	int YOffset;
	Player player;
	Platform platforms[MAX_PLATFORMS];
	Image Backgroundimg[2];
	Image BlackBoarders;
	Image RedBoarders;
	time_t t_backgroundmusicstart;
	time_t t_now;

	TextureManager GuardTM;

	TextureManager BackgroundTM;
	TextureManager BlackBoardersTM;
	TextureManager RedBoardersTM;
	TextureManager PlayerTextureManager;
	TextureManager KatanaTM;
	TextureManager ShurikenTM;
	TextureManager BulletTM;
	TextureManager PlatformTM;
	TextureManager GunTM;
	TextureManager ExitTM;

	Image shurikenIndicator[MAX_SHURIKEN];

	Katana katana;
	Shuriken shuriken[MAX_SHURIKEN];
	
	Guard guards[MAX_GUARDS];

	Entity LevelExit;

	// game variables
	float timeSinceThrow;
	VECTOR2 collisionVec;

	int ammo;
	int score;
	int lives;
	Life liveCounter[MAX_LIVES];
	
	bool flinch;
	float flinchTime;
	bool Invincibility;
	bool UnlimitedAmmo;

	// MENU/SPLASH STUFF
	Menu *mainMenu;

	TextureManager MainMenuSplashTM;
	Image MainMenuSplash;
	TextureManager Level1SplashTM;
	Image Level1Splash;
	TextureManager Level2SplashTM;
	Image Level2Splash;
	TextureManager TutorialTM;
	Image Tutorial;
	TextureManager GameOverTM;
	Image GameOverFilter;

	TextDX *gameOverFont1;
	TextDX *gameOverFont2;

	TextDX *gameCompleteFont1;
	TextDX *gameCompleteFont2;
	
	TextDX *cheatFont;

	COLOR_ARGB healthFilter;

	// STATE STUFF
	float timeInState;
	void gameStateUpdate();
	GameStates gameState;

	void LoadLevel();

	float timeSinceMenuPress;
	float flashTime;

	// functs
	void spawnShuriken(VECTOR2 pos, VECTOR2 vel);
	void resetVars();

public:
	NinjaGhost();
	virtual ~NinjaGhost();
	void initialize(HWND hwnd);
	void reset();
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};

#endif
