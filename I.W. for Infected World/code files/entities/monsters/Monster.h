#ifndef MONSTER_H
#define MONSTER_H

#include "entities/Entity.h"
#include "entities/MoveableEntity.h"
#include "entities/LivingEntity.h"

#include "map/Map.h"

#include "entities/player/Player.h"


class Monster 
	: public LivingEntity
{
public:


	Monster(const EntityInit& Einit, const Map& map, const LivingEntity* targetEn = nullptr);


	virtual ~Monster() = default;



	unsigned int gatherHits(const Vector<Bullet>& bullets);


	void draw(RenderTarget& target, RenderStates states) const override;


private:


	const LivingEntity* targetEntity;

	const Map& refMap;


};
#endif // MONSTER_H