#include "guard.h"

Guard::Guard()
{
	spriteData.width = guardNS::WIDTH;           // size of Ship1
	spriteData.height = guardNS::HEIGHT;
	spriteData.x = guardNS::X;                   // location on screen
	spriteData.y = guardNS::Y;
	spriteData.rect.bottom = guardNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = guardNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = guardNS::WIDTH/2.0;
	mass = guardNS::MASS;
	collisionType = entityNS::BOX;
	setHealth(guardNS::MAX_HEALTH);
	health = guardNS::MAX_HEALTH;
	facingDir = right;
	patrolDir = right;

	edge.left = -guardNS::WIDTH/5;
	edge.right = guardNS::WIDTH/5;
	edge.top = -guardNS::HEIGHT/2;
	edge.bottom = guardNS::HEIGHT/2;

	setFrameDelay(.1f);
	setLoop(true);

	dist = 0;
	target = nullptr;
	targetAquired = false;
	timeSinceShoot = 0;

	lastFrameFace = none;
	facingDir = none;
	patrolDir = none;
}

void Guard::gunInit(TextureManager* gunTM)
{
	if(!gun.initialize(graphics, gunNS::WIDTH, gunNS::HEIGHT, 2, gunTM))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error init gun image"));
	gun.setScale(gunNS::SCALE);
}

void Guard::bulletsInit(TextureManager* bulletTM, Game* g)
{
	for(int i=0; i<BULLETS_PER_GUARD; i++)
	{
		if(!bullets[i].initialize(g, bulletNS::WIDTH, bulletNS::HEIGHT, 0, bulletTM))
			throw(GameError(gameErrorNS::FATAL_ERROR,"Error init bullets"));
		bullets[i].setScale(.6);
	}
}

