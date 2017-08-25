#ifndef STATUS_DISPLAY_HPP
#define STATUS_DISPLAY_HPP

/* The StatusDisplay is the main way to get information about an Entity.
 * It is part of the players UI.
 */

#include <SFML/Graphics/RenderTexture.hpp>
#include "object/widget.hpp"
namespace sf { class RenderTarget; class RenderStates; }
class Entity;



class StatusDisplay : public Widget
{
private:
  // Might actually be stored elsewhere.
  std::vector<Entity const *> selection;

  sf::RenderTexture core;

  void draw (sf::RenderTarget& target, sf::RenderStates states) const;

protected:
public:
  StatusDisplay ();

  void display (Entity const & source);
};

#endif//STATUS_DISPLAY_HPP
