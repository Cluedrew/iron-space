#ifndef TEXT_FRAGMENT_HPP
#define TEXT_FRAGMENT_HPP

/* A game-object that repersents a piece of text.
 */

#include <string>
#include "../game-object.hpp"
#include "../util/alignment.hpp"



struct TextFragment : public GameObject
{
  TextFragment (std::string const & text, float x = 0, float y = 0,
      Alignment2D alignment = Alignment2D::TopLeft);
  /* Create a text fragment that desplays the given text.
   * Params: A string repersenting the characters to print out.
   *   The x & y coordinates of where the text should be drawn.
   *   The alignment of the origin.
   */
};

#endif//TEXT_FRAGMENT_HPP
