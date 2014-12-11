#ifndef GUARD_H
#define GUARD_H

#define WIN32_LEAN_AND_MEAN
#include "entity.h"

namespace guardNS{
	const int WIDTH = 68;                   // image width
	const int HEIGHT = 68;                  // image height
	const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
	const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const float MAX_HEALTH = 100.0f;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 750;
	const int SPEED = 100;
	const float MASS = 5.0f;//5Kg

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

	const float VISION_ANGLE = PI/float(4);
	const int VISION_LENGTH = 200.0f;
	const int PATROL_SIZE = 256;

	const float COLLISION_DAMAGE = 50.0f;
}

namespace swordNS {
	const int WIDTH = 100;
	const int HEIGHT = 100;
	const float SCALE = 1.0f;	
}

class Guard: public Entity{
private:
	entityNS::direction facingDir;
	Entity* target;
	float rad;
	VECTOR2 tarVec;
	bool alert;
	float alertTime;
	VECTOR2 anchor;
	bool patrolUp;
	bool onPatrol;
	VECTOR2 patrolTar;
	VECTOR2 patrolPoint1;
	VECTOR2 patrolPoint2;

public:
	float flinchTime;

	Guard();

	void Guard::draw(VECTOR2 cam);
	void Guard::update(float frameTime);
	void Guard::ai(bool &hey);
	
	void Guard::reset();
	void setTarget(Entity* t){target = t;}
	void setPatrol(int x, int y, bool up);
	void deltaTrack(VECTOR2 tar);

	float getRad(){return rad;}

};

#endif