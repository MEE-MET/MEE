#include <SFML/Graphics.hpp>
#include "Circle.h"

auto test(sf::RenderTarget& target) -> void;

int main() {
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "PhysicsEngine" };
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        Object circle(75.0f, {960.0f, 540.0f});
        circle.show(window);
        window.display();
    }
}

auto test(sf::RenderTarget& target) -> void {
    sf::Vector2f v = {960.0f, 540.0f};
    sf::CircleShape circle(100.0f, 100);
    circle.setOrigin(50.0f, 50.0f);
    circle.setPosition(v);
    circle.setScale(1.0f, 1.0f);
    circle.setFillColor(sf::Color::Magenta);
    target.draw(circle);
}