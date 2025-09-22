#include "Range.h"



// Struct: Bullet
// --------------------------------------------



void Bullet::update(const DeltaTime& dt, float threshold, float maxDist) noexcept
{
	if (!reachedTarget)
	{
		float delta{ dt.getEllapsedTime().asSeconds() };

		if (delta <= 0.1)
			delta = 0.1;

		current += getOffset(target, origin, velocity) * delta;

		if ((target - current).lengthSquared() <= threshold * threshold
			|| (target - current).length() >= maxDist)
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




// Class: Range
// --------------------------------------------



void Range::update(const DeltaTime& dt)
{
	for (auto& bullet : bullets)
	{
		bullet.update(dt, threshold, maxDist);
	}

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& bull) {return bull.reachedTarget; }), bullets.end());
}
