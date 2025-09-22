#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H
// ===========================
// Author: Allosker
// --
// File Name: LivingEntity.h
// --
// Description: This class manages living traits (e.g. life, damage...), this living traits are what defines an entity that can interact with other entities of the same type.
// If a living Entity's life reaches 0, it ceases to show on screen and is considered dead -- it's whole logic gets blocked and it is erased from memory.
// This class also manages a pointer to weapon that cna be changed, this pointer is necessary because the Entity doesn't own the weapon (the weapon must exist on its own) but it needs it for its internal logic to function.
// ===========================



#include "entities/weapons/Weapon.h"



// Manages all "living traits" that a Living Entity has (for better readibility and easier access)
// Note: isDead is mutable here to permit any entity to access its members without alternating them and yet let them kill it.
struct LivingTraits
{

	// Life

	double life{ 1 };

	double regenMulti{ 1 };

	double maxLife{ 1 };

	bool isDead{ false };


	// Armor

	double armor{ 1 };

	double armordMulti{ 1 };

	double maxArmor{ 1 };


	// Damage

	double damage{ 1 };

	double damageMulti{ 1 };

	double maxDamage{ 1 };

};



// Those two enums help manage LivingTraits
enum class Traits
{
	Life,
	Armor,
	Damage,
};
enum class Specifier
{
	Current,
	Max,
	Multi,
	Condi,
};



// Living Entity mainly acts as a base class for other living Entities, it may or may not have a gun.
// This class can only check if it is being hit by a hitbox or another living entity -> see Weapon.h
class LivingEntity 
{
public:
// Constructors & Destructors



	LivingEntity() = default;

	LivingEntity(const LivingTraits& livingTs);

	LivingEntity(LivingEntity&&) noexcept = default;

	LivingEntity& operator=(LivingEntity&&) noexcept = default;

	LivingEntity(LivingEntity&) = delete;

	LivingEntity& operator=(LivingEntity&) = delete;


	virtual ~LivingEntity() = default;


// Getters



	double get(Traits trait, Specifier spe) noexcept;

	Weapon* getWeapon() const noexcept;



// Setters


	void pickCurrentTraits(Traits trait) noexcept;

	void set(Traits trait, Specifier spe, double newVar=0) noexcept;

	void add(Traits trait, Specifier spe, double newVar) noexcept;

	void sub(Traits trait, Specifier spe, double newVar) noexcept;


	void setWeapon(Weapon& weap);

	
	void die() noexcept { livingtraits.isDead = true; }


// Actors



	virtual void updateWeapon(const DeltaTime& dt);

	virtual void updateHiting() = 0;

	virtual void updateHitHitbox() = 0;

	virtual void updateHitEntity() = 0;


protected:


		// Living Traits
		LivingTraits livingtraits{};

		double* current{ &livingtraits.life };

		double* max{ &livingtraits.maxLife };

		double* multi{ &livingtraits.regenMulti };

		bool& condi{ livingtraits.isDead };


	bool getsHitbyHitbox{ true };

	bool getsHitbyEntities{ true };


	Weapon* weapon{ nullptr };

};


#endif // LIVINGENTITY_H

