#include "text-fragment.hpp"

// Implementation of TextFragment object constructor.

#include "../ai/null-ai.hpp"
#include "../physics/null-physics.hpp"
#include "../graphics/text-graphics.hpp"
#include "../util/transforms.hpp"



TextFragment::TextFragment(std::string const & text, float x, float y,
    Alignment2D alignment) :
  GameObject(xyTransformable(x, y), new NullAi(), new NullPhysics(),
      new TextGraphics("FreeSans.ttf", text))
{
#if 0
  // TODO The underlying code required for this simply does not exist.
  // Not even with a basic work around. At GameObject and several of the
  // components will have to change.
  sf::FloatRect bounds;
  {
    TextGraphics temp("FreeSans.ttf", text);
    bounds = temp.getLocalBounds();
  }
  float xOrigin;
  float yOrigin;
  switch(verticalAlignmentComponent(alignment))
  {
  case VerticalAlignment::Top:
    yOrigin = 0;
    break;
  case VerticalAlignment::Middle:
    yOrigin = bounds.height / 2;
    break;
  case VerticalAlignment::Bottom:
    yOrigin = bounds.height;
    break;
  }
  switch(horizontalAlignmentComponent(alignment))
  {
  case HorizontalAlignment::Left:
     xOrigin = 0;
     break;
  case HorizontalAlignment::Center:
     xOrigin = bounds.width / 2;
     break;
  case HorizontalAlignment::Right:
     xOrigin = bounds.width;
     break;
  }
  setOrigin(xOrigin, yOrigin);
#endif
}
