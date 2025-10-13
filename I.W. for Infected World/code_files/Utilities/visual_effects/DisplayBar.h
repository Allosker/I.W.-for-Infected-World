#pragma once

#include "umbrella headers/sfml.h"

#include "entities/LivingEntity.h"

namespace Util
{


	enum class Position
	{
		Up_left,
		Up_right,
		Middle,
		Down_left,
		Down_right,
	};

	enum class BarType
	{
		Bar,
		Frame,
		Under,
	};


	class DisplayBar
		: public sf::Drawable
	{
	public:

		DisplayBar() = delete;

		DisplayBar(const Position& _position)
			: position{ _position }
		{
			for (int i{}; i != bar.getVertexCount(); i++)
			{
				bar[i].color = Color::Green;
				underBar[i].color = Color::Red;
			}
		}


		void setDisplay(bool b) noexcept
		{
			display = b;
		}

		void setSize(const Vec2f& newSize) noexcept
		{
			size = newSize;
		}

		void update(float life, float maxLife, const Vec2f& pos, const Vec2f& text)
		{
			using P = Position;
			float quotient{};

			switch (position)
			{
			case P::Up_left:

				underBar[0].position = pos; // Up left 
				underBar[1].position = { pos.x, pos.y + size.y }; // Down left
				underBar[3].position = { pos.x + size.x, pos.y + size.y }; // Down right
				underBar[2].position = { pos.x + size.x, pos.y }; // Up right

				quotient = life * size.x / maxLife;

				if (quotient > size.x)
					quotient = size.x;
				break;

			case P::Middle:

				Vec2f sPosition{ pos.x + text.x / 2, pos.y - 5 };

				underBar[0].position = { sPosition.x - size.x, sPosition.y }; // Up left 
				underBar[1].position = { sPosition.x - size.x, sPosition.y + size.y }; // Down left
				underBar[3].position = { sPosition.x + size.x, sPosition.y + size.y }; // Down right
				underBar[2].position = { sPosition.x + size.x, sPosition.y }; // Up right

				quotient = life * size.x / maxLife * 2;

				if (quotient > size.x * 2)
					quotient = size.x * 2;

				break;
			}
			

			bar[0].position = underBar[0].position;
			bar[1].position = underBar[1].position;

			bar[2].position = { underBar[0].position.x + quotient, underBar[0].position.y };
			bar[3].position = { underBar[1].position.x + quotient, underBar[1].position.y };
		}


		void draw(RenderTarget& target, RenderStates states) const override
		{
			if (display)
			{
				target.draw(underBar);

				target.draw(bar);
			}
		}


	private:

		VertexArray bar{ sf::PrimitiveType::TriangleStrip, 4 };
		VertexArray underBar{ sf::PrimitiveType::TriangleStrip, 4 };

		Vec2f size{ 20, 2.5 };

		Position position;


		bool display{ true };
	};
}