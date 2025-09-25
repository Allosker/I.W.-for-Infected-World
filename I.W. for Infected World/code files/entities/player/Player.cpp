// ===========================
// Author: Allosker
// --
// File Name: Player.cpp
// --
// Description: This class manages everything a player should have, it redefines its movements alongside its different textures and sounds. This class is derived from two others.
// Note: the class manages the controls through a spelcialized class.
// ===========================



#include "Player.h"

#include "entities/weapons/Weapon.h"


// Namespace allowing use of base values (class' member attributes) without poluting global namespace
// Note: this avoids recompiling every file depending on this class (hence no static constexpr in class declaration)
namespace Player_Default
{
	// Life
	constexpr double Life{ 20 };
	constexpr double MaxLife{ 30 };

	// Damage
	constexpr double Damage{ 1 };
	constexpr double MaxDamage{ 5 };

	// Armor
	constexpr double Armor{ 1 };
	constexpr double MaxArmor{ 20 };

	// Speed
	constexpr float Speed{ 200 };

}



// Class -- Player
/* ----------------------------------------------------------------------------- */


// Constructor



Player::Player(const EntityInit& Einit, const Map& map)
	: LivingEntity{ Einit },
	refMap{map}
{
	// Sets the base values for the player
	using namespace Player_Default;
	using T = Traits;
	using S = Specifier;


	set(T::Life, S::Current, Life);
	set(T::Life, S::Max, MaxLife);

	set(T::Armor, S::Current, Armor);
	set(T::Armor, S::Max, MaxArmor);

	set(T::Damage, S::Current, Damage);
	set(T::Damage, S::Max, MaxDamage);

	setSpeed(Speed);

	threshold = 1.5;
}


// Getters



const Vector<const Tile*> Player::isCollidingBT() const noexcept
{
	Vector<const Tile*> colliders;

	bool inBounds{ true };
	
	Vec2f playerUL{ sprite.getPosition() };
	Vec2f playerUR{ sprite.getPosition().x + sprite.getTexture().getSize().x, sprite.getPosition().y };
	Vec2f playerDL{ sprite.getPosition().x, sprite.getPosition().y + sprite.getTexture().getSize().y };
	Vec2f playerDR{ sprite.getPosition().x + sprite.getTexture().getSize().x, sprite.getPosition().y };

	Array<size_t, 4> ind;

	setBorderReturn(playerUL, inBounds, ind.at(0));

	setBorderReturn(playerUR, inBounds, ind.at(1));

	setBorderReturn(playerDL, inBounds, ind.at(2));

	setBorderReturn(playerDR, inBounds, ind.at(3));


	for (const auto& i : ind)
		if (inBounds && refMap.getCurrentZone().getTileZone().at(i).isaBorder())
			colliders.push_back(&refMap.getCurrentZone().getTileZone().at(i));


	return colliders;
}

int Player::getIndex_ofTile(const Vec2f& pos) const noexcept
{
	if(refMap.currentZoneContains(pos))
	{
		Vec2i temp( pos / refMap.getCurrentZone().getTileTextureSize());
		return temp.x + temp.y * refMap.getTileCount().x;
	}
	else
	{
		return -1;
	}
}


// setters



void Player::setBorderReturn(const Vec2f& plaPos, bool& b, size_t& ind) const noexcept
{
	if (int temp{ getIndex_ofTile(plaPos) }; temp < 0)
		b = false;
	else
		ind = temp;
}

void Player::setTarget(const Vec2f& target)
{
	targetPosition = currentPosition;
	reachedTarget = true;
	positionAvailable = false;

	if (target != currentPosition)
	{
		lastValidPosition = currentPosition;
		targetPosition = { target.x - sprite.getTexture().getSize().x / 2, target.y - sprite.getTexture().getSize().y / 2 };
		reachedTarget = false;
		positionAvailable = true;
	}
}


// Actors



void Player::update(const Time& dt)
{
	using BT = BorderType;

	Vec2f offset{ applySpeedDT(normalizedDirection(), dt) };

	if ((targetPosition - currentPosition).lengthSquared() <= std::pow(threshold, 2))
	{
		reachedTarget = true;
	}

	updatePlayerOnBorders();
	
	if (!reachedTarget)
	{
		sprite.move(offset);
		cThreshold = {std::abs(offset.x) + 3, std::abs(offset.y) + 3};
	}
	currentPosition = sprite.getPosition();


	updateTextures();
	updateSounds();

	// Updates the weapon the player potentially is carrying -> see LivingEntity.h
	updateWeapon(dt);
}

