#pragma once
// ===========================
// Author: Allosker
// --
// File Name: Weapon.h
// --
// Description: This class mainly manages a pointer to a moveable entity to which it is attached. It also maanages circle (a literal circle around the entity being pointed to). As well as a range, the range defines where and how hitboxes are managed (a vector with some other attributes).
// Thus, the addition of the circle and a range can be seen as a weapon, plus damage. This weapon class acts as the base class of all guns.
// ===========================


#include "time utils/VisualCoolDown.h"

#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"

#include "umbrella headers/Math.h"


class LivingEntity;


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



class Weapon
	: public MoveableEntity
{
public:
// Constructors & Destructors



	Weapon(const EntityInit& Einit, const LivingEntity& entity);


	Weapon(Weapon&&) noexcept = default;

	Weapon& operator=(Weapon&&) noexcept = default;

	Weapon(Weapon&) = delete;

	Weapon& operator=(Weapon&) = delete;


// Setters



	void setUser(const LivingEntity& newUser);

	void setTarget(const Vec2f& target) override;

	virtual void setShootTarget(const Vec2f& target) noexcept;

	void setCoolDown(unsigned int cd) noexcept;

	void setRecoil(int rec) noexcept;

	Vec2f newPositionCircle() noexcept;


	void setDebug(bool b) noexcept; 

	
// Getters 



	CircleAround& getCircle() noexcept { return circle; }

	const CircleAround& getCircle() const noexcept { return circle; }

	double getDamageDealt(double oDamage) const noexcept;


// Actors



	void update(const Time& dt) override;

	void updateTextures() override;

	void updateWeaponCircle();

	void updateSounds() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


protected:


	double damage{ 1 };

	const LivingEntity* user;

		// Structs -- External managers
		CircleAround circle;

		Vec2f shootTarget;
		Vec2f fireOrigin;

	VisualCoolDown cooldown;
	
	int recoil{ 6 };

	bool animFired{ false };

	bool inverted{ false };

	bool debug{ true };
};