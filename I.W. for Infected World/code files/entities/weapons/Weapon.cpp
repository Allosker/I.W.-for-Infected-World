// ===========================
// Author: Allosker
// --
// File Name: Weapon.cpp
// --
// Description: This class mainly manages a pointer to a moveable entity to which it is attached. It also maanages circle (a literal circle around the entity being pointed to). As well as a range, the range defines where and how hitboxes are managed (a vector with some other attributes).
// Thus, the addition of the circle and a range can be seen as a weapon, plus damage. This weapon class acts as the base class of all guns.
// ===========================



#include "Weapon.h"




//  Struct -- CircleAround
// -----------------------------------------------------------------


// Constructors & Destructors



CircleAround::CircleAround(const Vec2f& positionO, float distFromO)
	: posO{positionO}, radius{distFromO}
{
	circle.resize(360);
}


// Setters


void CircleAround::setRadius(float newDist)
{
	radius = newDist;
}


// Calculations



void CircleAround::calculatePerimeter()
{
	// Calculates the perimeter of the circle based on the number of points
	for (int i = 0; i != circle.size(); i++)
	{
		double theta{ i * (std::numbers::pi / 180) };

		circle.at(i).x = posO.x + radius * std::cos(theta);

		circle.at(i).y = posO.y + radius * std::sin(theta);
	}
}




//  Class - Weapon
// -----------------------------------------------------------------




// Constructors & Destructors 

Weapon::Weapon(const EntityInit& Einit, const LivingEntity& entity)
	: MoveableEntity{ Einit },
	user{&entity},
	cooldown{entity},
	circle{ {std::move(newPositionCircle())}, static_cast<float>((user->getSprite().getTexture().getSize().x > user->getSprite().getTexture().getSize().y ? user->getSprite().getTexture().getSize().x / 2  : user->getSprite().getTexture().getSize().y / 2))}
{
}




// Setters



void Weapon::setUser(const LivingEntity& newUser)
{
	user = &newUser;
}

void Weapon::setTarget(const Vec2f& target)
{
	targetPosition = target;
}

void Weapon::setShootTarget(const Vec2f& target) noexcept
{
	if(cooldown.isFinished())
	{
		shootTarget = target;
		animFired = true; 
		cooldown.start();
	}
}

void Weapon::setCoolDown(unsigned int cd) noexcept
{
	cooldown.setCoolDown(cd);
}
void Weapon::setRecoil(int rec) noexcept
{
	recoil = rec;
}

Vec2f Weapon::newPositionCircle() noexcept
{
	// Places the circle (around which the weapon will rotate) to give the illusion that it goes in front of and behind the player
	return { user->getCurrentPosition().x + user->getSprite().getTexture().getSize().x / 2, user->getCurrentPosition().y + user->getSprite().getTexture().getSize().y / 4 };
}

void Weapon::setDebug(bool b) noexcept
{
	debug = b;
}


// Getters 



double Weapon::getDamageDealt(double oDamage) const noexcept
{
	return damage + oDamage;
}


// Actors



void Weapon::update(const Time& dt)
{
	cooldown.update();
	
	updateTextures();
	updateSounds();
}

void Weapon::updateTextures()
{
	if (!animFired)
	{
		teleport(user->getCurrentPosition());
		updateWeaponCircle();
	}
	else
	{
		static bool b{ true };

		static Clock timer;

		if (b)
		{
			timer.restart();
			setTexture(getCurrentIndexTextures().x, 1);
		}

		int elasped{ timer.getElapsedTime().asMilliseconds() };

		if (elasped < 60)
		{
			setTexture(getCurrentIndexTextures().x, getCurrentIndexTextures().y, 0);
		}
		else 
		if (elasped < 100)
		{
			setTexture(getCurrentIndexTextures().x, getCurrentIndexTextures().y, 1);
		}
		else 
		if (elasped < 140)
		{
			if(inverted)
				teleport({ getCurrentPosition().x + recoil, getCurrentPosition().y });
			else
				teleport({ getCurrentPosition().x - recoil, getCurrentPosition().y });

			setTexture(getCurrentIndexTextures().x, getCurrentIndexTextures().y, 2);
		}

		b = false;

		if (elasped >= 140)
		{
			setTexture(getCurrentIndexTextures().x, 0, 0);

			b = true;
			animFired = false;
		}

	}
}

void Weapon::updateWeaponCircle()
{
	// Adjusts the position of the circle based on the new player's position
	circle.posO = newPositionCircle();
	circle.calculatePerimeter();

	Vec2f newVec{ targetPosition - user->getCurrentPositionTextures() };

	// Calculate the angle between vector and x-axis taking into account all four quadrants
	double angle = std::atan2(newVec.y, newVec.x) * 180 / std::numbers::pi;
	double oppositeAngle{ std::fmod(angle + 180, 360) };

	if (angle < 0)
		angle += 360;

	if (angle >= 360)
		angle = 359;

			static Vec2f ori {getOrigin()};

	if (angle > 90 && angle < 270)
	{
		sprite.setRotation(sf::degrees(oppositeAngle));

		sprite.setScale({-1, 1});
		inverted = true;
	}
	else
	{
		sprite.setRotation(sf::degrees(angle));

		sprite.setScale({ 1, 1 });
		inverted = false;
	}

	// Teleports the weapon on one of the 360 points of the circle to make it seem like it is rotating
	teleport(circle.circle.at(angle));
}

void Weapon::updateSounds()
{
	// TODO: do the sound logic
}


void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	MoveableEntity::draw(target, states);

	target.draw(cooldown);
}