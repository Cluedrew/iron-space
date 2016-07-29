#ifndef NULLING_TARGET_HPP
#define NULLING_TARGET_HPP

/* This handles the targets code for the self nulling NullingPtr. (Implemented
 * in the GameObjectPtr.)
 */

#include <vector>
#include "../game-object-ptr.hpp"



class NullingTarget
{
private:
  // A list of all the pointers pointingg at this class.
  std::vector<GameObjectPtr*> ptrsToThis;
  typedef typename std::vector<GameObjectPtr*>::iterator ptr_iterator;
  friend class GameObjectPtr;

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

#endif//NULLING_TARGET_HPP
