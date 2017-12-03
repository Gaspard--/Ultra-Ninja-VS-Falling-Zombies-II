#include "Human.hpp"

Human::Human(Entity entity, CityBlock &home)
  : Mob(entity, 1),
    infected(false),
    homePtr(&home)
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

CityBlock const &Human::getHome() const
{
  return *homePtr;
}

CityBlock &Human::getHome()
{
  return *homePtr;
}
