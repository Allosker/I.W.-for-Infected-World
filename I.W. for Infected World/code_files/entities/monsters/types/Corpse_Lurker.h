#pragma once // The Corpse Lurker


#include "entities/monsters/Monster.h"

class Corpse_Lurker
	: public Monster
{
public:


	Corpse_Lurker(const EntityInit& Einit);

	Corpse_Lurker(SharedEntityInit Einit);


	Corpse_Lurker(Corpse_Lurker&&) noexcept = default;

	Corpse_Lurker& operator=(Corpse_Lurker&&) noexcept = default;


	void setTarget(const Vec2f& target) override;

	void retrievePlayerPosition(const Vec2f& pPos) override;

	void update(const Time& dt) noexcept override;


private:



};