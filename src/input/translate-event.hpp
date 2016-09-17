#ifndef TRANSLATE_EVENT_HPP
#define TRANSLATE_EVENT_HPP

// Function for sf::Event->InputEvent

namespace sf { class Event; }
class InputEvent;



bool translateEvent(sf::Event const & sfEvent, InputEvent & iEvent);
/* Translate sfEvent and write the result in iEvent.
 * Params: Reference to source sf::Event, mutable reference to
 *   destination InputEvent.
 * Effect: Will write to iEvent if a translation for sfEvent exists,
 *   otherwise has no effect.
 * Return: True if there is a translation for sfEvent, false otherwise.
 */

template<typename SourceT>
bool pollTranslateEvent(SourceT & source, InputEvent & iEvent);
/* Poll an event from source, translate it and write the result in iEvent.
 * Params: Mutable references to the source to get the event from and
 *   the iEvent to store the translated event in.
 * Return: True if an event was polled and translated, false the source had
 *   no more translatable events.
 */



#include "translate-event.tpp"

#endif//TRANSLATE_EVENT_HPP