void Player::updatePlayerOnBorders()
{
	// Iterates through the vector of colliders and teleports the player
	// Checks for collisions and doesn't allow the player to go "out of bounds"
	if (auto colliders = isCollidingBT(); colliders.size() > 0)
		for (const auto& collider : colliders)
			for (const auto& i : collider->getBorderArray())
			{
				if(debug_)
					for (size_t i{ 0 }; i != debugVA.getVertexCount(); i++)
					{
						debugVA[i].color = Color::Red;
						/*debugVA[i].position = { 0,0 };*/
					}

				const Vec2f& colliderPos{ collider->getPosition() };

				const Vec2f& colliderPosText{ collider->getPosition().x + collider->getTexture().getSize().x, collider->getPosition().y + collider->getTexture().getSize().y };

				const Vec2f& pPos{ currentPosition };
				const Vec2f& pPosText{ currentPosition.x + getCurrentTexture().getSize().x,  currentPosition.y + getCurrentTexture().getSize().y };


				switch (i)
				{
				case BT::Up:
					if(debug_)
					{
						debugVA[0].position = colliderPos;
						debugVA[1].position = { colliderPosText.x, colliderPos.y };
					}

					if (pPos.y <= colliderPos.y + cThreshold.y &&
						pPos.y >= colliderPos.y )
					{
						teleport({ pPos.x, pPos.y + cThreshold.y });
						reachedTarget = true;
					}
					break;

				case BT::Down:
					if(debug_)
					{
						debugVA[2].position = { colliderPos.x, colliderPosText.y };
						debugVA[3].position = colliderPosText;
					}

					if (pPos.y <= colliderPosText.y  &&
						pPosText.y >= colliderPosText.y - cThreshold.y)
					{
							teleport({ currentPosition.x, currentPosition.y - 0.1f });
							reachedTarget = true;
					}
					break;

				case BT::Left:
					if(debug_)
					{
						debugVA[4].position = colliderPos;
						debugVA[5].position = { colliderPos.x, colliderPosText.y };
					}

					if (pPos.x <= colliderPos.x + cThreshold.x &&
						pPos.x >= colliderPos.x)
					{
						teleport({ currentPosition.x + 0.1f, currentPosition.y });
						reachedTarget = true;
					}
					break;

				case BT::Right:
					if (debug_)
					{
						debugVA[6].position = { colliderPosText.x, colliderPos.y };
						debugVA[7].position = colliderPosText;
					}
					if (pPos.x <= colliderPosText.x &&
						pPosText.x >= colliderPosText.x - cThreshold.x)
					{
						teleport({ currentPosition.x - 0.1f, currentPosition.y });
						reachedTarget = true;
					}
					break;
				}
			}
}

void Player::updateSounds()
{
}

void Player::updateTextures()
{
	// Updates the set of frames to be used
	if(reachedTarget)
	{
		Vec2f diff{ currentPosition - weapon->getTargetPosition() };
		updateOrientationPlayerTextures(diff);
	}
	else
	{
		Vec2f diff{ lastValidPosition - targetPosition };
		updateOrientationPlayerTextures(diff);
	}

		
	// Updates the current animation frame 
	static Clock FrameRate;
	Time timeEllapsed{ FrameRate.getElapsedTime() };
	if (reachedTarget)
	{
		setTexture(getCurrentIndexTextures().x, getCurrentIndexTextures().y, 0);
	}
	else
	{
		if (timeEllapsed.asMilliseconds() >= 100u)
		{
			nextTexture();
			FrameRate.restart();
		}
	}
	
}

void Player::updateOrientationPlayerTextures(const Vec2f& diff)
{
	if (getTextureWrapper().size(0) >= 4)
	{
		if (std::abs(diff.x) > std::abs(diff.y))
		{
			if (diff.x >= 0)
			{
				setTexture(getCurrentIndexTextures().x, 2, getCurrentIndexTextures().z); // Left
			}
			else
			{
				setTexture(getCurrentIndexTextures().x, 3, getCurrentIndexTextures().z); // Right
			}
		}
		else
		{
			if (diff.y >= 0)
			{
				setTexture(getCurrentIndexTextures().x, 0, getCurrentIndexTextures().z); // Up
			}
			else
			{
				setTexture(getCurrentIndexTextures().x, 1, getCurrentIndexTextures().z); // Down
			}
		}
	}
}

void Player::updateHiting()
{
}

void Player::updateHitBullet()
{
}

void Player::updateHitEntity()
{
}


// Rendering



void Player::draw(RenderTarget& target, RenderStates states) const
{
	Entity::draw(target, states);

	target.draw(debugVA);
}