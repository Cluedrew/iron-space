#ifndef AI_COMPONENT
#define AI_COMPONENT

/* The component that does the thinking.
 * Currently there is only one Component at all, later it should be a base
 * class for all the different blocks of AI.
 */

namespace sf { class Time; }
class InputEvent;



class AiComponent
{
private:
protected:
public:
  AiComponent ();

  virtual ~AiComponent ();

  bool handleInput (/*GameObject & parent,*/ InputEvent const & ievent);

  void update (/*GameObject & parent,*/ sf::Time const & deltaT);
};

#endif//AI_COMPONENT
