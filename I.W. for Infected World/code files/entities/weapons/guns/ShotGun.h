#ifndef SHOTGUN_H
#define SHOTGUN_H


#include "entities/weapons/guns/Gun.h"


struct ShotGun
	: public Gun
{
	ShotGun() = delete;

	ShotGun(const GunInit& Ginit);

};
#endif // SHOTGUN_H