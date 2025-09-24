// ===========================
// Author: Allosker
// --
// File Name: MoveableEntity.cpp
// --
// Description: This class manages all deplacements of any Moveable Entity (hence the name), it includes all speed calculations that are needed for any entity to move around in the 2D world.
// Note: derived from Entity.
// ===========================



#include "MoveableEntity.h"


// Namespace allowing use of base values (class' member attributes) without poluting global namespace
// Note: this avoids recompiling every file depending on this class (hence no static constexpr in class declaration)
namespace MoveableEntity_Default
{
	constexpr float Speed{ 2 };
	constexpr float SpeedMulti{ 1 };
	constexpr float MaxSpeed{ 20 };
}



// Class -- Moveable Entity
/* ----------------------------------------------------------------------------- */


// Constructor
	


	MoveableEntity::MoveableEntity(const EntityInit& Einit)
		: Entity{Einit}
	{
		using namespace MoveableEntity_Default;

		velo.speed = Speed;
		velo.maxSpeed = MaxSpeed;
		velo.speedMulti = SpeedMulti;
	}


// Getters
	

	
	float MoveableEntity::getMagnitude() const noexcept
	{
		return std::sqrt(std::pow(currentPosition.x, 2) + std::pow(currentPosition.y, 2));
	}

	float MoveableEntity::getMagnitudeTextures() const noexcept 
	{
		return std::sqrt(std::pow(currentPosition.x + sprite.getTexture().getSize().x / 2, 2) + std::pow(currentPosition.y + sprite.getTexture().getSize().y / 2, 2));
	}

	Vec2f MoveableEntity::getNormalized() const noexcept
	{
		return currentPosition / getMagnitude();
	}

	float MoveableEntity::getDot(const Vec2f& point) const noexcept
	{
		return currentPosition.dot(point);
	}
	
	Vec2f MoveableEntity::getSeparatingVector(const Vec2f& point) const noexcept
	{
		return {point - currentPosition};
	}

	float MoveableEntity::getSeparatingAngle(const Vec2f& point) const noexcept
	{
		return std::acos(currentPosition.dot(point) / (getMagnitude() * point.length()));
	}


	// Not calculation related getters 

	const Vec2f& MoveableEntity::getCurrentPosition() const noexcept
	{
		return currentPosition;
	}

	Vec2f MoveableEntity::getCurrentPositionTextures() const noexcept
	{
		return currentPosition + static_cast<Vec2f>(Vec2u{ sprite.getTexture().getSize().x / 2, sprite.getTexture().getSize().y / 2 });
	}

	const Vec2f& MoveableEntity::getTargetPosition() const  noexcept
	{
		return targetPosition;
	}

	const Vec2f& MoveableEntity::getLastValidPosition() const noexcept
	{
		return lastValidPosition;
	}

	bool MoveableEntity::hasReachedTarget() const noexcept
	{
		return reachedTarget;
	}

	const Vec2f& MoveableEntity::getCurrentViewPosition() const noexcept
	{
		return currentViewPosition;
	}

	const View& MoveableEntity::getView() const noexcept
	{
		return view;
	}


// Setters



	void MoveableEntity::setReachedTarget(bool hasReached) noexcept
	{
		reachedTarget = hasReached;
	}

	void MoveableEntity::setSpeed(float newSpeed) noexcept
	{
		velo.speed = newSpeed;
	}

	void MoveableEntity::addSpeed(float addSpeed) noexcept
	{
		if (addSpeed >= velo.maxSpeed)
			addSpeed = velo.maxSpeed;

		velo.speed += addSpeed;
	}

	void MoveableEntity::setMaxSpeed(float maxSpeed) noexcept
	{
		velo.maxSpeed = maxSpeed;
	}

	void MoveableEntity::setSpeedMultiplicator(float newSpeedMulti) noexcept
	{
		velo.speedMulti = newSpeedMulti;
	}

	void MoveableEntity::teleportCenter(const Vec2f& target) noexcept
	{
		sprite.setPosition({target.x - sprite.getTexture().getSize().x / 2, target.y - sprite.getTexture().getSize().y / 2 });
		currentPosition = sprite.getPosition();
	}

	void MoveableEntity::teleport(const Vec2f& target) noexcept
	{
		sprite.setPosition(target);
		currentPosition = sprite.getPosition();
	}

	void MoveableEntity::setViewPosition(const Vec2f& newPos) noexcept
	{
		currentViewPosition = newPos;
	}

	void MoveableEntity::setNewView(View&& newView) noexcept
	{
		view = std::move(newView);
	}

	void MoveableEntity::setUpdatedZone(const sf::FloatRect& scissor) noexcept
	{
		view.setScissor(scissor);
	}

	void MoveableEntity::setViewSize(const Vec2f& newSize) noexcept
	{
		view.setSize(newSize);
	}

	void MoveableEntity::zoomView(const float& zoom) noexcept
	{
		view.zoom(zoom);
	}


// Calculations



	Vec2f MoveableEntity::normalizedDirection()
	{
		Vec2f direction{ targetPosition - currentPosition };
		if (direction.length() == 0) return { 0,0 };
		return direction / direction.length();
	}

	Vec2f MoveableEntity::applySpeedDT(const Vec2f& quotient, const Time& dt) noexcept
	{
		return { quotient * velo.speed * velo.speedMulti * dt.asSeconds() };
	}

	Vec2f MoveableEntity::applySpeedDT(const Vec2f& quotient, float x) noexcept
	{
		return { quotient * velo.speed * velo.speedMulti * x };
	}


// Actors



	void MoveableEntity::updateTextures()
	{
		static Clock FrameRate;
		Time timeEllapsed{ FrameRate.getElapsedTime() };
		if (reachedTarget)
		{
			setTexture(getCurrentIndexTextures().x, 0);
		}
		else
		{
			if(timeEllapsed.asMilliseconds() >= 100u)
			{
				nextTexture();
				FrameRate.restart();
			}
		}
	}

	void MoveableEntity::updateSounds()
	{

	}

	void MoveableEntity::updateView()
	{
		if(!detachView)
		{
			currentViewPosition = currentPosition;
			view.setCenter(currentViewPosition);
		}
	}


// Retrievers



	/*bool MoveableEntity::isPositionAvailable(const  Map& map)
	{
		size_t count{ 0 };
		for(const auto& tile : map.getCurrentZone().getTileZone())
		{
			if (tile.isCorrect(targetPosition))
			{
				count++;
			}
		}
		return (count == map.getCurrentZone().getTileZone().size()) ? true : false;
	}*/