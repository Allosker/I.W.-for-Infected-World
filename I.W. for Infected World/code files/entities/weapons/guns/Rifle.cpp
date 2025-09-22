#include "Rifle.h"


Rifle::Rifle(const GunInit& Ginit)
	: Entity{ Ginit.Einit },
	Gun{ Ginit }
{
}