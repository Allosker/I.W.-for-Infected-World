// ===========================
// Author: Allosker
// --
// File Name: LivingEntity.cpp
// --
// Description: This class manages living traits (e.g. life, damage...), this living traits are what defines an entity that can interact with other entities of the same type.
// If a living Entity's life reaches 0, it ceases to show on screen and is considered dead -- it's whole logic gets blocked and it is erased from memory.
// This class also manages a pointer to weapon that cna be changed, this pointer is necessary because the Entity doesn't own the weapon (the weapon must exist on its own) but it needs it for its internal logic to function.
// ===========================



#include "LivingEntity.h"

#include "entities/weapons/Weapon.h"


// Class -- LivingEntity
/* ----------------------------------------------------------------------------- */


// Constructors & Destructors



LivingEntity::LivingEntity(SharedEntityInit Einit)
	: MoveableEntity(Einit)
{
}

LivingEntity::LivingEntity(const EntityInit& Einit, const LivingTraits& livingTs)
	: MoveableEntity{ Einit },
	livingtraits{ livingTs }
{
}

LivingEntity::LivingEntity(const EntityInit& Einit)
	: MoveableEntity{ Einit }
{
}


// Getters



double LivingEntity::get(Traits trait, Specifier spe) noexcept
{
	using S = Specifier;

	pickCurrentTraits(trait);
	switch (spe)
	{
	case S::Current:
		return *current;
		break;
	case S::Max:
		return *max;
		break;
	case S::Multi:
		return *multi;
		break;
	default:
		return -1;
		break;
	}
}

Weapon* LivingEntity::getWeapon() const noexcept
{
	return weapon;
}

std::int16_t LivingEntity::getNumberWeapons() const noexcept
{
	return numberWeapons;
}

bool LivingEntity::isDead() const noexcept
{
	return dead;
}


// Setters



void LivingEntity::pickCurrentTraits(Traits trait) noexcept
{
	switch (trait)
	{
	case Traits::Life:
		current = &livingtraits.life;
		max = &livingtraits.maxLife;
		multi = &livingtraits.regenMulti;
		break;
	case Traits::Armor:
		current = &livingtraits.armor;
		max = &livingtraits.maxArmor;
		multi = &livingtraits.armordMulti;
		break;
	case Traits::Damage:
		current = &livingtraits.damage;
		max = &livingtraits.maxDamage;
		multi = &livingtraits.damageMulti;
		break;
	}
}
#include <iostream>
void LivingEntity::set(Traits trait, Specifier spe, double newVar) noexcept
{
	using S = Specifier;
		 
	pickCurrentTraits(trait);
	switch(spe)
	{
	case S::Current:
		if (newVar > *max)
		{
			*current = *max;
		}
		else
			*current = newVar;
		break;
	case S::Max:
			*max = newVar;
		break;
	case S::Multi:
		if (newVar <= 1)
			*multi = 1;
		else
			*multi = newVar;
		break;
	}
}

void LivingEntity::add(Traits trait, Specifier spe, double newVar) noexcept
{
	using S = Specifier;

	pickCurrentTraits(trait);
	switch (spe)
	{
	case S::Current:
		if (newVar >= *max)
			*current = *max;
		else
			*current += newVar;
		break;
	case S::Max:
		*max += newVar;
		break;
	case S::Multi:
		*multi += newVar;
		break;
	}
}

void LivingEntity::sub(Traits trait, Specifier spe, double newVar) noexcept
{
	using S = Specifier;

	pickCurrentTraits(trait);
	switch (spe)
	{
	case S::Current:
		if (/**current -*/ newVar <= 0)
			*current = 0;
		else
			*current -= newVar;
		break;
	case S::Max:
		if (newVar <= 0)
			*max = 0;
		else
			*max -= newVar;
		break;
	case S::Multi:
		if (newVar <= 0)
			*multi = 0;
		else
			*multi -= newVar;
		break;
	}
}



void LivingEntity::setWeapon(Weapon* weap)
{
	if (weapon == weap)
		return;

	weapon = weap;
}



// Actors



void LivingEntity::updateWeapon(const Time& dt)
{
	if (weapon && !dead)
		weapon->update(dt);
}