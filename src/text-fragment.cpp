#include "text-fragment.hpp"

// Implementation of TextFragment object constructor.

#include "ai/null-ai.hpp"
#include "physics/align-rect-collider.hpp"
#include "physics/physics-component.hpp"
#include "graphics/text-graphics.hpp"



TextFragment::TextFragment(std::string const & text) :
    GameObject(new NullAi(),
               new PhysicsComponent(new AlignRectCollider(0, 0, 50, 10)),
               new TextGraphics("FreeSans.ttf", text))
{}
