#include "HandGun.h"


HandGun::HandGun(const GunInit& Ginit)
	: Entity{ Ginit.Einit },
	Gun{ Ginit }
{
}