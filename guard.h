#ifndef _GUARD_H
#define _GUARD_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "platform.h"
#include "bullet.h"

namespace guardNS
{
    const int WIDTH = 128;                   // image width
    const int HEIGHT = 128;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float MASS = 300.0f;              // mass
	const float MAX_HEALTH = 4.0f;
	const int SPEED = 200;
	const int FLEE_SPEED = 400;
	const int MAX_SPEED_X = 750;
	const int MAX_SPEED_Y = 1000;
	const float SCALE = 1.0;

	const int TEXTURE_COL = 2;

	const float PATROL_PERCENT = .8;

	const float FLEE_DIST = GAME_WIDTH/4;
	const float ATTACK_DIST = GAME_WIDTH/3;

	const int COLLISION_DAMAGE = 50;

	const float SHOOT_COOLDOWN = 1.0;

}

namespace gunNS
{
	const int WIDTH = 43;
	const int HEIGHT = 8;
	const float SCALE = 2.0;
}

class Guard: public Entity{
private:
	Image gun;
	
	direction facingDir;
	direction patrolDir;
	direction lastFrameFace;

	int patrolAnchor;
	int patrolWidth;
	Platform* patrolPlatform;
	
	Entity* target;
	float dist;
	VECTOR2 distVec;
	bool targetAquired;
	float targetAngle;

	float timeSinceShoot;

	void spawnBullet(VECTOR2 pos, VECTOR2 vel);

public:
	Guard();
	direction FacingDir();
	void Guard::draw();
	void Guard::update(float frameTime);
	void Guard::ai();

	void setVelY(int y) {velocity.y = y;}

	void gunInit(TextureManager* gunTM);
	void setTarget();
	void initializePatrol(Platform* plat, Entity* t);

	Bullet bullets[BULLETS_PER_GUARD];
	void bulletsInit(TextureManager* bulletTM, Game* g);

};

#endif