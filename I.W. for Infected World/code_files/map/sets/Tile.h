#pragma once // Tile.h

// ===========================
// Author: Allosker
// --
// File Name: Tile.h
// --
// Description: This class manages a tile (which stands as a sf::Sprite) that can be drawn on screen and that manages it's own position. A tile can be set to have a border to either of its sides. It then blocks a MoveableEntity from going.
// ===========================


#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"



// BorderType defines all types of border possible for a tileS
enum class BorderType
{
	None = -1,
	Up,
	Down,
	Left,
	Right
};


using BT = BorderType;


 
// Tile manages one tile, its postion and its texture and its type. A tile is a set of 6 vertices (a rectangle) for performances.
class Tile
	: public sf::Drawable
{
public:
// Constructor & Destructor 



	Tile(const SystemPath& path, Array<BT, 4> bt);


	Tile(const SystemPath& path);

	Tile(Texture&& otherTexture, Array<BT, 4> bt);

	Tile(Tile&&) = default;

	Tile& operator=(Tile&&) = default;

	Tile(const Tile&) = default;

	Tile& operator=(const Tile&) = default;


	virtual ~Tile() = default;


// Getters



	BT getBorder(size_t index) const;

	Array<BT, 4> getBorderArray() const noexcept;

	const Vec2f& getPosition() const noexcept;

	const Texture& getTexture() const noexcept;

	/*bool isCorrect(const Vec2f& target) const;*/

	bool isaBorder() const noexcept;

	bool contains(const Vec2f& point) const noexcept;


// Setters



	void setBorderType(size_t index, BT bt) noexcept;

	// Sets whether this tile acts as a border or not
	void setBorder(bool b) noexcept;

	void setPosition(const Vec2f& newPosition) noexcept;

	void setTexture(const SystemPath& path) noexcept;


// Actors



	void construct() noexcept;
	
	void draw(RenderTarget& target, RenderStates states) const override;



protected:
// Members



	Texture texture;

	VertexArray tile{ sf::PrimitiveType::TriangleStrip, 4 };

	Vec2f basePosition{};

	Array<BT, 4> borderType;

	bool isBorder{ false };
	

};