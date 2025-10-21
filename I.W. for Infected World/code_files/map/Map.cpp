// ===========================
// Author: Allosker
// --
// File Name: Map.cpp
// --
// Description: This class manages a set of zones and a pointer to one of the zones it includes to make it easy to communicate between all entities as to which zone they should appear on.
// Note: makes it easier for the zones to be loaded.
// TODO: make the system to manage the gates and allow the player to change zones.
// ===========================


#include "Map.h"



// Class -- Map
/* ----------------------------------------------------------------------------- */


// Constructors & Destructors



Map::Map(const Vector<ZoneInit>& zoneInit, const Vector<PlaceInit>& placeinit)
{
	for(const auto& i : zoneInit)
	{ 
		Zone temp{ i };

		zone_saver.emplace(i.name, std::move(temp));
	}

	currentZone = &zone_saver.at(zoneInit.at(0).name);

	for (const auto& i : placeinit)
		place_saver.push_back(Place{ i });

}


// setters



void Map::setCurrentZone(const String& key)
{
	currentZone = &zone_saver.at(key);
	loadCurrentZone();
}


// Actors



float Map::getWidth() const noexcept
{
	return currentZone->getTileCount().x * currentZone->getTileTextureSize().x;
}

Vec2f Map::getRealSize() const noexcept
{
	return { currentZone->getTileCount().x * currentZone->getTileTextureSize().x, currentZone->getTileCount().y * currentZone->getTileTextureSize().y };
}

Vec2u Map::getTileCount() const noexcept
{
	return currentZone->getTileCount();
}

Vec2f Map::getPosition() const noexcept
{
	return currentZone->getPosition();
}

Vec2f Map::getPosition_plus_Size() const noexcept
{
	return { getPosition().x + getRealSize().x, getPosition().y + getRealSize().y };
}

bool Map::currentZoneContains(const Vec2f& point) const noexcept
{
	return ( ( point.x >= getPosition().x && point.y >= getPosition().y) && (point.x <= getPosition_plus_Size().x && point.y <= getPosition_plus_Size().y) );
}

PlaceTypes Map::placeThatContains(const Vec2f& mousePosition)
{
	for (const auto& place : place_saver)
		if (place.contains(mousePosition))
			return place.getPlaceType();
}



void Map::shufflePlaces()
{
	for (auto& place : place_saver)
	{
		u_int index = Util::random_number(0, currentZone->size() - 1);

		const Tile& tile{ currentZone->getTileZone().at(index) };

		place.setCenteredPosition(tile.getPosition(), Util::vec2_cast<float>(tile.getTexture().getSize()) );
	}
}

void Map::loadCurrentZone()
{
	currentZone->load();
	shufflePlaces();
}

void Map::teleportCurrentZone(const Vec2f& newPos)
{
	currentZone->setPosition(newPos);
}


void Map::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(*currentZone);
	
	for (const auto& tar : place_saver)
		target.draw(tar);
}