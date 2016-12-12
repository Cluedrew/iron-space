#include "text-fragment.hpp"

// Implementation of TextFragment object constructor.

#include "../ai/null-ai.hpp"
#include "../physics/null-physics.hpp"
#include "../graphics/text-graphics.hpp"



TextFragment::TextFragment(std::string const & text) :
    GameObject(new NullAi(), new NullPhysics(),
               new TextGraphics("FreeSans.ttf", text))
{}
