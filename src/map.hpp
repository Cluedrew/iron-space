#ifndef MAP_HPP
#define MAP_HPP

/*
 */

#include <vector>
#include <SFML/Graphics/View.hpp>
#include "map-object.hpp"



class Map
{
private:
  std::vector<MapObject> objects;
  sf::View cammra;
protected:
public:
  Map ();
  virtual ~Map ();
};

#endif//MAP_HPP
