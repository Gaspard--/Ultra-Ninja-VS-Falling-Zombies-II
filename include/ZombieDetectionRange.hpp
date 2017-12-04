#ifndef ZOMBIEDETECTIONRANGE_HPP
# define ZOMBIEDETECTIONRANGE_HPP

#include "Entity.hpp"

class Zombie;

class	ZombieDetectionRange
{

public:

  ZombieDetectionRange(Zombie&);

  Entity entity;
  Zombie* affiliated;

private:

  int	cooldown;

  static constexpr double const zombieRange = 5.0;
};


#endif /* ZOMBIEDETECTIONRANGE_HPP */
