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
	edge.left = -playerNS::WIDTH/2;
	edge.right = playerNS::WIDTH/2;
	collisionType = entityNS::BOX;

	health = playerNS::MAX_HEALTH;

	facingDir = none;
}

void Player::draw()
{
	Image::draw();              // draw Player
}

void Player::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += velocity.x;
	spriteData.y += velocity.y;


	// INPUT
	D3DXVECTOR2 inputDir(0,0);
	if(input->isKeyDown(W_KEY))
	{
		inputDir.y = -1;
		if(facingDir != up && !input->isKeyDown(A_KEY) && !input->isKeyDown(D_KEY))
		{
			facingDir = up;
			setFrames(playerNS::UP_START,playerNS::UP_END);
			setCurrentFrame(playerNS::UP_START +1);
		}
	}
	if(input->isKeyDown(S_KEY))
	{
		inputDir.y = 1;
		if(facingDir != down  && !input->isKeyDown(A_KEY) && !input->isKeyDown(D_KEY))
		{
			facingDir = down;
			setFrames(playerNS::DOWN_START,playerNS::DOWN_END);
			setCurrentFrame(playerNS::DOWN_START +1);
		}
	}
	if(input->isKeyDown(A_KEY))
	{
		inputDir.x = -1;
		if(facingDir != left)
		{
			facingDir = left;
			setFrames(playerNS::LEFT_START,playerNS::LEFT_END);
			setCurrentFrame(playerNS::LEFT_START +1);
		}
	}
	else if(input->isKeyDown(D_KEY))
	{
		inputDir.x = 1;
		if(facingDir != right)
		{
			facingDir = right;
			setFrames(playerNS::RIGHT_START,playerNS::RIGHT_END);
			setCurrentFrame(playerNS::RIGHT_START+1);
		}
	}
	if(inputDir.x == 0 && inputDir.y == 0)
	{
		facingDir = none;
		setCurrentFrame(playerNS::DOWN_START);
	}
	if(input->isKeyDown(SPACE_KEY))
	{
		inputDir *= .3f;
		setFrameDelay(playerNS::FRAME_DELAY/0.3f);
	}
	else
		setFrameDelay(playerNS::FRAME_DELAY);
	inputDir *= playerNS::SPEED*frameTime;

	D3DXVec2Normalize(&inputDir, &inputDir);
	setVelocity(inputDir);

}

