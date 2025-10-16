#pragma once // The Corpse Lurker


#include "entities/monsters/Monster.h"

class Corpse_Lurker
	: public Monster
{
public:


	Corpse_Lurker(const EntityInit& Einit);

	Corpse_Lurker(SharedEntityInit Einit, const sf::FloatRect& mB);


	Corpse_Lurker(Corpse_Lurker&&) noexcept = default;

	Corpse_Lurker& operator=(Corpse_Lurker&&) noexcept = default;



	bool isInActivationCircle(const Vec2f& point) noexcept;


	void teleport(const Vec2f& point) noexcept override;

		 
	void update(const Time& dt) noexcept override;

	void updateTextures() override;



private:


	Clock resTime{};

	Vec2f startingPosition{};

	Vec2f offset{};

	const sf::FloatRect mapBounds;
	
	float radiusActivationCircle{};

	float roamingDistance{}, rushingDistance{};
	
	bool resting{ false }, rushing{ false };


	

};