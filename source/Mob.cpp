#include "Mob.hpp"

Mob::Mob(Entity entity, int life)
  : entity(entity),
    isJumping(false),
    life(life),
    offsetY(0)
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

void Mob::setOffset(double offsetY)
{
  this->offsetY = offsetY;
}

double const& Mob::getOffset() const
{
  return offsetY;
}
