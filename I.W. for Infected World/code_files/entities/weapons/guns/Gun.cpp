#include "Gun.h"

#include "memory Utils/random.h"

#include "entities/weapons/Bullet.h"


Gun::Gun(const GunInit& Ginit)
	: Weapon{Ginit.Einit, Ginit.lv},
	bullets{Ginit.refManager}
{
	damage = Ginit.damage;
	precision = Ginit.precision;
	nbBullets = Ginit.nbBullets;
	velocity = Ginit.velocityBullets;

	cooldown.setCoolDown(Ginit.cooldown);
	setRecoil(Ginit.recoil);
}



void Gun::randomize(Bullet& bullet, size_t nbBllts) noexcept
{
	Vec2f delta{ shootTarget - fireOrigin };

	Vec2f newTarget{ shootTarget };


	float randRange{ std::abs(delta.x)  + std::abs(delta.y) };

	float randomNb{};

	if (randRange > 0)
		randomNb = Util::random_number(-randRange, randRange) / precision;


	if (Util::random_number(0, 1))
		newTarget.x += randomNb * 1.5;
	else
		newTarget.y += randomNb * 1.5;


	bullet.target = newTarget;
}

void Gun::initializeBullets() noexcept
{
	for (int i{ 0 }; i != nbBullets; i++)
	{
		Bullet tempB;

		tempB.current = fireOrigin;
		tempB.origin = fireOrigin;

		tempB.velocity = velocity;
		tempB.damage = Util::random_number<double>(damage.first, damage.second);
		tempB.threshold = threshold;

		tempB.debug = debug_;
		

		randomize(tempB, nbBullets);

		bullets.push_back(std::move(tempB));
	}
}

void Gun::setShootTarget(const Vec2f& target) noexcept
{
	if (cooldown.isFinished())
	{
		shootTarget = target;
		fireOrigin = currentPosition;
		initializeBullets();
		animFired = true;
		cooldown.start();
	}
}
