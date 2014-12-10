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

void Weaponhud::initWeapons(TextureManager * tm){
	for (int i=0;i<4;i++){
		if(!WeaponImg[i].initialize(graphics,64,64,4,tm))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error init weapon texture"));
		WeaponImg[i].setX(i*60+14);
		WeaponImg[i].setY(0);
	}
	WeaponImg[0].setCurrentFrame(0);
	WeaponImg[1].setCurrentFrame(1);
	WeaponImg[2].setCurrentFrame(3);
	WeaponImg[3].setCurrentFrame(4);
}


void Weaponhud::draw(VECTOR2 cam)
{
	Image::draw();
	for(int i=0;i<4;i++){
		WeaponImg[i].draw();
	}
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

