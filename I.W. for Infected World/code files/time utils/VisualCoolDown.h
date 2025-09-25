#pragma once // VisualCooldown.h

// ===========================
// Author: Allosker
// --
// File Name: CoolDown.h
// --
// Description: This class manages a cooldown akin to CoolDown. 
// With one exception, it has to be attached to an entity and it displays a visual representation of the cooldown upon it.
// ===========================


#include "CoolDown.h"

#include "entities/MoveableEntity.h" 



class VisualCoolDown :
	public CoolDown, public sf::Drawable
{
public:
// Constructors & Destructors



	VisualCoolDown(const MoveableEntity& mv)
		: entity{mv}
	{ 
	}



// Setters



	void setColorBar(const Color& c) noexcept
	{
		colorBar = c;
	}

	void setColorBarFrame(const Color& c) noexcept
	{
		colorBarFrame = c;
	}

	void setSizeBarFrame(const Vec2f& newSize) noexcept
	{
		size = newSize;
	}


// Actors 



    bool update() noexcept override
    {
		updateBar_and_Frame();

		if (timer.getElapsedTime().asSeconds() >= cooldown)
		{
			finished = true;
			timer.stop();
			return true;
		}
		else
		{
			if (!firstTime)
				finished = false;
			return false;
		}
    }

	void updateBar_and_Frame()
	{
		if(cooldown != 0)
		{

			Vec2f sPosition{ entity.getCurrentPosition().x + entity.getCurrentTexture().getSize().x / 2, entity.getCurrentPosition().y - 5 };

			barFrame[0].position = { sPosition.x - size.x, sPosition.y };
			barFrame[1].position = { sPosition.x - size.x, sPosition.y + size.y };
			barFrame[2].position = { sPosition.x + size.x, sPosition.y + size.y };
			barFrame[3].position = { sPosition.x + size.x, sPosition.y };
			barFrame[4].position = barFrame[0].position;
			

			float quotient{ static_cast<float>(timer.getElapsedTime().asSeconds() * size.x / cooldown) * 2 };

			if (quotient > size.x * 2)
				quotient = size.x * 2;
			
			bar[0].position = barFrame[0].position;
			bar[1].position = barFrame[1].position; 

			bar[2].position = { barFrame[0].position.x + quotient, barFrame[0].position.y};
			bar[3].position = { barFrame[1].position.x + quotient, barFrame[1].position.y };

			bar[0].color = colorBar;
			bar[1].color = colorBar;
			bar[2].color = colorBar;
			bar[3].color = colorBar;
		}
	}


	void draw(RenderTarget& target, RenderStates states) const override
	{
		if(cooldown != 0)
		{
			if(timer.getElapsedTime().asSeconds() != 0 && !finished)
			{
				target.draw(bar);

				target.draw(barFrame);
			}
		}
	}


protected:
// Members



	VertexArray barFrame{ sf::PrimitiveType::LineStrip, 5 };

	VertexArray bar{ sf::PrimitiveType::TriangleStrip, 4 };

	Vec2f size{ 10,  2.5 };

	Color colorBarFrame{};

	Color colorBar{ Color::Red };



	const MoveableEntity& entity;

	
};