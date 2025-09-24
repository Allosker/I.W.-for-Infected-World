#include "Monster.h"




Monster::Monster(const EntityInit& Einit, const Map& map, const LivingEntity* targetEn)
	: LivingEntity{Einit}, refMap{map}, targetEntity{targetEn}
{
}


unsigned int Monster::gatherHits(const Vector<Bullet>& bullets)
{
	unsigned int hit{};

	if (targetEntity && targetEntity->getNumberWeapons() && bullets.size() > 0)
	{
		
	}
	return hit;
}





void Monster::draw(RenderTarget& target, RenderStates states) const
{
	MoveableEntity::draw(target, states);
}
