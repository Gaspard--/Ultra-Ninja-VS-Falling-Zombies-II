#ifndef MOBMANAGER_HPP_
# define MOBMANAGER_HPP_

#include <vector>
#include <algorithm>
#include "Human.hpp"
#include "Zombie.hpp"

class MobManager
{
public:
  MobManager() = default;
  ~MobManager() = default;

  void mutation();

private:
  std::vector<Human> humans;
  std::vector<Zombie> zombies;
};

#endif //!MOBMANAGER_HPP_
