#include "Monster.h"




Monster::Monster(const EntityInit& Einit, const Map& map, const LivingEntity* targetEn)
	: Entity{Einit}, MoveableEntity{Einit}, refMap{map}, targetEntity{targetEn}
{
}


unsigned int Monster::gatherHits()
{
	unsigned int hit{};

	if (targetEntity && targetEntity->getWeapon() && targetEntity->getWeapon()->getRange().getHitboxes().size() > 0)
	{
		for (const auto& i : targetEntity->getWeapon()->getRange().getHitboxes())
			for (const auto& j : i)
				if (sprite.getGlobalBounds().contains(j.position))
				{
					j.markReached();
					hit += 1;
				}
	}
	return hit;
}





void Monster::draw(RenderTarget& target, RenderStates states) const
{
	MoveableEntity::draw(target, states);
}
