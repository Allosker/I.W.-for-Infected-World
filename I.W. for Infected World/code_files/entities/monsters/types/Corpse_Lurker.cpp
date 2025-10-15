#include "Corpse_Lurker.h"

Corpse_Lurker::Corpse_Lurker(const EntityInit& Einit)
	: Monster{Einit}
{
}

Corpse_Lurker::Corpse_Lurker(SharedEntityInit Einit)
	: Monster{Einit}
{
}




void Corpse_Lurker::setTarget(const Vec2f& target)
{
}

void Corpse_Lurker::retrievePlayerPosition(const Vec2f& pPos)
{
}


void Corpse_Lurker::update(const Time& dt) noexcept
{
}
