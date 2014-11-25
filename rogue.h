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
#include "player.h"

#include <sstream>

class Rogue : public Game
{
private:
	// game items

	TextureManager PlayerTM;
	Player player;

public:
	Rogue();
	virtual ~Rogue();
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
