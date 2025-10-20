#include "Puffer.h"



Puffer::Puffer(const EntityInit& Einit)
	: Monster{Einit} 
{
}

Puffer::Puffer(SharedEntityInit Einit, const Vec2f& a, const Vec2f& b)
	: Monster{ Einit }
{
	using T = Traits;
	using S = Specifier;


	set(T::Life, S::Max, -1);
	set(T::Damage, S::Max, -1);

	base_life = Util::random_number<double>(12, 20);

	set(T::Life, S::Current, base_life);

	set(T::Damage, S::Current, Util::random_number<double>(32, 38));

	setSpeed(Util::random_number<float>(20, 30));

	oldtarget = Util::random_point(a, b);

}



void Puffer::setTarget(const Vec2f& target) noexcept
{
	targetPosition = oldtarget;
	oldtarget = target;
}


void Puffer::isInExplodingCircle() const noexcept
{
}

void Puffer::update(const Time& dt) noexcept
{
	if (dead)
		return;


	if (!moving)
	{
		setTarget(playerPos);

		offset = applySpeedDT(normalizedDirection(), dt);

		moving = true;
	}

	if ((targetPosition - currentPosition).lengthSquared() <= threshold * threshold)
	{
		moving = false;
	}

	currentPosition += offset;

	sprite.setPosition(currentPosition);

	updateTextures();
}



void Puffer::updateTextures()
{
	if (frameRate.getElapsedTime().asMilliseconds() >= 100u)
	{
		nextTexture();
		frameRate.restart();
	}
}


float Puffer::getDamage() noexcept
{
	die();
	return get(Traits::Damage, Specifier::Current);
}
