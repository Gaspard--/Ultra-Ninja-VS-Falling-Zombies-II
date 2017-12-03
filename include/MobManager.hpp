#ifndef MOBMANAGER_HPP_
# define MOBMANAGER_HPP_

#include <vector>
#include <algorithm>
#include "Human.hpp"
#include "Zombie.hpp"
#include "Vect.hpp"

class MobManager
{
public:
  std::vector<Human> humans;
  std::vector<Zombie> zombies;

  MobManager() = default;
  ~MobManager() = default;

  void update(Physics const &physics);
  void mobDeath();
  void spawnZombie(Vect<2, double> pos);
};

#endif //!MOBMANAGER_HPP_
