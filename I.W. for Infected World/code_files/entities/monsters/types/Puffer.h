#pragma once // The Puffer

#include "entities/monsters/Monster.h"

class Puffer
	: public Monster
{
public:


	Puffer(const EntityInit& Einit);

	Puffer(SharedEntityInit Einit, const Vec2f& a, const Vec2f& b);

	Puffer(Puffer&&) noexcept = default;

	Puffer& operator=(Puffer&&) noexcept = default;



	void setTarget(const Vec2f& target) noexcept override;


	void isInExplodingCircle() const noexcept;

	void update(const Time& dt) noexcept override;

	void updateTextures() override;


	float getDamage() noexcept override;


private:


	Vec2f offset{};

	Vec2f oldtarget{};

	bool moving{ false };

};