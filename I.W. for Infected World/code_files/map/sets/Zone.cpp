// ===========================
// Author: Allosker
// --
// File Name: Zone.cpp
// --
// Description: This class manages a zone (zone defined by a set of tiles). This zone manages the placement of the tiles alongisde their functions (whether they are borders or not).
// Note: needs to be loaded (is created but not loaded upon creation) -- to improve performances and choose well-placed loading times.
// TODO: include the boundaries around the zone.
// ===========================


#include "Zone.h"



// Class -- Zone
/* ----------------------------------------------------------------------------- */


// Constructors & Destructors



Zone::Zone(const ZoneInit& zoneInit)
	: tileSize{zoneInit.size}, name{zoneInit.name}
{
	for (const auto& paths : zoneInit.paths)
	{
		Tile temp{ paths };

		tile_set.push_back(std::move(temp));
	}

	for (int i{ 0 }; i != tileSize.x * tileSize.y; i++)
	{
		tile_zone.push_back(Tile{ zoneInit.paths.at(0) });
	}
}

Zone::Zone(Vector<Tile>&& tiles, const Vec2f& newSize, String&& _name) noexcept
	: tile_set{ std::move(tiles) }, globalBounds{ {}, newSize }, tileSize{ static_cast<Vec2u>(newSize) }, name { std::move(_name) }
{
}


// Getters



const Tile& Zone::getTile(size_t index) const
{
	return tile_set.at(index);
}

const Vector<Tile>& Zone::getTileSet() const noexcept
{
	return tile_set;
}

const Vector<Tile>& Zone::getTileZone() const noexcept
{
	return tile_zone;
}

Vector<Tile>& Zone::getTileZone() noexcept
{
	return tile_zone;
}

const Vec2u& Zone::getTileCount() const noexcept
{
	return countTiles;
}

const Vector<size_t>& Zone::getTileBorder() const noexcept
{
	return borderTilesIndexes;
}

const sf::FloatRect& Zone::getGlobalBounds() const noexcept
{
	return globalBounds;
}

const Vec2f& Zone::getSize() const noexcept
{
	return globalBounds.size;
}

const Vec2f& Zone::getTileSize() const noexcept
{
	return tileSize;
}

Vec2f Zone::getTileTextureSize() const noexcept
{
	return { static_cast<float>(tile_zone.at(0).getTexture().getSize().x), static_cast<float>(tile_zone.at(0).getTexture().getSize().y) };
}

size_t Zone::size() const noexcept
{
	return tile_zone.size();
}

const Vec2f& Zone::getPosition() const noexcept
{ 
	return globalBounds.position; 
}

const String& Zone::getName() const noexcept
{
	return name;
}


// Setters



void Zone::setName(String&& newName) noexcept
{
	name = newName;
}

void Zone::setTileBorderType(size_t tileIndex, size_t borderTypeIndex, const BT& type)
{
	tile_set.at(tileIndex).setBorderType(borderTypeIndex, type);
}

void Zone::setTilePosition(size_t index, const Vec2f& newPosition)
{
	tile_set.at(index).setPosition(newPosition);
}

void Zone::setSizeInTiles(const Vec2f& newSize) noexcept
{
	tileSize = newSize;
}

void Zone::setPosition(const Vec2f& newPos) noexcept
{
	defineZone(tileSize.x, tileSize.y);
}


// Actors



void Zone::load()
{
	constructZone(tileSize.x, tileSize.y);
}

// Width and Height in tiles
void Zone::constructZone(size_t width, size_t height)
{
	countTiles = { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
	generateZone(width, height);
	defineZone(width, height);
	borderZone(width, height);
	getTileBorder();
}





// define which tile should be a border
void Zone::borderZone(size_t width, size_t height)
{
	using BT = BorderType;

	{
		if (!isBordered)
			for (size_t i{ 0 }; i != height; i++)
			{
				for (size_t j{ 0 }; j != width; j++)
				{
					if (j == 0)
						tile_zone.at(i * width + j).setBorderType(0, BT::Left);

					if (j == width - 1)
						tile_zone.at(i * width + j).setBorderType(1, BT::Right);

					if (i == 0)
						tile_zone.at(i * width + j).setBorderType(2, BT::Up);

					if (i == height - 1)
						tile_zone.at(i * width + j).setBorderType(3, BT::Down);


					if (tile_zone.at(i * width + j).isaBorder())
						borderTilesIndexes.push_back(i * width + j);
				}
			}
	}
}

// Fully constructs the zone by alligning the tiles and setting their borders
void Zone::defineZone(size_t width, size_t height)
{
	if(!isDefined)
	{
		Vec2f newPos{ globalBounds.position };

		for (size_t i{ 0 }; i != height; i++)
		{
			for (size_t j{ 0 }; j != width; j++)
			{
				tile_zone.at(i * width + j).setPosition(newPos);

				newPos.x += tile_zone.at(0).getTexture().getSize().x;
			}
			newPos.y += tile_zone.at(0).getTexture().getSize().y;

			newPos.x = 0;
		}
		isDefined = true;
	}
}

// Randomly retrieves a tile from the saver to put it into the zone saver to then complete its construction
void Zone::generateZone(size_t width, size_t height)
{
	if(!isGenerated)
		for (size_t i{ 0 }; i != width * height; i++)
			tile_zone.at(Util::random_number(0, tile_zone.size() - 1)) = tile_set.at(Util::random_number(0, tile_set.size() - 1));

	isGenerated = true;
}



void Zone::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& i : tile_zone)
		target.draw(i);
}


