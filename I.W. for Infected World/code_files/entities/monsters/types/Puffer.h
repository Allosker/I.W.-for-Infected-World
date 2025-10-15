#pragma once // The Puffer

#include "entities/monsters/Monster.h"

class Puffer
	: public Monster
{
public:


	Puffer(const EntityInit& Einit);

	Puffer(SharedEntityInit Einit);


	Puffer(Puffer&&) noexcept = default;

	Puffer& operator=(Puffer&&) noexcept = default;


	void setTarget(const Vec2f& target) override;

	void retrievePlayerPosition(const Vec2f& pPos) override;

	void update(const Time& dt) noexcept override;



private:



};