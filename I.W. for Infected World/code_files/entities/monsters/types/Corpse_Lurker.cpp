#include "Corpse_Lurker.h"

Corpse_Lurker::Corpse_Lurker(const EntityInit& Einit)
	: Monster{Einit}, mapBounds{}
{
}

Corpse_Lurker::Corpse_Lurker(SharedEntityInit Einit, const sf::FloatRect& mB)
	: Monster{Einit}, mapBounds{mB}
{
	reachedTarget = true;

	using T = Traits;
	using S = Specifier;


	set(T::Life, S::Max, -1);
	set(T::Damage, S::Max, -1);

	base_life = Util::random_number<double>(50, 90);

	set(T::Life, S::Current, base_life);

	set(T::Damage, S::Current, Util::random_number<double>(3, 10));

	setSpeed(Util::random_number<float>(40, 45));


	roamingDistance = 400;
	rushingDistance = 300;

	radiusActivationCircle = 100;
}




bool Corpse_Lurker::isInActivationCircle(const Vec2f& point) noexcept
{
	float dx{ point.x - currentPosition.x }, dy{ point.y - currentPosition.y };

	return dx * dx + dy * dy < radiusActivationCircle * radiusActivationCircle;
}

void Corpse_Lurker::teleport(const Vec2f& point) noexcept
{
	currentPosition = point;
	sprite.setPosition(point);

	startingPosition = point;
}


void Corpse_Lurker::update(const Time& dt) noexcept 
{
	if (!rushing && !isInActivationCircle(playerPos) )
	{

		if (resting && resTime.getElapsedTime().asSeconds() >= 2)
		{
			resting = false;
		}


		if(reachedTarget && !resting)
		{
			Vec2f ranPos{ Util::random_point<float>(startingPosition - roamingDistance, startingPosition + roamingDistance) };
			while (!mapBounds.contains(ranPos) || !mapBounds.contains(ranPos + Util::vec2_cast<float>(getCurrentTexture().getSize())))
			{
				ranPos = Util::random_point<float>(startingPosition - roamingDistance, startingPosition + roamingDistance);
			}
			setTarget(ranPos);
			
			reachedTarget = false;
		}

		
		if (!resting && (targetPosition - currentPosition).lengthSquared() <= threshold * threshold)
		{
			reachedTarget = true;
			resting = true;
			resTime.restart();
		}


		offset = applySpeedDT(normalizedDirection(), dt);

	}
	else
	{


		if (rushing == false)
		{
			startingPosition = currentPosition;
			setSpeed(velo.speed * 2);

			rushing = true;
			setTarget(playerPos);
			offset = applySpeedDT(normalizedDirection(), dt);
		}


		if ((currentPosition - startingPosition).length() >= rushingDistance || !mapBounds.contains(currentPosition) || !mapBounds.contains(currentPosition + Util::vec2_cast<float>(getCurrentTexture().getSize())) )
		{
			rushing = false;
			reachedTarget = true;
			setSpeed(velo.speed / 2);
			startingPosition = currentPosition;
		}


	}

	currentPosition += offset;

	sprite.setPosition(currentPosition);

	updateTextures();

}

void Corpse_Lurker::updateTextures()
{
	if (frameRate.getElapsedTime().asMilliseconds() >= 100u)
	{
		nextTexture();
		frameRate.restart();
	}
}
