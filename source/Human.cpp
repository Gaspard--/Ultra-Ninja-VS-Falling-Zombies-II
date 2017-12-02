#include "Human.hpp"

Human::Human(Entity entity)
  : Mob(entity, 1), infected(false)
{
}

Human::~Human()
{
}

void Human::setInfected(bool infected)
{
  this->infected = infected;
}

bool const& Human::getInfected() const
{
  return infected;
}
