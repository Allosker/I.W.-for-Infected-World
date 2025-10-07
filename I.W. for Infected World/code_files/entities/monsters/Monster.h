#pragma once // Monster.h


#include "entities/LivingEntity.h"

#include "Utilities/visual_effects/LifeBar.h"

#include "map/Map.h"


class Bullet;


class Monster 
	: public LivingEntity
{
public:


	Monster(const EntityInit& Einit);

	Monster(SharedEntityInit Einit);

	Monster(Monster&&) = default;

	Monster& operator=(Monster&&) = default;



	virtual ~Monster() = default;





	void setTarget(const Vec2f& target) override;

	
	float getDamageDealt(float otherDmg, LivingEntity& targetEntity) noexcept;



	void damageOnHit(LivingEntity& targetEntity, Vector<Bullet>& bullets);


	void update(const Time& dt) override;

	void updateHiting(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitBullet(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitEntity(LivingEntity& targetEntity) override;


	void draw(RenderTarget& target, RenderStates states) const override;


private:



	bool updateOffset{ true };

	Util::LifeBar lifebar{ Util::Position::Middle };
};