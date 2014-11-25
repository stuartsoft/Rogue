#include "player.h"
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
		setCurrentFrame(1);
	}
	else if(input->isKeyDown(S_KEY))
	{
		inputDir.y = 1;
		setCurrentFrame(0);
	}
	else if(input->isKeyDown(A_KEY))
	{
		inputDir.x = -1;
		setCurrentFrame(2);
	}
	else if(input->isKeyDown(D_KEY))
	{
		inputDir.x = 1;
		setCurrentFrame(3);
	}
	else
	{
		setCurrentFrame(0);
	}
	if(input->isKeyDown(SPACE_KEY))
	{
		inputDir *= .3f;
	}
	inputDir *= playerNS::SPEED*frameTime;
	setVelocity(inputDir);

}

