#include "Human.hpp"

Human::Human(Entity entity, CityBlock &home)
  : Mob(entity, 1),
    infected(false),
    homePtr(&home),
    coolDown(0),
    basicWalkCooldown(0),
    dir(-1.0),
    runAwayCooldown(0),
    mustRunAway(false),
    posToEscape({0.0, 0.0}),
    canHighfive(false)
{
  entity.fixture.speed = {0.01, 0.0};
}

Human::~Human()
{
  homePtr->hab -= homePtr->hab ? 1 : 0;
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

void	Human::runAway(void)
{
  entity.fixture.speed += (entity.fixture.pos - posToEscape).normalized() * 0.0002;
}

void Human::update()
{
  handleJump();
  if (!isJumping)
    anim.animate(entity);
  coolDown -= coolDown > 0;
  canHighfive = false;
  if (mustRunAway)
    runAway();
  else if ((entity.fixture.pos - Vect<2, double>(static_cast<double>(homePtr->x), static_cast<double>(homePtr->y))).length2() > 1.0) {
    entity.fixture.speed += (Vect<2, double>(static_cast<double>(homePtr->x), static_cast<double>(homePtr->y)) - entity.fixture.pos).normalized() * 0.0005;
  }
  else {
      basicWalkCooldown -= basicWalkCooldown > 0;
      if (!basicWalkCooldown) {
	basicWalkCooldown = 100;
	dir *= -1.0;
      }
    entity.fixture.speed[0] += 0.0001 * dir;
  }
  runAwayCooldown -= runAwayCooldown > 0;
  if (!runAwayCooldown)
    mustRunAway = false;
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

float Human::getAnimationFrame() const
{
  return anim.getAnimationFrame();
}

void	Human::beScaredOf(const Vect<2, double>& pos)
{
  if (!mustRunAway || (entity.fixture.pos - pos).length2() < (entity.fixture.pos - posToEscape).length2()) {
    runAwayCooldown = 120;
    mustRunAway = true;
    posToEscape = pos;
  }
}
