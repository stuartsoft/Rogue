#include "player_BOOM.h"
#include <ctime>
#include <chrono>

Player::Player(){
	spriteData.width = playerNS::WIDTH;           // size of Ship1
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = playerNS::WIDTH/2.0;
	setScale(playerNS::SCALE);

	edge.top = -playerNS::HEIGHT/2;
	edge.bottom = playerNS::HEIGHT/2;
	edge.left = -20;
	edge.right = 20;
	collisionType = entityNS::BOX;

	health = playerNS::MAX_HEALTH;

	facingDir = entityNS::direction::none;
}

void Player::draw(VECTOR2 cam)
{
	spriteData.x += cam.x;
	spriteData.y += cam.y;
	Image::draw();              // draw Player
	spriteData.x -= cam.x;
	spriteData.y -= cam.y;
}

void Player::update(float frameTime)
{
	Entity::update(frameTime);

	// INPUT
	D3DXVECTOR2 inputDir(0,0);
	if(input->isKeyDown(W_KEY))
	{
		inputDir.y = -1;
		if(facingDir != entityNS::direction::up && !input->isKeyDown(A_KEY) && !input->isKeyDown(D_KEY))
		{
			facingDir = entityNS::direction::up;
			setFrames(playerNS::UP_START,playerNS::UP_END);
			setCurrentFrame(playerNS::UP_START +1);

		}
	}
	if(input->isKeyDown(S_KEY))
	{
		inputDir.y = 1;
		if(facingDir != entityNS::direction::down  && !input->isKeyDown(A_KEY) && !input->isKeyDown(D_KEY))
		{
			facingDir = entityNS::direction::down;
			setFrames(playerNS::DOWN_START,playerNS::DOWN_END);
			setCurrentFrame(playerNS::DOWN_START +1);
		}
	}
	if(input->isKeyDown(A_KEY))
	{
		inputDir.x = -1;
		if(facingDir != entityNS::direction::left)
		{
			facingDir = entityNS::direction::left;
			setFrames(playerNS::LEFT_START,playerNS::LEFT_END);
			setCurrentFrame(playerNS::LEFT_START +1);
		}
	}
	else if(input->isKeyDown(D_KEY))
	{
		inputDir.x = 1;
		if(facingDir != entityNS::direction::right)
		{
			facingDir = entityNS::direction::right;
			setFrames(playerNS::RIGHT_START,playerNS::RIGHT_END);
			setCurrentFrame(playerNS::RIGHT_START+1);
		}
	}
	if(inputDir.x == 0 && inputDir.y == 0)
	{
		facingDir = entityNS::direction::none;
		setCurrentFrame(playerNS::DOWN_START);
		setFrames(playerNS::DOWN_START, playerNS::DOWN_START);
	}

	D3DXVec2Normalize(&inputDir, &inputDir);

	if(input->isKeyDown(SPACE_KEY))
	{
		inputDir *= playerNS::SPEED/2;
		setFrameDelay(playerNS::FRAME_DELAY/0.3f);
	}
	else
	{
		setFrameDelay(playerNS::FRAME_DELAY);
		inputDir *= playerNS::SPEED;
	}

	setVelocity(inputDir);

	//update position based on velocity changes
	incPosition(D3DXVECTOR2(velocity*frameTime));
	
/*    if (getPositionX() > GAME_WIDTH-getWidth()*getScale()) 
		setPositionX(GAME_WIDTH-getWidth()*getScale()); 
    if (getPositionX() < 0) 
        setPositionX(0);
	if (getPositionY() > GAME_HEIGHT-getHeight()*getScale())
		setPositionY(GAME_HEIGHT-getHeight()*getScale());
	if (getPositionY() < 0)
		setPositionY(0);
*/
	//apply new position
	spriteData.x = getPositionX();
	spriteData.y = getPositionY();
	
}

