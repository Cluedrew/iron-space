#include "entity.hpp"

// Construct the entity.

#include "ai/ai-wrapper.hpp"



Entity::Entity(PhysicsComponent * physics, GraphicsComponent * graphics) :
    PlaneObject(new AiWrapper(), physics, graphics)
{}
