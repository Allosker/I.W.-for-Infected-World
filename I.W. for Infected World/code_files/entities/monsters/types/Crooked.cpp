#include "Crooked.h"



Crooked::Crooked(const EntityInit& Einit)
	: Monster{Einit}
{
}

Crooked::Crooked(SharedEntityInit Einit)
	: Monster{Einit}
{
	using T = Traits;
	using S = Specifier;


	set(T::Life, S::Max, -1);
	set(T::Damage, S::Max, -1);

	base_life = Util::random_number<double>(30, 60);

	set(T::Life, S::Current, base_life);

	set(T::Damage, S::Current, Util::random_number<double>(3, 4));

	setSpeed(Util::random_number<float>(20, 42));
} 




void Crooked::setTarget(const Vec2f& target)
{
	targetPosition = Util::random_point(target - threshold, target + threshold);
}


void Crooked::update(const Time& dt) noexcept
{
	// Running Phase
	if (resting == false && phaseTime.getElapsedTime().asSeconds() >= 10)
	{
		resting = true;
		setSpeed(velo.speed / 4);
		phaseTime.restart();
	}

	// Resting Phase
	if (resting == true && phaseTime.getElapsedTime().asSeconds() >= 4)
	{
		resting = false;
		setSpeed(velo.speed * 4);
		phaseTime.restart();
	}

		setTarget(playerPos);

		Vec2f offset{ applySpeedDT(normalizedDirection(), dt) };

		currentPosition += offset;

		sprite.setPosition(currentPosition);

	updateTextures();
}


void Crooked::updateTextures()
{
	if (resting)
		/*currentIndexT.y = 1;*/ { }
	else
		currentIndexT.y = 0;

	if (frameRate.getElapsedTime().asMilliseconds() >= 100u)
	{
		nextTexture();
		frameRate.restart();
	}
}