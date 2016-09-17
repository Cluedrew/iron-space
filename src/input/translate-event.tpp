#ifndef TRANSLATE_EVENT_TPP
#define TRANSLATE_EVENT_TPP

// Implementation of pollTranslateEvent.



template<typename SourceT>
bool pollTranslateEvent (SourceT & source, InputEvent & iEvent)
{
  sf::Event sfEvent;
  while (source.pollEvent(sfEvent))
  {
    if (translateEvent(sfEvent, iEvent))
      return true;
  }

  return false;
}

#endif//TRANSLATE_EVENT_TPP
