#pragma once // Player.h

// ===========================
// Author: Allosker
// --
// File Name: Player.h
// --
// Description: This class manages everything a player should have, it redefines its movements alongside its different textures and sounds. This class is derived from two others.
// Note: the class manages the controls through a spelcialized class.
// ===========================


#include "entities/LivingEntity.h"

#include "Utilities/visual_effects/DisplayBar.h"

#include "map/Map.h"

class Bullet;

class Mosnter;

struct pDebug
{
	bool dProtective{ false }, dBorders{ false }, dCollect{ false }, dDie{ true };
};

// The class Player is an end, this class is a fully self-mananging enty derived from Living and Moveable entity. It is an entity that can be controlled by the player and it acts as the main window through which the user gets gameplay.
// See: MoveableEntity.h, LivingEntity.h
class Player final
	: public LivingEntity
{
public: 
// Constructor & Destructor 


	
	Player(const EntityInit& Einit, const Map& map);


	Player(Player&&) noexcept = default;

	Player& operator=(Player&&) = default;

	Player(Player&) = delete;

	Player operator=(Player&) = delete;


// Getters



	const Vector<const Tile*> isCollidingBT() const noexcept;

	int getIndex_ofTile(const Vec2f& pos) const noexcept;

	bool isWithinProtectiveArea(const Vec2f& point) const noexcept;

	bool isWithinCollectCircle(const Vec2f& point) const noexcept;

	pDebug& getPlayerDebug() noexcept;

	Util::DisplayBar& getLifeBar() noexcept;

	float getMoneyCount() const noexcept;

	u_int getFleshCount() const noexcept;


// Setters



	void setTarget(const Vec2f& target) override;

	void setRadiusProtectiveArea(unsigned int newRadiusArea) noexcept;

	void setRadiusCollectCircle(unsigned int newRadius) noexcept;

	void setViewSize(const Vec2f& newSize) noexcept;

	void setMoney(float money) noexcept;

	void setFleshCount(float flesh) noexcept;


// Actors


	
	void update(const Time& dt) override;

	void updatePlayerOnBorders(const Vec2f& offset);

	void updateSounds() override;

	void updateTextures() override;

	void updateOrientationPlayerTextures(const Vec2f& diff);

	
	void updateHiting(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitBullet(LivingEntity& targetEntity, Vector<Bullet>& bullets) override;

	void updateHitEntity(Monster& targetEntity) override;


	void draw(RenderTarget& target, RenderStates states) const override;


private:


	void setBorderReturn(const Vec2f& plaPos, bool& b, size_t& ind) const noexcept;


// Members


	const Map& refMap;

	sf::VertexArray debugVA{ sf::PrimitiveType::Lines, 8 };

	sf::CircleShape protectiveCircle{ };

	sf::CircleShape collectCircle{ };


	Util::DisplayBar lifebar{ Util::Position::Up_left };

	Vec2f sizeView;

	u_int fleshCount{};
	float moneyCount{};


	pDebug pdebug{};

};