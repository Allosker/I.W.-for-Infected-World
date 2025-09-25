#include "Bullet.h"

#include "entities/weapons/guns/Gun.h"


Bullet::Bullet(const Gun& _gun) noexcept
	: gun{&_gun}
{
}

void Bullet::update(const Time& dt) noexcept
{
	if (!reachedTarget)
	{
		current += getOffset(target, origin, gun->velocity) * dt.asSeconds();

		if ((target - current).lengthSquared() <= gun->threshold * gun->threshold)
			reachedTarget = true;
	}
}


// Rendering

void Bullet::draw(RenderTarget& target, RenderStates states) const
{
	if (debug)
	{
		VertexArray va{ sf::PrimitiveType::Lines, 2 };

		va[0].position = origin;
		va[1].position = current;

		target.draw(va);
	}
}
