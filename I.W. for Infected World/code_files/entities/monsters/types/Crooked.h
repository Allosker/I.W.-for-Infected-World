#pragma once // The Crooked One

#include "entities/monsters/Monster.h"

class Crooked
	: public Monster
{
public:


	Crooked(const EntityInit& Einit);

	Crooked(SharedEntityInit Einit);


	Crooked(Crooked&&) noexcept = default;

	Crooked& operator=(Crooked&&) noexcept = default;



	void setTarget(const Vec2f& target) override;

	void update(const Time& dt) noexcept override;
	
	void updateTextures() override;


private:


	Vec2f threshold{ 30, 40 };

	bool resting{ false };

	Clock phaseTime;

};