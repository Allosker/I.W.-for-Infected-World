#include "Gun.h"




Gun::Gun(const GunInit& Ginit)
	: Entity{ Ginit.Einit },
	Weapon{Ginit.Einit, Ginit.mv}
{
	damage = Ginit.damage;
	range.randomizer = Ginit.randomizer;
	range.maxDistance = Ginit.range;
	range.nbHitboxes = Ginit.nbBullets;
	range.velocity = Ginit.velocityBullets;

	cooldown.setCoolDown(Ginit.cooldown);
	setRecoil(Ginit.recoil);
}
