#include "Puffer.h"



Puffer::Puffer(const EntityInit& Einit)
	: Monster{Einit} 
{
}

Puffer::Puffer(SharedEntityInit Einit)
	: Monster{ Einit }
{
}




void Puffer::setTarget(const Vec2f& target)
{
}


void Puffer::update(const Time& dt) noexcept
{
}
