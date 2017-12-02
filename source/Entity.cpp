#include "Entity.hpp"

Entity::Entity(Fixture f, bool b)
  : fixture(f), isOnPlanet(b)
{
}

void Entity::update(void)
{
  // renderable.destPos = fixture.pos;
}
