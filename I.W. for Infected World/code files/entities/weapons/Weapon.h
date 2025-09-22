#ifndef WEAPON_H
#define WEAPON_H
// ===========================
// Author: Allosker
// --
// File Name: Weapon.h
// --
// Description: This class mainly manages a pointer to a moveable entity to which it is attached. It also maanages circle (a literal circle around the entity being pointed to). As well as a range, the range defines where and how hitboxes are managed (a vector with some other attributes).
// Thus, the addition of the circle and a range can be seen as a weapon, plus damage. This weapon class acts as the base class of all guns.
// ===========================


#include "entities/MoveableEntity.h"


#include <cmath>
#include <numbers>


#include "memory Utils/random.h"

#include "time utils/VisualCoolDown.h"



// Small class defining a set of positions circled around a specified target for the weapon to rotate on it
struct CircleAround
{
	CircleAround(const Vec2f& positionO, float distFromO);

	CircleAround(CircleAround&&) = default;


// Setters

	void setRadius(float newDist);


// Calculations

	void calculatePerimeter();


// Members

	float radius{};

	Vec2f posO{};

	Vector<Vec2f> circle{};

};



// Weapon manages a range (that manages hitboxes), a weapon is an moveable entity that attaches itself to another moveable entity but does not manage it (hence the pointer to MoveableEntity).
class Weapon
	: public MoveableEntity
{
public:
// Constructors & Destructors



	Weapon(const EntityInit& Einit, const MoveableEntity& entity);


	Weapon(Weapon&&) noexcept = default;

	Weapon& operator=(Weapon&&) noexcept = default;

	Weapon(Weapon&) = delete;

	Weapon& operator=(Weapon&) = delete;


// Setters



	void setUser(const MoveableEntity& newUser);

	void setTarget(const Vec2f& target) override;

	void setShootTarget(const Vec2f& target) noexcept;

	void setCoolDown(unsigned int cd) noexcept;

	void setRecoil(int rec) noexcept;

	Vec2f newPositionCircle() noexcept;


	void setDebug(bool b) noexcept; 

	
// Getters 



	CircleAround& getCircle() noexcept { return circle; }

	const CircleAround& getCircle() const noexcept { return circle; }

	const Range& getRange() const noexcept { return range; }

	Range& getRange() noexcept { return range; }
	
	double getDamageDealt(double oDamage) const noexcept;

	const Vector<Vector<Hitbox>>& getHitboxes() const noexcept { return range.hitboxes; }


// Actors



	void update(const DeltaTime& dt) override;

	void updateTextures() override;

	void updateWeaponCircle();

	void updateSounds() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


protected:


	double damage{ 1 };

	const MoveableEntity* user;

		// Structs -- External managers
		CircleAround circle;

		Range range;

	VisualCoolDown cooldown;
	
	int recoil{ 6 };

	bool animFired{ false };

	bool inverted{ false };

	bool debug{ true };
};


#endif // WEAPON_H