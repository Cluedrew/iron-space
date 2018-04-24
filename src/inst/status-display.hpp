#ifndef STATUS_DISPLAY_HPP
#define STATUS_DISPLAY_HPP

/* The StatusDisplay is the main way to get information about an Entity.
 * It is part of the players UI.
 *
 * The StatusDisplay works with the Entity base class to show information
 * about the selected Entity classes.
 * First the StatusDisplay will grab the simple "uniform" data from the
 * Entity's getter functions. Second, it will pass the request for any
 * particular images it needs (probably using a combination of RenderTarget
 * and View). Third it will just hand-over control of the drawing to the
 * Entity by use of some callbacks.
 */

#include <string>
#include <SFML/Graphics/RenderTexture.hpp>
namespace sf { class RenderTarget; class RenderStates; }
#include "object/widget.hpp"
#include "graphics/font-marc.hpp"
class Entity;



class StatusDisplay : public Widget
{
private:
  sf::RenderTexture core;
  FontMaRC titleFont;

  // Display variables:
  unsigned char numStatusBars;

  void updateCore (sf::Time const & deltaT);

  // Yet another reason I have to refactor.
  friend class StatusDisplayAi;

protected:
public:
  StatusDisplay ();

  virtual ~StatusDisplay () {}

  void display (Entity const & source);
  /* Display the given entity on this widget.
   */

  // CallBacks:
  void drawStatusBar(std::string const & name, sf::Color const & color,
                     unsigned int max, unsigned int current);
  /* Draw a bar, showing some X/Y score on the unit.
   *   + Also the proof of concept call back right now.
   */
};

#endif//STATUS_DISPLAY_HPP
