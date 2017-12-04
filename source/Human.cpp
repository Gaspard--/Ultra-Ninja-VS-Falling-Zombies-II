#include "Human.hpp"

Human::Human(Entity entity, CityBlock &home)
  : Mob(entity, 1),
    infected(false),
    homePtr(&home),
    coolDown(0),
    canHighfive(false)
{
}

Human::~Human()
{
}

void Human::handleJump()
{
  constexpr double const maxHeight = 0.05;

  if (isJumping && offsetY < maxHeight)
    offsetY += 0.005;
  if (isJumping && offsetY >= maxHeight)
    isJumping = false;
  if (!isJumping && offsetY > 0.0)
    offsetY -= 0.005;
}

void Human::update()
{
  handleJump();
  if (!isJumping)
    anim.animate(entity);
  coolDown -= coolDown > 0;
  canHighfive = false;
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
  return canHighfive && coolDown <= 0;
}

void Human::addHunter(Zombie& z)
{
  for (auto h : this->hunters) {
    if (h == &z)
      return ;
  }
  this->hunters.push_back(&z);
}

void Human::removeHunter(Zombie& z)
{
  for (auto h = this->hunters.begin() ; h != this->hunters.end() ; ++h) {
    if (*h == &z) {
      this->hunters.erase(h);
      return ;
    }
  }
}

float Human::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}
