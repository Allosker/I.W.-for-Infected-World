#ifndef HANDGUN_H
#define HANDGUN_H

#include "entities/weapons/guns/Gun.h"


class HandGun
	: public Gun
{
public:


	HandGun() = delete;

	HandGun(const GunInit& Ginit);

};

#endif // HANDGUN_H