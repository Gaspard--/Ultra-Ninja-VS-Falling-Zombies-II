#ifndef MOBMANAGER_HPP_
# define MOBMANAGER_HPP_

#include <vector>
#include <algorithm>
#include "Player.hpp"
#include "Human.hpp"
#include "Zombie.hpp"
#include "Vect.hpp"

class MobManager
{
public:
  std::vector<Player> players;
  std::vector<Human> humans;
  std::vector<Zombie> zombies;

  MobManager() = default;
  ~MobManager() = default;

  void update(Physics const &physics);
  void mobDeath();
  void spawnZombie(Vect<2, double> const& pos);
  void spawnPlayer(Vect<2, double> const& pos);
  Player& getPlayer();
  Player const& getPlayer() const;
};

#endif //!MOBMANAGER_HPP_
