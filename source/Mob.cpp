#include "Mob.hpp"

Mob::Mob(Entity entity, int life)
  : entity(entity),
    life(life)
{
}

Mob::~Mob()
{
}

void Mob::setLife(int life)
{
  this->life = life;
}

int const& Mob::getLife() const
{
  return life;
}

