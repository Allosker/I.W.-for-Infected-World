#include "Monster.h"

#include "entities/weapons/Bullet.h"

#include <iostream>

Monster::Monster(const EntityInit& Einit, const Map& map, Vector<Bullet>& _bullets, const LivingEntity* targetEn)
	: LivingEntity{Einit}, refMap{map}, targetEntity{targetEn}, bullets{_bullets}
{
}


unsigned int Monster::gatherHits()
{
	unsigned int hit{};

	if (targetEntity && targetEntity->getNumberWeapons() && bullets.size() > 0)
	{
		for (auto& bullet : bullets)
		{
			if(contains(bullet.current))
			{
				sub(Traits::Life, Specifier::Current, bullet.damage);
				bullet.reachedTarget = true;
			}
		}
	}

	std::cout << "Life: " << get(Traits::Life, Specifier::Current) << '\n';
	return hit;
}





void Monster::draw(RenderTarget& target, RenderStates states) const
{
	MoveableEntity::draw(target, states);
}

void Monster::setTarget(const Vec2f& target)
{
}

void Monster::update(const Time& dt)
{
}

void Monster::updateHiting()
{
}

void Monster::updateHitBullet()
{
	gatherHits();
}

void Monster::updateHitEntity()
{
}
