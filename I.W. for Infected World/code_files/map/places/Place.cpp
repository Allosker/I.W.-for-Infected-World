#include "Place.h"




Place::Place(const SystemPath& texturePath, PlaceTypes _type)
	: type{ _type },
	textures{ Texture{ texturePath } }
{
	rebind();
}

Place::Place(const Vector<SystemPath>& texturePaths, PlaceTypes _type)
	: type{_type}
{
	for (const auto& path : texturePaths)
		textures.push_back(Texture{ path });

	rebind();
}

Place::Place(const PlaceInit& init)
	: type{init.type}
{
	for (const auto& path : init.paths)
		textures.push_back(Texture{ path });

	rebind();
}



const PlaceTypes& Place::getPlaceType() const noexcept
{
	return type;
}


bool Place::contains(const Vec2f& point) const noexcept
{
	Vec2f cT{ Util::vec2_cast<float>(textures.at(textureIndex).getSize()) + position };
	return (point.x > position.x && point.x < cT.x && point.y > position.y && point.y < cT.y);
}

void Place::nextTexture() noexcept
{
	textureIndex = textureIndex + 1 % textures.size();
	changeTexture = true;
	rebind();
}

void Place::setCenteredPosition(const Vec2f& pos, const Vec2f& text) noexcept
{
	Vec2f ocT{ text / 2.f };
	Vec2f cT{ Util::vec2_cast<float>(textures.at(textureIndex).getSize() / 2u) };

	position = pos + ocT - cT;
	rebind();
}


void Place::rebind()
{
	Vec2f cT{ Util::vec2_cast<float>(textures.at(textureIndex).getSize()) };


	core[0].position = position; // Up left
	core[1].position = { position.x + cT.x, position.y }; // Up right 
	core[2].position = { position.x, position.y + cT.y }; // Down left
	core[3].position = position + cT; // Down right


	if(changeTexture)
	{
		core[0].texCoords = { 0.f, 0.f };
		core[1].texCoords = { cT.x, 0.f };
		core[2].texCoords = { 0.f, cT.y };
		core[3].texCoords = cT;

		changeTexture = false;
	}

}


void Place::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(core, &textures.at(textureIndex));
}
