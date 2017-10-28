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

// Name to: reciveInput?
bool GameObject::handleInput (InputEvent const & input)
{
  // For all relievent event times, check to see if targets this object.
  // I think that is all can do at this point and that is not very much.
  // InputEvent pos whould have to be a vector2
  if (InputEvent::Select == input.type && !collides(PointCollider(input.pos)))
    return false;
  else
    return innerHandleInput(input);
}

// This pair could be used in the input handler, but we need to have some
// access to the attached state. I could just store it, one wasted pointer
// on non-listening objects is reasonable at this scale.
void GameObject::regester ()
{
  WorldState * state = getItSomeHow();
  FatFunction<void, InputEvent const &> listener;
  listener.set<GameObject, &GameObject::handleInput>(this);
  state.listeners.insert(listener);
}

void GameObject::unregester ()
{
  WorldState * state = getItSomeHow();
  FatFunction<void, InputEvent const &> listener;
  listener.set<GameObject, &GameObject::handleInput>(this);
  state.listeners.remove(listener);
}


class PlaneObject : public GameObject
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
  setFlag(GameObject::UpdatePhysics);
}


class Widget : public GameObject
{
public:
  Widget ();
};

Widget::Widget () :
{
  //setFlag(...);
}
