#include "Zombie.hpp"

Zombie::Zombie(Entity entity)
  : Mob(entity, 2),
    lead(false)
{
}

Zombie::Zombie(Human &villager)
  : Mob(villager.entity, 2),
    lead(false)
{
}

Zombie::~Zombie()
{
}

void Zombie::setLead(bool lead)
{
  this->lead = lead;
}

bool const& Zombie::getLead() const
{
  return lead;
}
