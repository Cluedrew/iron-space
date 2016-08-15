#ifndef NULL_AI_HPP
#define NULL_AI_HPP

/* Null Object for the AiComponent.
 */



class NullAi : public AiComponent
{
private:
protected:
public:
  virtual ~NullAi {}

  void init (GameObject &) {}
  /* Does nothing.
   * Params: Doesn't matter.
   */

  bool handleInput (GameObject &, InputEvent const &)
  /* Does nothing.
   * Params: Doesn't matter.
   * Return: Always false.
   */
  { return false; }

  void update (GameObject &, sf::Time const &) {}
  /* Does nothing.
   * Params: Doesn't matter.
   */
};

#endif//NULL_AI_HPP
