#include "weapon.h"


Weapon::Weapon(){
	spriteData.width = weaponNS::WIDTH;
	spriteData.height = weaponNS::HEIGHT;
	spriteData.x = weaponNS::X;
	spriteData.y = weaponNS::Y;

	spriteData.rect.bottom = weaponNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = weaponNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	radius = weaponNS::WIDTH/2.0;
	setScale(weaponNS::SCALE);

	edge.top = -weaponNS::HEIGHT/2;
	edge.bottom = weaponNS::HEIGHT/2;
	edge.left = -weaponNS::WIDTH/2;
	edge.right = -weaponNS::WIDTH/2;
	collisionType = entityNS::BOX;
	facingDir = entityNS::direction::none;
}