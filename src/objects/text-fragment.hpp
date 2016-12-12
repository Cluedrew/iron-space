#ifndef TEXT_FRAGMENT_HPP
#define TEXT_FRAGMENT_HPP

/* A game-object that repersents a piece of text.
 */

#include <string>
#include "../game-object.hpp"



struct TextFragment : public GameObject
{
  TextFragment (std::string const & text);
  /* Create a text fragment that desplays the given text.
   * Params: A string repersenting the characters to print out.
   */
};

#endif//TEXT_FRAGMENT_HPP
