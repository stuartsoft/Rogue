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

#include <sstream>

class Rogue : public Game
{
private:
	// game items

	TextureManager PlayerTM;
	Player player;
	Wall wall[100];
	TextureManager WallTM;
	Crate crate[100];
	TextureManager CrateTM;
	
	VECTOR2 camera;

	GameStates gameState;
	float timeInState;

	Menu* menu;


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
};

#endif
