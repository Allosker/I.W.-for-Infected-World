#ifndef RANGE_H
#define RANGE_H


#include <cmath>
#include <numbers>

#include "umbrella headers/sfml.h"

#include "memory Utils/DeltaTime.h"

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
	: sf::Drawable
{
// Actors


	void update(const DeltaTime& dt, float threshold, float maxDist) noexcept;

	// Rendering
	void draw(RenderTarget& target, RenderStates states) const override;
	

// Members



	Vec2f origin{};

	Vec2f target{};

	Vec2f current{};
	
	float velocity{ 1 };

	bool reachedTarget{ false };


	bool debug{ false };
};



class Range
	: sf::Drawable
{
public:


	void update(const DeltaTime& dt);



private:


	float velocity{ 1 };

	float randomizer{}, minRand{}, maxRand{ 1 };

	float threshold{ 2 }, maxDist{};

	Vec2f originWeapon{};

	Vec2f weaponTarget{};

	Vector<Bullet> bullets;

};


#endif RANGE_H
