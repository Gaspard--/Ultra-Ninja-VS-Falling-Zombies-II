# include "ZombieDetectionRange.hpp"
# include "Zombie.hpp"

ZombieDetectionRange::ZombieDetectionRange(Zombie &zombie): affiliated(&zombie)
{
  this->entity.fixture.radius = this->zombieRange;
  this->entity.fixture.pos = this->affiliated->entity.fixture.pos;
}

