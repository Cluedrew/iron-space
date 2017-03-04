#ifndef GAME_OBJECT
#define GAME_OBJECT

/* So some thoughts on a posible rework on the GameObject. The current
 * container based design is having some issues. Most of this has to do
 * with comunication between the components.
 *
 * For instance if the Ai wants to tell the Graphics how to draw itself,
 * it will have to get a GraphicsComponent and then cast it down to the
 * type with the proper interface. Or it could store the pointer itself,
 * but at that point it is starting to take on the role of the GameObject.
 *
 * So I am thinking of discarding the "generic container" model and then
 * have a GameObject base class which you inherite from and then create the
 * exact object you want. Shouldn't be any slower, it just pushes the virtual
 * method look-ups up a layer.
 *
 * Components will still be a thing, especially for reuse, but they might be
 * direct members instead of pointers. That may or may not be a problem for
 * some optimization ideas I had, but I'm a long way from having to cross that
 * bridge.
 *
 * Further re-use will come from intermediate base classes. These handle
 * functions many (but not all) of the final game objects share.
 */

class GameObject;
/* Defines the general interface for all GameObjects. Most of this has to do
 * with the main loop (input, update (ai/physics/colition) and draw) and
 * probably a memory management tool.
 *
 * Should default implementations be included or use pure virtual?
 */

class GameObject2D : public GameObject, public sf::Transformable;
/* MapObject? PlaneObject? I like the idea of varing it by the first letter.
 * This takes all of the features of the GameObject but then makes it occur
 * in a space. GameObject2D then has a location in space, and probably a body
 * that can collide and overlap (well maybe not always, but I think at this
 * point it is reasonable to assume that) as well as move around.
 *
 * So in short it adds 2D location and physics to the GameObject.
 *
 * handleCollision should also be broken up. There is some timing issues with
 * the current set up. I think we need 3 handlers: begin->continue->end.
 * Begin is called the first frame of collision, continue ever frame of
 * collison there after and end the first frame after that.
 * Those (begin->continue->end) are not the actual names.
 */

class Widget : public GameObject;
/* The "GuiObject". There might be some shared code with the GameObject2D but
 * really it is lacking the physics (except for collision with the mouse).
 * It might also have some nesting options, because widgets seem to be
 * orginized that way.
 */

class GameObject3D : public GameObject;
/* This isn't going to come along for a long time. But some day it might.
 * SpaceObject?
 */

template<typename ObjectType>
class GameObjectPointer;
/* The special pointer, which I do think will remain useful, would have to
 * change to a template. This is so we don't have to cast the results of the
 * pointer. I have been thinking about it and I don't think I can get around
 * casting the pointer.
 *
 * There is a base pointer which points to the object. The object always
 * points back to that base. To create subtypes we put it in a wrapper, which
 * checks the type in so the cast on the way out should never fail.
 *
 * Maybe an 'alive' field and a reference counter would work better, but I
 * would like to see this work.
 */

template<typename InternalType, typename ExternalType = InternalType>
class NullingPtr : public NullingPtrBase<InternalType>;
// Possible way to implement the NullingPtr, according to the above design.

#endif//GAME_OBJECT