#include "button.hpp"

// Implementation of the button. Which is to say the set of components that
// make a button.

#include "util/command.hpp"
#include "physics/align-rect-collider.hpp"
#include "physics/physics-component.hpp"
#include "ai/click-ai.hpp"
#include "graphics/align-rect-graphics.hpp"
#include "util/transforms.hpp"



// see header
Button::Button(Command * effect, float x, float y, float w, float h) :
    GameObject(xyTransformable(x, y),
               new ClickAi(effect),
               new PhysicsComponent(new AlignRectCollider(x, y, w, h)),
               new AlignRectGraphics(w, h))
{
  // TODO Something to move the shape over so x & y are not ignored.
  // This solution isn't working.
  //this->move(x, y);
}
