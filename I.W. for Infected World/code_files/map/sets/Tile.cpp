// ===========================
// Author: Allosker
// --
// File Name: Tile.h
// --
// Description: This class manages a tile (which stands as a sf::Sprite) that can be drawn on screen and that manages it's own position. A tile can be set to have a border to either of its sides. It then blocks a MoveableEntity from going.
// ===========================


#include "Tile.h"



enum class BorderType;

using BT = BorderType;



// Class -- Tile
/* ----------------------------------------------------------------------------- */


// Constructor



Tile::Tile(const SystemPath& path, Array<BT, 4> bt)
	: borderType{ bt }
{
	if (!texture.loadFromFile(path))
		throw std::runtime_error{ "couldnt load texture" }; 
	construct();
}

Tile::Tile(const SystemPath& path)
	: texture{ path }, borderType{ BT::None, BT::None, BT::None, BT::None}
{
	construct();
}

Tile::Tile(Texture&& otherTexture, Array<BT, 4> bt)
	: texture{std::move(otherTexture)}, borderType{ bt }
{
	construct();
}


// Getters



BT Tile::getBorder(size_t index) const
{
	switch (borderType.at(index))
	{
	case BT::Up:
		return BT::Up;
		break;
	case BT::Down:
		return BT::Down;
		break;
	case BT::Left:
		return BT::Left;
	case BT::Right:
		return BT::Right;
	case BT::None:
		return BT::None;
		break;
	}
}

Array<BT, 4> Tile::getBorderArray() const noexcept
{
	return borderType;
}

const Vec2f& Tile::getPosition() const noexcept
{ 
	return basePosition;
}

const Texture& Tile::getTexture() const noexcept
{
	return texture;
}

bool Tile::isaBorder() const noexcept
{
	return isBorder;
}

bool Tile::contains(const Vec2f& point) const noexcept
{
	const Vec2f& text{ static_cast<Vec2f>(texture.getSize()) };
	if ((point.x >= basePosition.x && point.y >= basePosition.y) && (point.x <= basePosition.x + text.x && point.y <= basePosition.y + text.y))
		return true;
	
	return false;
}


// Setters



void Tile::setBorderType(size_t index, BT bt) noexcept
{
	borderType.at(index) = bt;
	if (borderType.at(index) != BT::None)
		isBorder = true;
}

void Tile::setBorder(bool b) noexcept
{
	isBorder = b;
}

void Tile::setPosition(const Vec2f& newPosition) noexcept
{
	basePosition = newPosition;
	construct();
}

void Tile::setTexture(const SystemPath& path) noexcept
{
	texture.loadFromFile(path);
}


// Actors



void Tile::construct() noexcept
{
	tile[0].position = basePosition;
	tile[1].position = { basePosition.x + texture.getSize().x, basePosition.y  };
	tile[2].position = { basePosition.x, basePosition.y + texture.getSize().y };
	tile[3].position = { basePosition.x + texture.getSize().x, basePosition.y + texture.getSize().y };

	tile[0].texCoords = { 0.f , 0.f };
	tile[1].texCoords = { 0.f + texture.getSize().x, 0.f };
	tile[2].texCoords = { 0.f, 0.f + +texture.getSize().y };
	tile[3].texCoords = { 0.f + texture.getSize().x, 0.f + +texture.getSize().y };
}

void Tile::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(tile, &texture);
}