#include "Human.hpp"

Human::Human(Entity entity, CityBlock &home)
  : Mob(entity, 1),
    infected(false),
    homePtr(&home),
    coolDown(0)
{
}

Human::~Human()
{
}

void Human::update()
{
  if (coolDown > 0)
    coolDown--;
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

void Human::setCoolDown(int coolDown)
{
  this->coolDown = coolDown;
}

bool Human::canHighFive() const
{
  return coolDown <= 0;
}

void	Human::addHunter(Zombie& z)
{
  for (auto h : this->hunters) {
    if (h == &z)
      return ;
  }
  this->hunters.push_back(&z);
}

void	Human::removeHunter(Zombie& z)
{
  for (auto h = this->hunters.begin() ; h != this->hunters.end() ; ++h) {
    if (*h == &z) {
      this->hunters.erase(h);
      return ;
    }
  }
}
