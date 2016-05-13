#include "interface.hpp"



// see header
Interface::Interface ();

// see header
Interface::~Interface ();

// see header
void Interface::handleUnMappedInput (sf::Event const &);

// see header
void Interface::foreachSelected (void (*)(GameObjectPtr));
