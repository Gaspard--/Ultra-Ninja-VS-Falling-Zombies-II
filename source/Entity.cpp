#include "Entity.hpp"

Entity::Entity(Fixture f)
  : fixture(f)
{
}

void Entity::update(void)
{
  renderable.destPos = fixture.pos;
}
