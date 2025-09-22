#include "ShotGun.h"


ShotGun::ShotGun(const GunInit& Ginit)
	: Entity{Ginit.Einit},
	Gun{Ginit}
{
}
