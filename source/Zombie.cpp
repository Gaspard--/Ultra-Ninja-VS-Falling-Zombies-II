#include "Zombie.hpp"

Zombie::Zombie(Entity entity)
  : Mob(entity, 2),
    lead(false),
    target(NULL)
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

void Zombie::infectHuman(Human &villager) const
{
  villager.setInfected(true);
}

void Zombie::updateTarget(Human& newTarget)
{
  if (this->target == &newTarget)
    return ;
  if (!this->target || (newTarget.entity.fixture.pos - this->entity.fixture.pos).length2() < (this->target->entity.fixture.pos - this->entity.fixture.pos).length2()) {
    if (this->target)
      this->target->removeHunter(*this);
    this->target = &newTarget;
    this->target->addHunter(*this);
  }
}
