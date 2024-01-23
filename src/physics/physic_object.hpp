#pragma once
#include "collision_grid.hpp"
#include "engine\utils.hpp"


struct PhysicObject {
/**
 * @brief Represents a physics object in a simulation.
 * 
 * This class stores the position, last position, acceleration, and color of a physics object.
 * It provides a method to update the object's position based on the current acceleration and time step.
 */
    Vec2 position       = {0.0f, 0.0f};     /**< The current position of the physics object. */
    Vec2 last_position  = {0.0f, 0.0f};     /**< The previous position of the physics object. */
    Vec2 acceleration   = {0.0f, 0.0f};     /**< The acceleration of the physics object. */
    sf::Color color;                        /**< The color of the physics object. */

    /**
     * @brief Represents a physics object.
     * 
     * This class serves as a base class for all physics objects in the system.
     * It provides a default constructor.
     */
    PhysicObject() = default;

    /**
     * @brief Constructor that initializes the position of the physics object.
     * 
     * @param position_ The initial position of the physics object.
     */
    explicit
    PhysicObject(Vec2 position_)
        : position(position_)
        , last_position(position_)
    {}

    /**
     * @brief Updates the position of the physics object based on the current acceleration and time step.
     * 
     * @param dt The time step for the update.
     */
    void update(float dt)
    {
        const Vec2 last_update_move = position - last_position;

        const float VELOCITY_DAMPING = 40.0f; // arbitrary, approximating air friction

        const Vec2 new_position = position + last_update_move + (acceleration - last_update_move * VELOCITY_DAMPING) * (dt * dt);
        last_position           = position;
        position                = new_position;
        acceleration = {0.0f, 0.0f};
    }
};
