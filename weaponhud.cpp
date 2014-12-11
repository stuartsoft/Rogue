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
	currentweapon = 0;
	ammo[0] = 1;
	ammo[1] = 2;
	ammo[2] = 3;
	ammo[3] = 4;
	ammotext = new TextDX;
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
	if(!ammotext->initialize(graphics, 52, true, false, "consolas"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font"));
	ammotext->setFontColor(graphicsNS::WHITE);
}


void Weaponhud::draw(VECTOR2 cam)
{
	Image::draw();
	for(int i=0;i<4;i++){
		WeaponImg[i].draw();
	}
	if(getCurrentFrame()!=0){
		std::string ammostr = std::to_string(ammo[currentweapon]);
		ammostr+="x";
		ammotext->print(ammostr,12+currentweapon*60,68);
	}
}

void Weaponhud::update(float frameTime)
{
	Entity::update(frameTime);
	time(&tnow);

	if(input->isKeyDown('1')){
		setCurrentFrame(1);
		currentweapon = 0;
		time(&timesincekeypress);
	}
	else if(input->isKeyDown('2')){
		setCurrentFrame(2);
		currentweapon = 1;
		time(&timesincekeypress);
	}
	else if (input->isKeyDown('3')){
		setCurrentFrame(3);
		currentweapon = 2;
		time(&timesincekeypress);
	}
	else if (input->isKeyDown('4')){
		setCurrentFrame(4);
		currentweapon = 3;
		time(&timesincekeypress);
	}
	else if (input->getMouseWheelDelta()!=0){
		if (input->getMouseWheelDelta()>0)
			currentweapon--;
		else if (input->getMouseWheelDelta() <0)
			currentweapon++;

		if(currentweapon<0)
			currentweapon=3;
		else if (currentweapon>3)
			currentweapon=0;

		setCurrentFrame(currentweapon+1);
		
		input->clearMouseWheelDelta();
		time(&timesincekeypress);
	}
	else if (difftime(tnow, timesincekeypress)>2.0f){
		setCurrentFrame(0);
	}

}