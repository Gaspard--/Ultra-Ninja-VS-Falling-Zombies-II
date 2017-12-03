# include "ZombieDetectionRange.hpp"

ZombieDetectionRange::ZombieDetectionRange(Zombie& zombie): affiliated(&zombie)
{
  this->cooldown = this->tickBetween;
  this->entity.fixture.radius = this->zombieRange;
  this->entity.fixture.pos = this->affiliated->entity.fixture.pos;
}

bool	ZombieDetectionRange::refreshRange(void)
{
  this->entity.fixture.pos = this->affiliated->entity.fixture.pos;
  if (!--this->cooldown) {
    this->cooldown = this->tickBetween;
    return (true);
  }
  return (false);
}
