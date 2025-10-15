#pragma once // Monster.h


#include "entities/LivingEntity.h"

#include "Utilities/visual_effects/DisplayBar.h"

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

	virtual void retrievePlayerPosition(const Vec2f& pPos) = 0;

	
	float getDamageDealt(float otherDmg, LivingEntity& targetEntity) noexcept;

	float getRandomDamage() const noexcept;



	void damageOnHit(LivingEntity& targetEntity, Vector<Bullet>& bullets);


	void update(const Time& dt) override;

	void updateHiting(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitBullet(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitEntity(Monster& targetEntity) override;


	void draw(RenderTarget& target, RenderStates states) const override;


protected:



	bool updateOffset{ true };

	float randomDamage{ 5 };

	Util::DisplayBar lifebar{ Util::Position::Middle };

	double base_life{};

	Vec2f playerPos{};
};