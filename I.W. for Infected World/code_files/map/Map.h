#pragma once // Map.h

// ===========================
// Author: Allosker
// --
// File Name: Map.h
// --
// Description: This class manages a set of zones and a pointer to one of the zones it includes to make it easy to communicate between all entities as to which zone they should appear on.
// Note: makes it easier for the zones to be loaded.
// TODO: make the system to manage the gates and allow the player to change zones.
// ===========================


#include "sets/Tile.h"
#include "sets/Zone.h"

#include "umbrella headers/memory.h"
#include "umbrella headers/sfml.h"



// Map manages the sets of zones that can be traveled throughout the duration of the game, it also manages loading times and the 'gates' that enable the player to go from one zone to another.
class Map : public sf::Drawable
{
public:
// Constructors & Destructors



	Map(const Vector<ZoneInit>& zoneInit);


	Map(Map&&) = default;

	Map& operator=(Map&&) = default;


	virtual ~Map() = default;


// Setters



	void setCurrentZone(const String& key);


// Getters



	const Zone& getCurrentZone() const noexcept { return *currentZone; }

	Zone& getCurrentZone() noexcept { return *currentZone; }

	float getWidth() const noexcept;

	// Returns real size of current zone
	Vec2f getRealSize() const noexcept;
	
	Vec2u getTileCount() const noexcept;

	Vec2f getPosition() const noexcept;

	Vec2f getPosition_plus_Size() const noexcept;

	bool currentZoneContains(const Vec2f& point) const noexcept;

	
// Actors

	

	void loadCurrentZone();

	void teleportCurrentZone(const Vec2f& newPos);

	void draw(RenderTarget& target, RenderStates states) const override;


private:
// Members


	Omap<String, Zone> zone_saver{};

	Zone* currentZone{};


};