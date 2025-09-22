#ifndef ZONE_H
#define ZONE_H
// ===========================
// Author: Allosker
// --
// File Name: Zone.h
// --
// Description: This class manages a zone (zone defined by a set of tiles). This zone manages the placement of the tiles alongisde their functions (whether they are borders or not).
// Note: needs to be loaded (is created but not loaded upon creation) -- to improve performances and choose well-placed loading times.
// TODO: include the boundaries around the zone.
// ===========================


#include "map/sets/Tile.h"

#include "memory Utils/random.h"



using BT = BorderType;


// ZoneInit helps for the construction of a zone by reducing the number of arguement needed
struct ZoneInit
{
	ZoneInit(const Vector<SystemPath>& p, const Vec2f& s, String&& n="undefined")
		: paths{p}, size{s}, name{std::move(n)}
	{
	}

	ZoneInit(Vector<SystemPath>&& p, const Vec2f& s, String&& n="undefined")
		: paths{std::move(p)}, size(s), name(std::move(n))
	{ }

	Vector<SystemPath> paths{};
	Vec2f size{};
	String name;
};


// Zone defines a set of tiles. It manages the positions/functions of those tiles. When a zone is constructed it is not yet loaded.
class Zone : public sf::Drawable
{
public:
// Constructor & Destructor



	Zone(const ZoneInit& zoneInit);

	Zone(Vector<Tile>&& tiles, const Vec2f& newSize, String&& _name) noexcept;


	Zone(Zone&&) = default;

	Zone& operator=(Zone&&) = default;

	Zone(Zone&) = delete;

	Zone operator=(Zone&) = delete;


// Getters

	

	const Tile& getTile(size_t index) const;

	// tile_set contains all the tiles that exist for this zone
	// Note: doesn't represent the zone
	const Vector<Tile>& getTileSet() const noexcept;

	// tile_zone contains all the tiles composing the zone -- this represents the real zone
	const Vector<Tile>& getTileZone() const noexcept;

	Vector<Tile>& getTileZone() noexcept;

	const Vec2u& getTileCount() const noexcept;

	const Vector<size_t>& getTileBorder() const noexcept;

	const sf::FloatRect& getGlobalBounds() const noexcept;


	const Vec2f& getSize() const noexcept;

	const Vec2f& getTileSize() const noexcept;

	const Vec2f& getTileTextureSize() const noexcept;


	const Vec2f& getPosition() const noexcept;

	const String& getName() const noexcept;


// Setters



	void setName(String&& newName) noexcept;

	void setPosition(const Vec2f& newPos) noexcept;

	void setTileBorderType(size_t tileIndex, size_t borderTypeIndex, const BT& type);

	void setTilePosition(size_t index, const Vec2f& newPosition);


// Actors



	void load();
	
	void constructZone(size_t width, size_t height);

	void borderZone(size_t width, size_t height);

	void defineZone(size_t width, size_t height);

	void generateZone(size_t width, size_t height);


	void draw(RenderTarget& target, RenderStates states) const override;


private:
// Members



	String name{};

	Vector<Tile> tile_set{};

	Vector<Tile> tile_zone{};

	Vec2f tileSize{};

	Vec2u countTiles{};
	
	sf::FloatRect globalBounds{ {0,0}, {} };
	
	mutable Vector<size_t> borderTilesIndexes{};


};
#endif // ZONE_H