void Guard::spawnBullet(VECTOR2 pos, VECTOR2 vel)
{
	audio->playCue("Fire");
	Bullet* first = nullptr;
	for(int i=0; i<BULLETS_PER_GUARD; i++)
	{
		if(!(bullets[i].getActive()))
		{
			first = &bullets[i];
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

void Guard::draw()
{
	if(active)
	{
		Image::draw();
		gun.draw();
	}
	for(int i=0; i<BULLETS_PER_GUARD; i++)
	{
		if(bullets[i].getActive())
		{
			bullets[i].draw();
		}
	}
}

direction Guard::FacingDir()
{
	return facingDir;
}

void Guard::initializePatrol(Platform* plat, Entity* t)
{
	patrolPlatform = plat;
	patrolAnchor = patrolPlatform->getCenterX();
	patrolWidth = Platformns::WIDTH/2 * guardNS::PATROL_PERCENT;
	spriteData.y = patrolPlatform->getY()-guardNS::HEIGHT*guardNS::SCALE;
	spriteData.x = patrolAnchor;
	patrolDir = right;

	target = t;
}

void Guard::update(float frameTime){
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	timeSinceShoot += frameTime;

	if(facingDir == left && lastFrameFace != left)
	{
		setFrames(2,3);
		lastFrameFace = left;
	}
	if(facingDir == right && lastFrameFace != right)
	{
		setFrames(0,1);
		lastFrameFace = right;
	}
	if(velocity.x == 0)
	{
		if(facingDir == left)
			setCurrentFrame(3);
		if(facingDir == right)
			setCurrentFrame(0);
	}

	

	setFrameDelay(0.25);

	if(facingDir == right)
	{
		gun.setX(getCenterX()+getScale()*guardNS::WIDTH/4-gunNS::WIDTH*gunNS::SCALE/2);
		gun.setY(getCenterY()+5);
		gun.setCurrentFrame(1);
		gun.setRadians(0);
	}
	if(facingDir == left)
	{
		
		gun.setX(getCenterX()-getScale()*guardNS::WIDTH/4-gunNS::WIDTH*gunNS::SCALE/2);
		gun.setY(getCenterY()+5);
		gun.setCurrentFrame(2);
		gun.setRadians(0);
	}
}

void Guard::ai()
{
	distVec = VECTOR2(target->getCenterX(),target->getCenterY()) - VECTOR2(getCenterX(),getCenterY());
	dist = D3DXVec2Length(&distVec);

	VECTOR2 pos = VECTOR2(gun.getCenterX(),gun.getCenterY());
	VECTOR2 dir = VECTOR2(target->getCenterX(),target->getCenterY()) - pos;
	D3DXVec2Normalize(&dir,&dir);
	float angle = atan(dir.y/dir.x);
	bool WithinFireAngle =  ((angle <= PI/4 && angle >= -PI/4));
	pos = VECTOR2(gun.getCenterX() - cos(angle)*gun.getWidth()*0.5*gun.getScale(),gun.getCenterY() - sin(angle)*gun.getWidth()*0.5*gun.getScale());

	if(dist < guardNS::FLEE_DIST)				//FLEE
	{
		if((getCenterX()-target->getX()) > 0)
		{
			velocity.x = guardNS::FLEE_SPEED;
			facingDir = right;
		}
		else
		{
			velocity.x = -guardNS::FLEE_SPEED;
			facingDir = left;
		}
		if(getCenterX() >= patrolAnchor + Platformns::WIDTH/2 && WithinFireAngle)
		{
			spriteData.x = patrolAnchor + Platformns::WIDTH/2 - guardNS::WIDTH/2*guardNS::SCALE;
			facingDir = left;
			//gun.setCurrentFrame(2);
			gun.setRadians(angle);
			if(timeSinceShoot >= guardNS::SHOOT_COOLDOWN)
			{
				spawnBullet(pos, dir*bulletNS::SPEED);
				timeSinceShoot = 0;
			}
		}
		else if(getCenterX() <= patrolAnchor - Platformns::WIDTH/2 && WithinFireAngle)
		{
			spriteData.x = patrolAnchor - Platformns::WIDTH/2 - guardNS::WIDTH/2*guardNS::SCALE;
			facingDir = right;
			//gun.setCurrentFrame(1);
			gun.setRadians(angle);
			if(timeSinceShoot >= guardNS::SHOOT_COOLDOWN)
			{
				spawnBullet(pos, dir*bulletNS::SPEED);
				timeSinceShoot = 0;
			}
		}
	}
	else if(dist < guardNS::ATTACK_DIST)		//ATTACK
	{
		velocity.x = 0;
		if(dir.x < 0)
		{
			facingDir = left;
			//gun.setCurrentFrame(2);
			gun.setRadians(angle);
		}
		else
		{
			facingDir = right;
			//gun.setCurrentFrame(1);
			gun.setRadians(angle);
		}
		if(timeSinceShoot >= guardNS::SHOOT_COOLDOWN && WithinFireAngle)
		{
			spawnBullet(pos, dir*bulletNS::SPEED);
			timeSinceShoot = 0;
		}
	}
	else 										//PATROL
	{
		if(patrolDir == left)
		{
			velocity.x = -guardNS::SPEED;
			facingDir = left;
			if(getCenterX() <= patrolAnchor - patrolWidth)
			{
				patrolDir = right;
			}
		}
		else if(patrolDir == right)
		{
			velocity.x = guardNS::SPEED;
			facingDir = right;
			if(getCenterX() >= patrolAnchor + patrolWidth)
			{
				patrolDir = left;
			}
		}
	}

	if(getCenterX() >= patrolAnchor + Platformns::WIDTH/2)
	{
		spriteData.x = patrolAnchor + Platformns::WIDTH/2 - guardNS::WIDTH/2*guardNS::SCALE;
	}
	else if(getCenterX() <= patrolAnchor - Platformns::WIDTH/2)
	{
		spriteData.x = patrolAnchor - Platformns::WIDTH/2 - guardNS::WIDTH/2*guardNS::SCALE;
	}

}