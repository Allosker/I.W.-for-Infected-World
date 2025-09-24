#ifndef BULLET_H
#define BULLET_H


#include <cmath>
#include <numbers>

#include "entities/weapons/guns/Gun.h"

#include "memory Utils/random.h"

#include "time utils/VisualCoolDown.h"


static inline Vec2f getOffset(const Vec2f& target, const Vec2f& origin, float velocity)
{
	Vec2f offset{ target - origin };
	offset /= offset.length();
	offset *= velocity;

	return offset;
}


struct Bullet
	: public sf::Drawable
{
	Bullet() = default;

	Bullet(const Gun& _gun) noexcept; 

	Bullet(Bullet&&) noexcept = default;

	Bullet& operator=(const Bullet&) = default; 

// Actors


	void update(const Time& dt) noexcept;

	// Rendering
	void draw(RenderTarget& target, RenderStates states) const override;
	

// Members



	Vec2f origin{};

	Vec2f target{};

	Vec2f current{};

	const Gun& gun;

	bool reachedTarget{ false };

	bool debug{ false };
};


#endif // BULLET_H
