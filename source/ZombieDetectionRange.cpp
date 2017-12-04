# include "ZombieDetectionRange.hpp"
# include "Zombie.hpp"

ZombieDetectionRange::ZombieDetectionRange(Zombie &zombie)
  : entity{zombie.entity.fixture}
  , affiliated(&zombie)
{
  this->entity.fixture.radius = this->zombieRange;
}

