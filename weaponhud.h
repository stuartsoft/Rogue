#ifndef _WEAPONHUD_H
#define _WEAPONHUD_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"
#include "textDX.h"

namespace weaponhudNS{
	const int WIDTH = 280;                   // image width
	const int HEIGHT = 132;                  // image height
	const int X = 0;   // location on screen
	const int Y = -2;

	const int TEXTURE_COL = 2;
	const float SCALE = 1.0f;
}

class Weaponhud: public Entity{
private:
	int currentweapon;
	time_t timesincekeypress;
	time_t tnow;
	Image WeaponImg[4];
	int ammo[4];
	TextDX* ammotext;
public:
	Weaponhud();
	void initWeapons(TextureManager* tm);
	void Weaponhud::draw(VECTOR2 cam);
	void Weaponhud::update(float frameTime);
	int Weaponhud::getCurrentWeapon(){return currentweapon;};
};

#endif