#include "ai-component.hpp"

// Implementation of the virtual AIComponent.
// This implements a bunch of default "do nothing" options.



AIComponent::AIComponent () {}

AIComponent::~AIComponent () {}

void AIComponent::update (GameObject & obj, sf::Time const & dt) {}

void AIComponent::handleInput (InputEvent const & iEvent) {}
void AIComponent::handleMessage (Message & msg) {}
void AIComponent::handleCollision (GameObjectPtr & with) {}
