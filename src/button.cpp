#include "button.hpp"

// Implementation of the button. Which is to say the set of components that
// make a button.

#include "physics/align-rect-collider.hpp"
#include "physics/physics-component.hpp"
#include "ai/click-ai.hpp"
#include "graphics/circle-graphics.hpp"



// see header
Button::Button(Command * effect, float x, float y, float w, float h) :
    GameObject(new ClickAi(effect),
//               new AlignRectCollider(x, y, w, h),
               new PhysicsComponent(),
               new CircleGraphics(25))
{}
