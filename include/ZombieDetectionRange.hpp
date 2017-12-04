#ifndef ZOMBIEDETECTIONRANGE_HPP
# define ZOMBIEDETECTIONRANGE_HPP

#include "Entity.hpp"

struct Zombie;

class	ZombieDetectionRange
{

public:

  ZombieDetectionRange(Zombie&);

  Entity entity;
  Zombie* affiliated;

private:

  int	cooldown;

  static constexpr double const zombieRange = 10.0;
};


#endif /* ZOMBIEDETECTIONRANGE_HPP */
