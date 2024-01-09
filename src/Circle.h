#include <SFML/Graphics.hpp>

/**
 * The Particle class represents a circle in a 2D space, using the Simple and Fast Multimedia Library (SFML).
 * It encapsulates properties such as radius, position, fill color, outline color, and outline thickness of the circle.
 */
class Particle {
public:
    float radius;
    float outline_thickness = 1.0f;
    sf::Vector2f position;
    sf::Vector2f position_last;
    sf::Vector2f acceleration;
    sf::CircleShape shape;
    sf::Color fill_color = sf::Color::Magenta;
    sf::Color outline_color = sf::Color::Black;

    Particle(float radius, sf::Vector2f position)
    : radius(radius)
    , position(position)
    , position_last(position)
    , acceleration(0.0f, 0.0f) {
        shape.setRadius(radius);
        shape.setPosition(position);
        shape.setFillColor(fill_color);
        shape.setOutlineColor(outline_color);
        shape.setOutlineThickness(outline_thickness);
        shape.setScale(1.0f, 1.0f);
    }
    /**
     * Member function that draws the circle on an SFML render window.
     * @param target The SFML render window on which the circle will be drawn.
     */
    void show(sf::RenderWindow& target) {
        target.draw(shape);
    }

    void update(float dt)
    {
        // Compute how much we moved
        const sf::Vector2f displacement = position - position_last;
        // Update position
        position_last = position;
        position      = position + displacement + acceleration * (dt * dt);
        // Reset acceleration
        acceleration  = {};
    }

    void setVelocity(sf::Vector2f v, float dt)
    {
        position_last = position - (v * dt);
    }

    void accelerate(sf::Vector2f a)
    {
        acceleration +=a;
    }

};