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
	setScale(guardNS::SCALE);

	mass = guardNS::MASS;
	edge.top = -guardNS::HEIGHT/2;
	edge.bottom = guardNS::HEIGHT/2;
	edge.left = -20;
	edge.right = 20;
	collisionType = entityNS::BOX;

	health = guardNS::MAX_HEALTH;
	setFrameDelay(guardNS::FRAME_DELAY);

	facingDir = entityNS::direction::none;
}

void Guard::draw(VECTOR2 cam)
{
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Guard::update(float frameTime)
{
	Entity::update(frameTime);

	
	float vx = velocity.x;
	float vy = velocity.y;
	if(vy < 0 && abs(vx) <= abs(vy))
	{
		if(facingDir != entityNS::direction::up)
		{
			facingDir = entityNS::direction::up;
			setFrames(guardNS::UP_START,guardNS::UP_END);
			setCurrentFrame(guardNS::UP_START+1);
		}
	}
	if(vy > 0 && abs(vx) <= abs(vy))
	{
		if(facingDir != entityNS::direction::down)
		{
			facingDir = entityNS::direction::down;
			setFrames(guardNS::DOWN_START,guardNS::DOWN_END);
			setCurrentFrame(guardNS::DOWN_START+1);
		}
	}
	if(vx < 0 && abs(vy) < abs(vx))
	{
		if(facingDir != entityNS::direction::left)
		{
			facingDir = entityNS::direction::left;
			setFrames(guardNS::LEFT_START,guardNS::LEFT_END);
			setCurrentFrame(guardNS::LEFT_START+1);
		}
	}
	if(vx > 0 && abs(vy) < abs(vx))
	{
		if(facingDir != entityNS::direction::right)
		{
			facingDir = entityNS::direction::right;
			setFrames(guardNS::RIGHT_START,guardNS::RIGHT_END);
			setCurrentFrame(guardNS::RIGHT_START+1);
		}
	}
	if(vx == 0 && vy == 0)
	{
		facingDir = entityNS::direction::down;
		setCurrentFrame(guardNS::DOWN_START);
		setFrames(guardNS::DOWN_START, guardNS::DOWN_START);
	}
		
	incPosition(D3DXVECTOR2(velocity*frameTime));
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();

}

void Guard::ai(bool alert)
{
	VECTOR2 dir(0,0);

	if(alert)
	{
		dir = (*target->getCenter())-(*getCenter());
		D3DXVec2Normalize(&dir,&dir);
		setVelocity(dir*guardNS::SPEED);
	}
	else
	{
		setVelocity(VECTOR2(0,0));
	}
	
}