#ifndef NULLING_PTR_HPP
#define NULLING_PTR_HPP

/* OK, so I have a slight issue with the GameObjectPtr, and that is that
 * nothing about its behaviour is about being a GameObject, so I am going
 * to make a template smart pointer and try and use that. Plus it would be
 * nice to take the pointer logic out of the GameObject class.
 *
 * It is actually an oberver. However it is a very narrow one.
 */

/* This is an intermediary that is to prevent a circle of dependancies.
 * This class is used to let the NullingTarget refer back to the NullingPtr
 * type.
 * This may be avoidable with some template tricks but currently I have no
 * how that world work.
 */
class NullingPtrBase
{
  virtual void nullptr() =0;
  friend class NullingTarget;
};

/* A NullingTarget is what the NullingPtr points at. Actually I might go for
 * composition and instead say that for a NullingPtr to point at a class it
 * must have a member that is a NullingTarget.
 */
class NullingTarget
{
private:
  // A list of all the pointers pointingg at this class.
  std::vector<NullingPtrBase*> ptrsToThis;

public:
  NullingTarget();
  /* Create a target with no pointers pointing at it.
   * Hence, it should have no references to pointers either.
   */

  virtual ~NullingTarget();
  /* When a NullingTarget is deleted all NullingPtrs pointing at it are set
   * to null so they may not be dereferenced (as the target no longer exists).
   */

  NullingTarget(NullingTarget const &) = delete;
  /* Invalid, even if the surounding class implements this you cannot copy
   * the idea of being pointed at.
   */

  NullingTarget(NullingTarget &&);
  /* Might be valid, as it does make sense that if something is moved the
   * pointers would keep pointing to it at its new location.
   */

  NullingTarget & operator=(NullingTarget const &) = delete;
  /* Invalid, again what does it mean to copy "is pointed at"? Not much.
   */

  NullingTarget & operator=(NullingTarget &&); // ? = delete; ?
  /* Move assignment is still up in the are. Pointers at the old object
   * can be changed to the new one, but what happens to things that were
   * pointing at the one being assigned to? Do they get nulled? Do all
   * the pointer continue to point at the assigned class?
   *
   * Lets use the combine operation for now:
   */
};

// Default Constructor for NullingTarget
NullingTarget::NullingTarget() :
  ptrsToThis()
{}

NullingTarget::~NullingTarget ()
{
std::vector<GameObjectPtr*>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     (**it).ptr = nullptr;
  }
}


NullingTarget::NullingTarget(NullingTarget && other) :
  ptrsToThis(other.ptrsToThis)
{
  // Is other.ptrsToThis emptied?

  std::vector<GameObjectPtr*>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     (**it).ptr = this;
  }
}

NullingTarget & NullingTarget::operator=(NullingTarget && other)
{
  while (!other.ptrsToThis.empty())
  {
    GameObjectPtr * ptr = other.ptrsToThis.back();
    ptr->ptr = this;
    other.ptrsToThis.pop_back();
  }
}

/* Smart pointer that goes to null when its target is deleted/freed.
 */
template<class TargetT>
class NullingPtr : public NullingPtrBase
{
private:
  TargetT * ptr;

  void nullptr()
  {
    ptr = nullptr;
  }

protected:
  void unregester ();
  /* Internal function for setting the pointer to point at nothing.
   * If the pointer already points at nothing than nothing is done.
   */

  void regesterTo (TargetT *);
  /* Internal function for setting the pointer to point at something.
   * If the pointer already points at something it is first unregestered.
   */

  void takeRegester (NullingPtr<TargetT> && other);
  /* takeRegester(other)
   * Take the other NullingPtr's pointer, nulling it if it isn't already
   * null.
   */

public:
  NullingPtr ();
  /* Default NullingPtr constructor, points at nothing.
   */
}

#endif//NULLING_PTR_HPP
