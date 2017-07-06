#include "null-game-object.hpp"

// Implement the GameObject that implements nothing.

#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"



NullGameObject::NullGameObject () :
  GameObject(new NullAi(), new NullPhysics(), new NullGraphics())
{}
