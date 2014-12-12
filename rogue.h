// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.h v1.0

#ifndef _THREECS_H              // Prevent multiple definitions if this 
#define _THREECS_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "constants.h"
#include "entity.h"
#include "player_BOOM.h"
#include "wall.h"
#include "crate.h"
#include "menu.h"
#include "guard.h"
#include "Weaponhud.h"
#include "weapon.h"
#include "shuriken.h"
#include "c4.h"
#include <time.h>

#include <sstream>

class Rogue : public Game
{
private:
	// game items
	int numGuards, numWalls, numCrates;

	TextureManager PlayerTM;
	TextureManager WallTM;
	TextureManager GuardTM;
	TextureManager CrateTM;
	TextureManager WeaponTM;
	TextureManager WeaponhudTM;

	Player player;
	Guard guard[MAX_GUARDS];
	Wall wall[MAX_WALLS];
	Crate crate[MAX_CRATES];
	Weapon * weapons[4][NUM_WEAPONS]; 

	TextureManager ExitTM;
	Entity levelExit;

	Weaponhud WeaponHud;
	
	VECTOR2 camera;

	TextDX* splashFont;
	TextDX* winFont;
	TextDX* loseFont;

	TextureManager backgroundtm;
	Image background;

	TextureManager SplashTM, GameOverTM, GameWinTM, TutorialTM;
	Image Splash, GameOverSplash, GameWinSplash, Tutorial;

	TextureManager MainMenuTM;
	Image MainMenu;

	TextureManager DarknessTM, RedDarknessTM;
	Image Darkness, RedDarkness;

	GameStates gameState;
	float timeInState;
	clock_t tsoundfx;
	clock_t tnow;
	clock_t tmouseclick;
	Menu* menu;

	int score;

	void loadLevel();
	bool levelComplete;
	bool flinch;
	float flinchTime;
	bool prevMouseLState;
	bool prevMouseRState;
	DWORD healthFilter;

	void recordHighScore(int s);

public:
	Rogue();
	virtual ~Rogue();
	void initialize(HWND hwnd);
	void reset();
	void gameStateUpdate(float f);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
	void ElasticCollision(float m1, float m2, VECTOR2 vi1, VECTOR2 vi2, VECTOR2 &vf1, VECTOR2 &vf2);

};

#endif
