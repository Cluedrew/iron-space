#ifndef WINDOW_HPP
#define WINDOW_HPP

/* Scratch pad, I realized I need some way to make information about the
 * window (notably its height and width) widely avaible. But I don't want
 * to crack open the Engine class for that. So it looks like I am going to
 * have to resort to global variables to get it done. (Which I have so far
 * avoided.)
 *
 * OK
 */

// So what I ultimately want is something like this:
sf::Vector2u getWindowSize (unsigned int windowId);
/* Return the height and width of the window with the given Id.
 */

// But I think I will need a wrapper like this:
struct WindowManager
{
  static sf::Vector2u getWindowSize (unsigned int windowId);
  // Same as above:

  // Now does it hold references to the windows:
  static unsigned int regesterWindow (sf::Window & window);
  static void updateWindow (unsigned int windowId);
  // Or just the required information:
  static unsigned int regesterWindow (sf::Vector2u const & windowSize);
  static void updateWindowSize (sf::Vector2u const & windowSize);
};

#endif//WINDOW_HPP
