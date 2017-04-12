#include "text-fragment.hpp"

// Implementation of TextFragment object constructor.

#include "../ai/null-ai.hpp"
#include "../physics/null-physics.hpp"
#include "../graphics/text-graphics.hpp"
#include "../util/transforms.hpp"



TextFragment::TextFragment(std::string const & text, float x, float y,
    Alignment2D alignment) :
  Widget(xyTransformable(x, y), new NullAi(), new NullPhysics(),
      new TextGraphics("FreeSans.ttf", text, alignment))
{}
