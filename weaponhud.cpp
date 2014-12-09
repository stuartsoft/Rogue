#include "Weaponhud.h"
#include <ctime>
#include <chrono>

Weaponhud::Weaponhud(){
	spriteData.width = weaponhudNS::WIDTH;           // size of Ship1
	spriteData.height = weaponhudNS::HEIGHT;
	spriteData.x = weaponhudNS::X;                   // location on screen
	spriteData.y = weaponhudNS::Y;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	setScale(weaponhudNS::SCALE);
	time(&timesincekeypress);
}

void Weaponhud::draw(VECTOR2 cam)
{
	Image::draw();              // draw Player
}

void Weaponhud::update(float frameTime)
{
	Entity::update(frameTime);
	time_t tnow;
	time(&tnow);

	if(input->isKeyDown('1')){
		setCurrentFrame(1);
		time(&timesincekeypress);
	}
	else if(input->isKeyDown('2')){
		setCurrentFrame(2);
		time(&timesincekeypress);
	}
	else if (input->isKeyDown('3')){
		setCurrentFrame(3);
		time(&timesincekeypress);
	}
	else if (input->isKeyDown('4')){
		setCurrentFrame(4);
		time(&timesincekeypress);
	}
	else if (difftime(tnow, timesincekeypress)>2.0f){
		setCurrentFrame(0);
	}

}

