#ifndef PLAYER_H
#define PLAYER_H
// ===========================
// Author: Allosker
// --
// File Name: Player.h
// --
// Description: This class manages everything a player should have, it redefines its movements alongside its different textures and sounds. This class is derived from two others.
// Note: the class manages the controls through a spelcialized class.
// ===========================



#include "entities/MoveableEntity.h"


#include "entities/LivingEntity.h"


#include "umbrella headers/memory.h"
#include "umbrella headers/sfml.h"



// The class Player is an end, this class is a fully self-mananging enty derived from Living and Moveable entity. It is an entity that can be controlled by the player and it acts as the main window through which the user gets gameplay.
// See: MoveableEntity.h, LivingEntity.h
class Player final
	: public MoveableEntity, public LivingEntity
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


// Setters



	void setTarget(const Vec2f& target) override;


// Actors


	
	void update(const DeltaTime& dt) override;

	void updatePlayerOnBorders();

	void updateSounds() override;

	void updateTextures() override;

	void updateOrientationPlayerTextures(const Vec2f& diff);


	void draw(RenderTarget& target, RenderStates states) const override;


private:


	void setBorderReturn(const Vec2f& plaPos, bool& b, size_t& ind) const noexcept;

// Members


	const Map& refMap;

	sf::VertexArray debugVA{ sf::PrimitiveType::Lines, 8 };

	Vec2f newPos;
};


#endif // PLAYER_H