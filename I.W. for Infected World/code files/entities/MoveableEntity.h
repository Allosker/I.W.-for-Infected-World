#ifndef MOVEABLEENTITY_H
#define MOVEABLEENTITY_H
// ===========================
// Author: Allosker
// --
// File Name: MoveableEntity.h
// --
// Description: This class manages all deplacements of any Moveable Entity (hence the name), it includes all speed calculations that are needed for any entity to move around in the 2D world.
// Note: derived from Entity.
// ===========================



#include "entities/Entity.h"


#include "map/Map.h"



#include "umbrella headers/memory.h"
#include "umbrella headers/sfml.h" 



struct VelocityRelated
{
    float speed{ 1 };
    float maxSpeed{ 1 };

    float speedMulti{ 1 };
};



// Moveable Entity is an abstract class, it essentially acts as a base for any entity that can move on screen. It has many functions used to calculate postions/directiosn/offsets -- mainly acts as a giant pre-set of calculations.
// It also offers a common interface for all MoveableEntities, a common function to update them all (which allows for polymorphism), this class is essential for managing the displacments of a great number of enemies.
// See: Entity.h
class MoveableEntity 
    : public Entity
{
public:
// Constructor & Destructor 



    MoveableEntity(const EntityInit& Einit);


    MoveableEntity(MoveableEntity&&) noexcept = default;

    MoveableEntity& operator=(MoveableEntity&&) noexcept = default;

    MoveableEntity(MoveableEntity&) = delete;

    MoveableEntity operator=(MoveableEntity&) = delete;

    virtual ~MoveableEntity() = default;


// Getters



    float getMagnitude() const noexcept;

    float getMagnitudeTextures() const noexcept;

    Vec2f getNormalized() const noexcept;

    float getDot(const Vec2f& point) const noexcept;

    Vec2f getSeparatingVector(const Vec2f& point) const noexcept;

    // Note: doesn't take into account all four quadrants
    float getSeparatingAngle(const Vec2f& point) const noexcept;
    

    // # Not Calculations

    
    const Vec2f& getCurrentPosition() const noexcept;

    Vec2f getCurrentPositionTextures() const noexcept;

    const Vec2f& getTargetPosition() const noexcept;

    const Vec2f& getLastValidPosition() const noexcept;
        
    bool hasReachedTarget() const noexcept;

    const Vec2f& getCurrentViewPosition() const noexcept;

    const View& getView() const noexcept;


// Setters



    virtual void setTarget(const Vec2f& target) = 0;

    void setReachedTarget(bool hasReached) noexcept;

    void setSpeed(float newSpeed) noexcept;

    void addSpeed(float addSpeed) noexcept;

    void setMaxSpeed(float maxSpeed) noexcept;

    void setSpeedMultiplicator(float newSpeedMulti) noexcept;

    void teleportCenter(const Vec2f& target) noexcept;

    void teleport(const Vec2f& target) noexcept;

    void setViewPosition(const Vec2f& newPos) noexcept;

    void setNewView(View&& newView) noexcept;

    void setUpdatedZone(const sf::FloatRect& scissor) noexcept;

    void setViewSize(const Vec2f& newSize) noexcept;

    void zoomView(const float& zoom) noexcept;


// Calculations



    // ONLY Calculates the direction of the entity based on the target
    Vec2f normalizedDirection();

    // Calculates an offset based on the direction and speed
    Vec2f applySpeedDT(const Vec2f& quotient, const Time& dt) noexcept;

    Vec2f applySpeedDT(const Vec2f& quotient, float x) noexcept;


// Actors
      

    // Common interface between all Moveable Entities
    virtual void update(const Time& dt) = 0;

    virtual void updateTextures();

    virtual void updateSounds();

    virtual void updateView();



protected:
// Retrievers

    
    /*bool isPositionAvailable(const  Map& map);*/


    // Position Related 
    
        // Positions
        Vec2f targetPosition{};

        Vec2f currentPosition{};

        Vec2f lastValidPosition{};

        // States
        bool positionAvailable{ false };
        
        bool reachedTarget{ false };

        bool isMoving{ false };


        // Arrival
        float threshold{ 1 };

        Vec2f cThreshold{ 1, 1 };
    
        
    // View

        View view{};

        Vec2f currentViewPosition{};

        bool detachView{false};


    // Speed Related


        VelocityRelated velo{};

};

#endif // MOVEABLEENTITY_H