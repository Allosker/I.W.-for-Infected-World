#pragma once // Collectible.h


#include "umbrella headers/sfml.h"
#include "umbrella headers/memory.h"


class Collectible
	: public sf::Drawable
{
public:
// Constructors & Destructors



	Collectible(const Vector<SystemPath>& textPaths, Vec2f pos = { 0.f, 0.f });

	Collectible(const Vector<Shared_ptr<Texture>>& shared);

	virtual ~Collectible() = default;


// Setters



	void teleport(const Vec2f& newPos) noexcept;

	void collect() noexcept;


// Getters

	

	const Vec2f& getPosition() const noexcept; 

	Vec2f getPositionTextures() const noexcept;

	bool isCollected() const noexcept;

	const Vector<Shared_ptr<Texture>>& getSharedTextures() const noexcept;

	const Texture& getCurrentTexture() const noexcept;


// Actors 



	void bind_to_texture() noexcept;

	void bind_to_position() noexcept;

	void next_texture_in_array() noexcept;


	void draw(RenderTarget& target, RenderStates state) const override;


private:


	bool collected{ false };


	Vec2f position{};

	Vector<Shared_ptr<Texture>> textures;
	size_t currentTextureIndex{};


	VertexArray sprite{ sf::PrimitiveType::TriangleStrip, 4 };

};