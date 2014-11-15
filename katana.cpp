#include "katana.h"


Katana::Katana() : Entity()
{
	spriteData.width = katanaNS::WIDTH;           // size of Ship1
	spriteData.height = katanaNS::HEIGHT;
	spriteData.rect.bottom = katanaNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = katanaNS::WIDTH;
	spriteData.scale = katanaNS::SCALE;

	spriteData.x = 0;
	spriteData.y = 0;

	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = (katanaNS::WIDTH + katanaNS::HEIGHT)/4.0;

	edge.top = -katanaNS::HEIGHT/2;
	edge.bottom = katanaNS::HEIGHT/2;
	edge.left = 0;
	edge.right = katanaNS::WIDTH/2;

	collisionType = entityNS::ROTATED_BOX;
	active = false;

	edge.top = -katanaNS::HEIGHT/2;
	edge.bottom = katanaNS::HEIGHT/2;
	edge.left = -katanaNS::WIDTH/2;
	edge.right = 0;

	player = nullptr;
	swingAngle = 0;
	timeSinceSwing = 0;
}


void Katana::update(float frameTime)
{
	Entity::update(frameTime);
	timeSinceSwing += frameTime;
	if(!active && timeSinceSwing >= KATANA_COOLDOWN && input->getMouseLButton())
	{
		audio->playCue("Swoosh");
		setActive(true);
		swingAngle = katanaNS::SWING_START;
		setDegrees(swingAngle);
		timeSinceSwing = 0;
	}
	if(active)
	{
		swingAngle += frameTime*katanaNS::ROTATION_RATE;
		if(player->FacingDir() == right)
		{
			setCurrentFrame(0);
			setX(player->getCenterX()-5+player->getScale()*Playerns::WIDTH/4-katanaNS::WIDTH*katanaNS::SCALE/2);
			setY(player->getCenterY()+player->getfloatoffset());
			setDegrees(swingAngle);
			if(getDegrees() >= katanaNS::SWING_END)
			{
				setActive(false);
			}
			edge.top = -katanaNS::HEIGHT/2;
			edge.bottom = katanaNS::HEIGHT/2;
			edge.left = 0;
			edge.right = katanaNS::WIDTH/2;
		}
		if(player->FacingDir() == left)
		{
			setCurrentFrame(1);
			setX(player->getCenterX()+5-player->getScale()*Playerns::WIDTH/4-katanaNS::WIDTH*katanaNS::SCALE/2);
			setY(player->getCenterY()+player->getfloatoffset());
			setDegrees(-swingAngle);
			if(getDegrees() <= -katanaNS::SWING_END)
			{
				setActive(false);
			}
			edge.top = -katanaNS::HEIGHT/2;
			edge.bottom = katanaNS::HEIGHT/2;
			edge.left = -katanaNS::WIDTH/2;
			edge.right = 0;
		}
	}
	
}