#ifndef MAP_OBJECT_HPP
#define MAP_OBJECT_HPP

/* An object on the map.
 */



class MapObject : public GameObject
{
private:
  void draw (...);

protected:
public:
  MapObject ();
  virtual ~MapObject ();

  void update ();
  // Update the AI.

  void travel ();
  // Update physics over time.
};

#endif//MAP_OBJECT_HPP
