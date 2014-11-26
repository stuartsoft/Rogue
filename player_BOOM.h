#ifndef _PLAYER_H
#define _PLAYER_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"

namespace playerNS{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 64;                  // image height
	const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
	const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const float MAX_HEALTH = 100.0f;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 750;
	const int SPEED = 150;

	const int TEXTURE_COL = 4;
	const float SCALE = 1.0f;

	const int DOWN_START = 0;
	const int DOWN_END = 3;
	const int LEFT_START = 4;
	const int LEFT_END = 7;
	const int RIGHT_START = 8;
	const int RIGHT_END = 11;
	const int UP_START = 12;
	const int UP_END = 15;
	const float FRAME_DELAY = 0.15f;
}

class Player: public Entity{
private:
	direction facingDir;
public:
	Player();
	void Player::draw();
	void Player::update(float frameTime);
};

#endif