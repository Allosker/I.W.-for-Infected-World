#include "Collectible.h"




Collectible::Collectible(const Vector<SystemPath>& textPaths, Vec2f pos)
{
	position = std::move(pos);

	for (const auto& path : textPaths)
	{
		Texture temp{};

		if (!temp.loadFromFile(path))
			throw std::runtime_error{ "couldn't load file from collectible" };

		textures.push_back(std::make_shared<Texture>(std::move(temp)));
	}

	if (textures.size())
	{
		bind_to_texture();
		bind_to_position();
	}
}

Collectible::Collectible(const Vector<Shared_ptr<Texture>>& shared)
{
	for (const auto& i : shared)
	{
		textures.push_back(i);
	}
	if (textures.size())
	{
		bind_to_texture();
		bind_to_position();
	}
}

// Setters



void Collectible::teleport(const Vec2f& newPos) noexcept
{
	position = newPos;
	bind_to_position();
}

void Collectible::collect() noexcept
{
	collected = true;
}


// Getters



const Vec2f& Collectible::getPosition() const noexcept
{
	return position;
}

Vec2f Collectible::getPositionTextures() const noexcept
{
	const Vec2f text{ Util::vec2_cast<float>(textures.at(currentTextureIndex)->getSize()) };

	return { position.x + text.x / 2, position.y + text.y / 2};
}

bool Collectible::isCollected() const noexcept
{
	return collected;
}

const Vector<Shared_ptr<Texture>>& Collectible::getSharedTextures() const noexcept
{
	return textures;
}

const Texture& Collectible::getCurrentTexture() const noexcept
{
	return *textures.at(currentTextureIndex);
}


// Actors



void Collectible::bind_to_texture() noexcept
{
	const Vec2f text{ Util::vec2_cast<float>(textures.at(currentTextureIndex)->getSize()) };

	sprite[0].texCoords = { 0.f, 0.f };
	sprite[1].texCoords = { text.x, 0.f };
	sprite[2].texCoords = { 0.f, text.y };
	sprite[3].texCoords = { text };
}

void Collectible::bind_to_position() noexcept
{
	const Vec2f textPos{ Util::vec2_cast<float>(textures.at(currentTextureIndex)->getSize()) };

	sprite[0].position = position;
	sprite[1].position = {position.x, position.y + textPos.y};
	sprite[2].position = { position.x + textPos.x, position.y };
	sprite[3].position = { position.x + textPos.x, position.y + textPos.y };
}

void Collectible::next_texture_in_array() noexcept
{
	static std::int16_t index;

	currentTextureIndex = index % textures.size();

	index++;
}


void Collectible::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(sprite, &*textures.at(currentTextureIndex));
}
