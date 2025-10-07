#pragma once // Bullet.h


#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"

class Gun;


static inline Vec2f getOffset(const Vec2f& target, const Vec2f& origin, float velocity)
{
	Vec2f offset{ target - origin };
	offset /= offset.length();
	offset *= velocity;

	return offset;
}


class Bullet
	: public sf::Drawable
{
public:

	Bullet() = default;

	Bullet(Bullet&&) noexcept = default;

	Bullet& operator=(const Bullet&) = default; 

	Bullet& operator=(Bullet&&) = default;


// Actors


	void update(const Time& dt) noexcept;

	// Rendering
	void draw(RenderTarget& target, RenderStates states) const override;
	

// Members



	Vec2f origin{};

	Vec2f target{};

	Vec2f current{};

	float velocity{}, threshold{}, damage{};

	bool reachedTarget{ false };

	bool debug{ false };
};