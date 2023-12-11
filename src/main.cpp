#include <SFML/Graphics.hpp>
#include "Solver.hpp"

auto test(sf::RenderTarget& target) -> void;

int main() {
    constexpr int32_t window_width  = 1000;
    constexpr int32_t window_height = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet", sf::Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    Solver   solver;

    // Solver configuration
    solver.setConstraint({static_cast<float>(window_width) * 0.5f, static_cast<float>(window_height) * 0.5f}, 450.0f);
    solver.setSubStepsCount(8);
    solver.setSimulationUpdateRate(frame_rate);

    // Set simulation attributes
    const float        object_spawn_delay    = 0.5f;
    const float        object_spawn_speed    = 600.0f;
    const sf::Vector2f object_spawn_position = {500.0f, 500.0f};
    const uint32_t     object_count          = 5;
    
    sf::Clock clock;
    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
                
            }
        }

        if (solver.getObjectsCount() < object_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            auto&   object = solver.addObject(object_spawn_position, 25.0);
            solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{1.0, 0.0});
        }

        solver.update();
        window.clear(sf::Color::White);
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraint_background{constraint.z};
        constraint_background.setOrigin(constraint.z, constraint.z);
        constraint_background.setFillColor(sf::Color::Black);
        constraint_background.setPosition(constraint.x, constraint.y);
        constraint_background.setPointCount(128);
        window.draw(constraint_background);

        // Render objects
        sf::CircleShape circle{1.0f};
        circle.setPointCount(32);
        circle.setOrigin(1.0f, 1.0f);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.position);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.fill_color);
            window.draw(circle);
        }
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