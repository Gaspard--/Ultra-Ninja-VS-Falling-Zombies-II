#ifndef ZOMBIEDETECTIONRANGE_HPP
# define ZOMBIEDETECTIONRANGE_HPP

# include "Entity.hpp"
# include "Zombie.hpp"

class	ZombieDetectionRange
{

public:

  ZombieDetectionRange(Zombie&);

  bool refreshRange(void);

  Entity entity;
  Zombie* affiliated;

private:

  int	cooldown;

  static constexpr int const tickBetween = 100;
  static constexpr double const zombieRange = 20.0;

};


#endif /* ZOMBIEDETECTIONRANGE_HPP */
