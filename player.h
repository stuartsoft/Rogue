#ifndef _PLAYER_H
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"

namespace playerNS{
	const int WIDTH = 34;                   // image width
	const int HEIGHT = 34;                  // image height
	const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
	const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const float MAX_HEALTH = 100.0f;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 750;
	const int SPEED = 350;

	const int TEXTURE_COL = 1;
	const float SCALE = 3.0f;
}

class Player: public Entity{
private:
	
public:
	Player();
	void Player::draw();
	void Player::update(float frameTime);
};

#endif