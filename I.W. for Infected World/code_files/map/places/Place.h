#pragma once // Place.h

#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"


enum class PlaceTypes
{
	None = -1,
	Bunker,
	Campfire,
	Camp,
};

struct PlaceInit
{
	const Vector<SystemPath>& paths;

	const PlaceTypes& type;
};

class Place
	: public sf::Drawable
{
public:

	Place(const SystemPath& texturePath, PlaceTypes _type);

	Place(const Vector<SystemPath>& texturePaths, PlaceTypes _type);

	Place(const PlaceInit& init);


	const PlaceTypes& getPlaceType() const noexcept;


	bool contains(const Vec2f& point) const noexcept;


	void nextTexture() noexcept;

	void setCenteredPosition(const Vec2f& pos, const Vec2f& text) noexcept;

	void rebind();


	void draw(RenderTarget& target, RenderStates states) const override;


private:



	VertexArray core{ sf::PrimitiveType::TriangleStrip, 4 };

	Vector<Texture> textures{};

	Vec2f position{};

	u_int textureIndex{};

	PlaceTypes type{};

	bool changeTexture{ false };

};