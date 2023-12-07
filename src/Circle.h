#include <SFML/Graphics.hpp>

/**
 * The Particle class represents a circle in a 2D space, using the Simple and Fast Multimedia Library (SFML).
 * It encapsulates properties such as radius, position, fill color, outline color, and outline thickness of the circle.
 */
class Particle {
private:
    float radius;
    float outline_thickness = 1.0f;
    sf::Vector2f position;
    sf::CircleShape shape;
    sf::Color fill_color = sf::Color::Magenta;
    sf::Color outline_color = sf::Color::Black;

public:
    Particle(float radius, sf::Vector2f position) : radius(radius), position(position) {
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
};