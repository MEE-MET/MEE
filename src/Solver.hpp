#include <SFML/Graphics.hpp>
#include "Circle.h"

class Solver {
public:
    Solver() = default;

    Particle& addObject(sf::Vector2f position, float radius)
    {
        return objects.emplace_back(radius, position);
    }

        void setSimulationUpdateRate(uint32_t rate)
    {
        frame_dt = 1.0f / static_cast<float>(rate);
    }

    void update()
    {
        time += frame_dt;
        const float step_dt = getStepDt();
        for (uint32_t i{sub_steps}; i--;) {
            checkCollisions(step_dt);
            applyConstraint();
            updateObjects(step_dt);
        }
    }

    void setConstraint(sf::Vector2f position, float radius)
    {
        constraint_center = position;
        constraint_radius = radius;
    }

    void setSubStepsCount(uint32_t sub_steps)
    {
        sub_steps = sub_steps;
    }

    void setObjectVelocity(Particle& object, sf::Vector2f v)
    {
        object.setVelocity(v, getStepDt());
    }

    [[nodiscard]]
    const std::vector<Particle>& getObjects() const
    {
        return objects;
    }

    [[nodiscard]]
    sf::Vector3f getConstraint() const
    {
        return {constraint_center.x, constraint_center.y, constraint_radius};
    }

    [[nodiscard]]
    uint64_t getObjectsCount() const
    {
        return objects.size();
    }

    [[nodiscard]]
    float getTime() const
    {
        return time;
    }

    [[nodiscard]]
    float getStepDt() const
    {
        return frame_dt / static_cast<float>(sub_steps);
    }

private:
    uint32_t                  sub_steps          = 1;
    sf::Vector2f              constraint_center;
    float                     constraint_radius  = 100.0f;
    std::vector<Particle>     objects;
    float                     time               = 0.0f;
    float                     frame_dt           = 0.0f;

    void checkCollisions(float dt)
    {
        const float    response_coef = 0.75f;
        const uint64_t objects_count = objects.size();
        // Iterate on all objects
        for (uint64_t i{0}; i < objects_count; ++i) {
            Particle& object_1 = objects[i];
            // Iterate on object involved in new collision pairs
            for (uint64_t k{i + 1}; k < objects_count; ++k) {
                Particle&      object_2 = objects[k];
                const sf::Vector2f v        = object_1.position - object_2.position;
                const float        dist2    = v.x * v.x + v.y * v.y;
                const float        min_dist = object_1.radius + object_2.radius;
                // Check overlapping
                if (dist2 < min_dist * min_dist) {
                    const float        dist  = sqrt(dist2);
                    const sf::Vector2f n     = v / dist;
                    const float mass_ratio_1 = object_1.radius / (object_1.radius + object_2.radius);
                    const float mass_ratio_2 = object_2.radius / (object_1.radius + object_2.radius);
                    const float delta        = 0.5f * response_coef * (dist - min_dist);
                    // Update positions
                    object_1.position -= n * (mass_ratio_2 * delta);
                    object_2.position += n * (mass_ratio_1 * delta);
                }
            }
        }
    }

    void applyConstraint()
    {
        for (auto& obj : objects) {
            const sf::Vector2f v    = constraint_center - obj.position;
            const float        dist = sqrt(v.x * v.x + v.y * v.y);
            if (dist > (constraint_radius - obj.radius)) {
                const sf::Vector2f n = v / dist;
                obj.position = constraint_center - n * (constraint_radius - obj.radius);
            }
        }
    }

    void updateObjects(float dt)
    {
        for (auto& obj : objects) {
            obj.update(dt);
        }
    }
};
