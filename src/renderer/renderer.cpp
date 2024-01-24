#include "renderer.hpp"

/**
 * @brief Construct a new Renderer:: Renderer object
 * 
 * @param solver_ Solver to render
 * @param tp thread pool to use
 */
Renderer::Renderer(PhysicSolver& solver_, tp::ThreadPool& tp)
    : solver{solver_}
    , world_va{sf::Quads, 4}
    , objects_va{sf::Quads}
    , thread_pool{tp}
{
    initializeWorldVA();

    object_texture.loadFromFile("res/circle.png");
    object_texture.generateMipmap();
    object_texture.setSmooth(true);
}

/**
 * @brief Render the solver
 * 
 * @param context render context
 */
void Renderer::render(RenderContext& context)
{
    context.draw(world_va);

    sf::RenderStates states;
    states.texture = &object_texture;
    context.draw(world_va, states);
    // Particles
    updateParticlesVA();
    context.draw(objects_va, states);
}

/**
 * @brief Initialize the world vertex array
 * 
 */
void Renderer::initializeWorldVA()
{
    world_va[0].position = {0.0f               , 0.0f};
    world_va[1].position = {solver.world_size.x, 0.0f};
    world_va[2].position = {solver.world_size.x, solver.world_size.y};
    world_va[3].position = {0.0f               , solver.world_size.y};

    const uint8_t level = 50;
    const sf::Color background_color{level, level, level};
    world_va[0].color = background_color;
    world_va[1].color = background_color;
    world_va[2].color = background_color;
    world_va[3].color = background_color;
}

/**
 * @brief Update the particles vertex array
 * 
 */
void Renderer::updateParticlesVA()
{
    objects_va.resize(solver.objects.size() * 4);

    const float texture_size = 1024.0f;
    const float radius       = 0.5f;
    thread_pool.dispatch(to<uint32_t>(solver.objects.size()), [&](uint32_t start, uint32_t end) {
        for (uint32_t i{start}; i < end; ++i) {
            const PhysicObject& object = solver.objects.data[i];
            const uint32_t idx = i << 2;
            objects_va[idx + 0].position = object.position + Vec2{-radius, -radius};
            objects_va[idx + 1].position = object.position + Vec2{ radius, -radius};
            objects_va[idx + 2].position = object.position + Vec2{ radius,  radius};
            objects_va[idx + 3].position = object.position + Vec2{-radius,  radius};
            objects_va[idx + 0].texCoords = {0.0f        , 0.0f};
            objects_va[idx + 1].texCoords = {texture_size, 0.0f};
            objects_va[idx + 2].texCoords = {texture_size, texture_size};
            objects_va[idx + 3].texCoords = {0.0f        , texture_size};

            const sf::Color color = object.color;
            objects_va[idx + 0].color = color;
            objects_va[idx + 1].color = color;
            objects_va[idx + 2].color = color;
            objects_va[idx + 3].color = color;
        }
    });
}