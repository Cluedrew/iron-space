/* This is the proto-types for the designs in plan/game-object.hpp. So it
 * will be  both the .hpp and .cpp files later.
 */

// Generic GameObject. Management and messaging.
class GameObject
{
public:
  enum ControlFlags
  {
    RespondToMouse = 1,
    UpdatePhysics = 2,
  };

private:
  ControlFlags controlFlagSet;

  // Backwards compatability, this component system is probably going away.
  AiComponent * ai;
  PhysicsComponent * physics;
  GraphicsComponent * graphics;

protected:
  void setFlag (ControlFlags flag) { controlFlagSet |= flag; }
  void unsetFlag (ControlFlags flag) { controlFlagSet &= ~flag; }
  bool getFlag (ControlFlags flag) { return controlFlagSet & flag; }
  // Wrappers for accessing the internal flags.

  virtual void update (sf::Time const & deltaT);

public:
  GameObject ();
  GameObject (AiComponent * ai,
              PhysicsComponent * physics,
              GraphicsComponent * graphics);
  GameObject (sf::Transformable const & start);
  GameObject (sf::Transformable const & start,
              AiComponent * ai,
              PhysicsComponent * physics,
              GraphicsComponent * graphics);
  /* Create a new GameObject,
   * Params:
   * - start: The starting transform.
   * - ai, physics, graphics: Component objects, if not given they will be
   *   NULL. If given ownership is taken, do not free.
   */

  /* The functions that "delagate" to a Component object can still be
   * overriden, but if they aren't they will call the object if it is
   * provided, otherwise it will be a no-op.
   */

  GameObject (GameObject const & other) = delete;
  GameObject & operator= (GameObject const & other) = delete;
  GameObject & operator= (GameObject && other) = delete;
  GameObject (GameObject && other) = delete;
  // All disabled, move construction might be added back in.

  virtual ~GameObject ();

  void updateStep (sf::Time const & deltaT);

  virtual void draw (sf::RenderTarget & target, sf::RenderStates states) const;

  bool handleInput (InputEvent const & input);
  bool collides (GameObject const & other) const;
  bool collides (Collider const & other) const;
  void handleCollision (GameObjectPtr & with);
};

GameObject::~GameObject ()
{
  delete ai;
  delete physics;
  delete graphics;
}

void GameObject::updateStep (sf::Time const & deltaT)
{
  update(deltaT);
  // If the object has physics, update it according to volocity. This will
  // cause a bit of shearing, will change to buffering if it is a problem.
  if (control & UpdatePhysics)
    updatePhysics();
}

void GameObject::update (sf::Time const & deltaT)
{
  if (update) ai->update(*this, deltaT);
}

void GameObject::draw (sf::RenderTarget & target,
                       sf::RenderStates states) const
{
  if (graphics)
  {
    states.transform *= getTransform();
    target.draw(*graphics, states);
  }
}

bool GameObject::handleInput (InputEvent const & input)
{
  // Or
  if (input.type == InputEvent::Select)
}


class PlaneObject
{
public:
  PlaneObject ();

  // Adds the overlap functions.
protected:
  virtual void overlapBegin (PlanObject & with) {}
  virtual void overlapNext (PlanObject & with) {}
  virtual void overlapEnd (PlanObject & with) {}
  // Plus the checkers.
};

PlaneObject::PlaneObject ()
{
  setFlags(GameObject::UpdatePhysics);
}
