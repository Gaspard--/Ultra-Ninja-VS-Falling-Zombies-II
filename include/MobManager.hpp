#ifndef MOBMANAGER_HPP_
# define MOBMANAGER_HPP_

#include <vector>
#include <algorithm>
#include "Human.hpp"
#include "Zombie.hpp"

class MobManager
{
public:
  std::vector<Human> humans;
  std::vector<Zombie> zombies;

  MobManager() = default;
  ~MobManager() = default;

  void update(Physics const &physics);
  void mutation();
};

#endif //!MOBMANAGER_HPP_
