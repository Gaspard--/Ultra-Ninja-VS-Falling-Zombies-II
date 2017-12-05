#include "Entity.hpp"

Entity::Entity(Fixture f)
  : fixture(f),
    isUseless(false)    
{
}

void Entity::update(void)
{
  // renderable.destPos = fixture.pos;
}
