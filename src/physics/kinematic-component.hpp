#ifndef KINEMATIC_COMPONENT_HPP
#define KINEMATIC_COMPONENT_HPP

/* Adds movement to the base physics component.
 */

#include <SFML/System/Vector2.hpp>

#include "physics-component.hpp"



class KinematicComponent : public PhysicsComponent
{
private:
    // ? bool moving;
    sf::Vector2f velocity;
    float rotational;

protected:
public:
    KinematicComponent ();

    virtual ~KinematicComponent ();

    sf::Vector2f getVelocity ();

    void updateBody ();
};

#endif//KINEMATIC_COMPONENT_HPP
