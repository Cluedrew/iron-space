#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

/* AI Component: Handles most of the thinking for its GameObject.
 */



class AIComponent
{
private:
protected:
public:
  AIComponent ();
  virtual ~AIComponent () =0;

  virtual void update (GameObject & obj, sf::Time const & dt);

  virtual void handleInput (InputEvent);
  virtual void handleMessage (Message);
  virtual void handleCollision (Collision);
};

#endif//AI_COMPONENT_HPP
