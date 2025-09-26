#pragma once // Monster.h


#include "entities/LivingEntity.h"

#include "map/Map.h"


class Bullet;


class Monster 
	: public LivingEntity
{
public:


	Monster(const EntityInit& Einit, const Map& map, Vector<Bullet>& _bullets, const LivingEntity* targetEn = nullptr);


	virtual ~Monster() = default;



	unsigned int gatherHits();


	void draw(RenderTarget& target, RenderStates states) const override;
	
	void setTarget(const Vec2f& target) override;

	void update(const Time& dt) override;

	void updateHiting() override;

	void updateHitBullet() override;

	void updateHitEntity() override;

	

private:


	const LivingEntity* targetEntity;

	const Map& refMap;

	Vector<Bullet>& bullets;
};