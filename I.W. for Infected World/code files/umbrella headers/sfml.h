#ifndef SFML_H
#define SFML_H
// ===========================
// Author: Allosker
// --
// File Name: memory.h
// --
// Description: This header includes everything that is used from SFML in the game.
// Note: it also defines type alliases to reduce wiritng-time as well as some overrides for vector2.
// ===========================


// Include
// ---------------------------------------------------------------------------------------


#include "SFML/Graphics.hpp"

#include "SFML/Audio.hpp"

#include "SFML/Window.hpp"



// Type Alliases
// ---------------------------------------------------------------------------------------


template<typename T>
using Vec2 = sf::Vector2<T>;

using Vec2f = sf::Vector2f; 
using Vec2i = sf::Vector2i; 
using Vec2u = sf::Vector2u; 

using Vec3f = sf::Vector3f;
using Vec3i = sf::Vector3i;

using RectShape = sf::RectangleShape;
using CircleShape = sf::CircleShape;
using Vertex = sf::Vertex;
using VertexArray = sf::VertexArray; 

using Sprite = sf::Sprite; 
using Texture = sf::Texture; 

using Sound = sf::Sound; 
using SoundBuffer = sf::SoundBuffer; 

using Text = sf::Text;
using Font = sf::Font;

using Color = sf::Color; 

using Shader = sf::Shader; 
using Image = sf::Image; 

using RenderWindow = sf::RenderWindow; 
using RenderTarget = sf::RenderTarget; 
using RenderStates = sf::RenderStates;
using RenderTexture = sf::RenderTexture; 

using View = sf::View; 

using Clock = sf::Clock;
using Time = sf::Time;

using SystemPath = std::filesystem::path; 



// Overloads
// ---------------------------------------------------------------------------------------


template<typename T, typename U>
Vec2f operator/(const Vec2<T>& a, const Vec2<U> b)
{
	return { a.x / b.x, a.y / b.y };
}

template<typename T, typename U>
Vec2f operator*(const Vec2<T>& a, const Vec2<U> b)
{
	return { a.x * b.x, a.y * b.y };
}

namespace Util
{

	template<typename T>
	T vAbs(const Vec2<T> vec)
	{
		return { std::abs(vec.x), std::abs(vec.y) };
	}

}


#endif // SFML_H